from flask import Flask
from flask import jsonify
from flask import request
import os
import sqlite3 as sl
import hashlib
from werkzeug.utils import redirect
import mail
import sendcard
from flask_socketio import SocketIO, emit, disconnect, join_room, leave_room
from flask import Blueprint
from flask import render_template
import json
import redis
import random
import threading
redis_db = redis.Redis(host='127.0.0.1', port=6379, db=0)
db = 'room_dbase'



room_id = 1
app = Flask(__name__)
socketio = SocketIO()
socketio.init_app(app, cors_allowed_origins='*')


UserData = sl.connect('D:\\server\\userdata.db',check_same_thread=False)

@app.route('/')
def index():
     return render_template('test.html')

# 对特定值进行计数
def count_value(key):
    count = redis_db.incr(key)
    return count

def decrease_value(key):
    count = redis_db.decr(key)
    return count

@socketio.on('create_room')
def Create_room(data):
    global room_id
    data_room_id = str(room_id)
    
    data = json.loads(data)
    
    data_account = data.get('account')
    redis_db.set(data_account,data_room_id)
    join_room(data_account)#用户自己的房间用于服务器区分用户
    join_room(room_id)
    check_room = str(room_id)+"_room"
    exist_room = str(room_id)+"_exist_room"
    redis_db.set(check_room,0)
    redis_db.set(exist_room,1)
    count_value(check_room)

    keys = redis_db.keys()

    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())

    emit('server_response',jsonify(type = 4,roomid = room_id).data.decode())
    room_id = room_id+1
    return str(room_id - 1) 



@socketio.on('join_room')
def Join_room(data):
    ##################################
    # 获取所有键
    keys = redis_db.keys()
    print("--------------------加入时候数据库内数据")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())
    ##################################
    
    data = json.loads(data)

    data_room_id = data.get("roomid")
    global room_id
    check_room = str(room_id-1)+"_room"

    
    count = redis_db.get(check_room)
    print("当前房间中人数为",count)
    if count == None:
        count = b'0'

    data_account = data.get("account")
    join_room(data_account)
    print("str(room_id)",str(room_id))
    print("redis_db.get(str(room_id)+)",redis_db.get(str(room_id-1)+"_exist_room"))
    if int(count.decode()) >= 3:
        print("当前房间已满")
        emit('sever_response',jsonify(type = 5,status = 2).data.decode())
        return False
    elif redis_db.get(str(room_id-1)+"_exist_room") == None:
        print("加入的房间不存在")
        emit('server_response',jsonify(type = 5,status = 0).data.decode())
        
    else:
        count_value(check_room)
        join_room(data_room_id)
        redis_db.set(data_account,data_room_id)
        print(request.sid,"已经成功加入")
        emit('server_response',jsonify(type = 5,status = 1).data.decode())
        print("--------------------",redis_db.get(data_account))
        return True
    
    
    
@socketio.on('leave_room')
def Leave_room(data):


    ##############################################
    # 获取所有键
    keys = redis_db.keys()
    print("--------------------删除前数据库内数据")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())
    ##############################################

    data = json.loads(data)
    print("要断开连接的数据是",data)
    data_account = data.get("account")
    data_room_id = data.get("roomid")
    check_room = str(room_id-1)+"_room"
    
    decrease_value(check_room)
    redis_db.delete(data_account)

    leave_room(data_room_id)
    print("删除成功")
    emit('server_response',jsonify(type = 6,status = 1).data.decode())
    ######################################
    # 获取所有键
    keys = redis_db.keys()
    print("删除后数据库内容")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())
    ######################################
    return True
class ReadyPlayer(threading.local):
    def __init__(self):
        self.num = 0
        self.account = []
ready_player = ReadyPlayer()
ready_player.num = 0
ready_player.account = []



class HandCards(threading.local):
    def __init__(self):
        self.all_cards = list(range(1,55))
        self.player_1_cards = []
        self.player_2_cards = []
        self.player_3_cards = []
        self.lord_cards = []
cards = HandCards()
def wash_cards():
    
    random.shuffle(cards.all_cards)
    cards.player_1_cards = cards.all_cards[:17]
        
    cards.all_cards = cards.all_cards[17:]
    cards.player_2_cards = cards.all_cards[:17]
    cards.all_cards = cards.all_cards[17:]
    cards.player_3_cards = cards.all_cards[:17]
    cards.all_cards = cards.all_cards[17:]
    cards.lord_cards = cards.all_cards


def package_cards(group):
    return int(sendcard.changetostring(sendcard.transfercard(group)),2)


@socketio.on('ready')
def ready(data):
    data = json.loads(data)
    data_account = data.get("account")
    
    ready_player.account.append(data_account)
    ready_player.num = ready_player.num + 1
    room_now = room_id -1
    print("------------------room_id",room_now)
    emit('server_response',data_account,room = room_now)
    print(data_account + "已经准备")
    if ready_player.num == 3:
        #emit('server_response','所有玩家都已经准备',room = room_now)
        wash_cards()

        print("一号玩家的手牌是",package_cards(cards.player_1_cards),"一号玩家的account:",ready_player.account[0])
        print("二号玩家的手牌是",package_cards(cards.player_2_cards),"二号玩家的account:",ready_player.account[1])
        print("三号玩家的手牌是",package_cards(cards.player_3_cards),"三号玩家的account:",ready_player.account[2])
        emit('server_response',jsonify(type = 8,handcards = package_cards(cards.player_1_cards),account = ready_player.account[0]).data.decode(),room = ready_player.account[0])
        emit('server_response',jsonify(type = 8,handcards = package_cards(cards.player_2_cards),account = ready_player.account[1]).data.decode(),room = ready_player.account[1])
        emit('server_response',jsonify(type = 8,handcards = package_cards(cards.player_3_cards),account = ready_player.account[2]).data.decode(),room = ready_player.account[2])
    return data_account + "已经准备" 




@app.route('/battle',methods = ["POST"])#存储对战数据
def BattlePost():
    BattleData = request.get_json()
    print(BattleData)
    get_Battle = BattleData.get("name")
    return jsonify(name = get_Battle)


@app.route('/signupmail',methods = ["POST"])#注册发送验证码
def SignupMailPost():
    SignupMailData = request.get_json()
    print(SignupMailData)

    mailData = SignupMailData.get("mail")
    print('mail=======================',mailData)
    code = mail.generate_verification_code()

    redis_db.setex(str(mailData)+"_signupmail",300,code)
    # 获取所有键
    keys = redis_db.keys()

    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())

    mail.send_email('18607706274@163.com','JNCMBLONBOPNOFTW',mail.write_email('18607706274@163.com',mailData,code),mailData)
    return str(code)

@app.route('/signup',methods = ["POST"])#存储注册信息
def SignupPost():
    SignupData = request.get_json()
    print(SignupData)
    global cursor
    cursor.execute('SELECT COUNT(*) FROM UserTable')

    accountData = str(cursor.fetchone()[0])
    accountData = accountData.zfill(11)

    print("accountData ==",accountData)

    mailData = SignupData.get("mail")
    usernameData = SignupData.get("username")
    codeData = SignupData.get("code")
    passwordData = SignupData.get("password")
    check_code = redis_db.get(str(mailData)+"_signupmail")
    print("redis_db.get(str(mailData)+_signupmail",check_code.decode())
    if str(codeData) == check_code.decode():
        passwordData = hashlib.md5(passwordData.encode()).digest().hex()
        UserDataDB = [usernameData,accountData,mailData,passwordData]
        print(UserDataDB)
        
        InsertLanguage = '''INSERT INTO UserTable values (?,?,?,?)'''
        cursor.execute(InsertLanguage,UserDataDB)
        global UserData
        UserData.commit()
        #UserData.close()
        return jsonify(upsignresult = True)
    else :
        return jsonify(upsignresult = False)


@app.route('/login',methods = ["POST"])#存储登录信息
def LoginPost():
    LoginData = request.get_json()
    print(LoginData)
    accountData = LoginData.get("account")
    mailData = LoginData.get("mail")
    passwordData = LoginData.get("password")
    encryptPassword = hashlib.md5(passwordData.encode()).digest().hex()
    AccountPassword = [accountData,encryptPassword]
    MailPassword = [mailData,encryptPassword]
   
    global cursor
    SelectLanguage_account = '''SELECT Uaccount,Upassword FROM UserTable WHERE Uaccount like ? AND Upassword like ?'''
    cursor.execute(SelectLanguage_account,AccountPassword)
    queryresult_account = cursor.fetchall()
    print("-----------------account_match_result",len(queryresult_account))

    SelectLanguage_mail = '''SELECT Uaccount,Upassword FROM UserTable WHERE Umail like ? AND Upassword like ?'''
    print("")
    cursor.execute(SelectLanguage_mail,MailPassword)
    queryresult_mail = cursor.fetchall()
    print("-----------------mail_match_result",len(queryresult_mail))
    
    if len(queryresult_account) == 0 and len(queryresult_mail) == 0:
        return jsonify(type = 1,loginStatus = 0)    
    else:
        return jsonify(type = 1,loginStatus = 1)


@app.route('/passwordforget',methods = ["POST"])#找回密码（验证是否发生过注册）
def PasswordForgetPost():
    PasswordForgetData = request.get_json()
    Findingmail = PasswordForgetData.get("mail")
    Findingcode = PasswordForgetData.get("code")
    
    print(redis_db.get(str(Findingmail)+'_passwordforgetmail'))
    print(str(Findingcode))
    FindingNewpassword = PasswordForgetData.get("password")
    print("code",Findingcode)
    FindingLanguage = '''SELECT Umail FROM UserTable WHERE Umail like ?'''
    cursor.execute(FindingLanguage,[Findingmail])
    queryresult = cursor.fetchall()
    print(queryresult)

    check_code =redis_db.get(str(Findingmail)+'_passwordforgetmail')
    print(" str(Findingcode):", str(Findingcode),"check_code:",check_code.decode())
    if len(queryresult) != 0 and str(Findingcode) == check_code.decode():
        Findingresult = True
    else:
        Findingresult = False
    if Findingresult == True:
        ChangeLanguage = '''UPDATE UserTable SET Upassword = ? WHERE Umail like ?'''
        FindingNewpassword = hashlib.md5(FindingNewpassword.encode()).digest().hex()
        cursor.execute(ChangeLanguage,[FindingNewpassword,Findingmail])
        print("mail and new password",[FindingNewpassword,Findingmail])
        global UserData
        UserData.commit()
        print("修改成功")
    else:
        print("您的验证码错误或者邮箱不存在")


    return jsonify(result = Findingresult)

@app.route('/passwordforgetmail',methods = ["POST"])#发送找回密码的验证码
def PasswordForgetMailPost():
    PasswordForgetData = request.get_json()
    Findingmail = PasswordForgetData.get("mail")
    print(Findingmail)

    FindingLanguage = '''SELECT Umail FROM UserTable WHERE Umail like ?'''
    cursor.execute(FindingLanguage,[Findingmail])

    code = mail.generate_verification_code()

    redis_db.setex(str(Findingmail) + "_passwordforgetmail",300,code)
    ##################################
    # 获取所有键
    keys = redis_db.keys()
    print("--------------------加入时候数据库内数据")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())
    ##################################
    mail.send_email('18607706274@163.com','JNCMBLONBOPNOFTW',mail.write_email('18607706274@163.com',Findingmail,code),Findingmail)
    
    return code 






cursor = UserData.cursor()
print("userdata")
CreateTable = '''CREATE TABLE UserTable (Uusername char(20),Uaccount char(20),Umail char(50),Upassword char(20),primary key(Uaccount))'''
#cursor.execute(CreateTable)
redis_db.flushdb()
    

socketio.run(app,port=22222,debug= True)

UserData.close()