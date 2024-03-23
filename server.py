from flask import Flask
from flask import jsonify
from flask import request
import os
import sqlite3 as sl
import hashlib
from werkzeug.utils import redirect
import mail
#import sendcard
from flask_socketio import SocketIO, emit, disconnect, join_room, leave_room
from flask import Blueprint
from flask import render_template
import json
import redis

room_db = redis.Redis(host='127.0.0.1', port=6379, db=0)
db = 'room_dbase'

connected_client = []

rooms = []
room_id = 1
app = Flask(__name__)
socketio = SocketIO()
socketio.init_app(app, cors_allowed_origins='*')


UserData = sl.connect('D:\\server\\userdata.db',check_same_thread=False)

@app.route('/')
def index():
     return render_template('test.html')


@socketio.on('create_room')
def Create_room(data):
    global room_id
    data_room_id = str(room_id)
    
    data = json.loads(data)
    
    data_account = data.get('account')
    room_db.set(data_account,data_room_id)

    join_room(room_id)
    keys = room_db.keys()

    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = room_db.get(key)
        print(key.decode(), "->", value.decode())

    emit('server_response',room_id)
    room_id = room_id+1
    return str(room_id - 1) 


@socketio.on('join_room')
def Join_room(data):
    ##################################
    # 获取所有键
    keys = room_db.keys()
    print("--------------------加入时候数据库内数据")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = room_db.get(key)
        print(key.decode(), "->", value.decode())
    ##################################

    data = json.loads(data)
    data_room_id = data.get("roomid")
    
    
    count = 0
    Find = False
    for key in keys:
        value1 = room_db.get(key)
        if value1.decode() == data_room_id:
            count += 1
            Find = True
    print("当前房间中人数为",count)

    data_account = data.get("account")
    
    if count >= 3:
        print("当前房间已满")
        return False
    elif Find == False:
        print("加入的房间不存在")
        emit('server_response','房间不存在')
        
    else:
        join_room(data_room_id)
        room_db.set(data_account,data_room_id)
        print(request.sid,"已经成功加入")
        emit('server_response','加入房间成功')
        print("--------------------",room_db.get(data_account))
        return True
    
    
    
@socketio.on('leave_room')
def Leave_room(data):


    ##############################################
    # 获取所有键
    keys = room_db.keys()
    print("--------------------删除前数据库内数据")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = room_db.get(key)
        print(key.decode(), "->", value.decode())
    ##############################################




    data = json.loads(data)
    print("要断开连接的数据是",data)
    data_account = data.get("account")
    data_room_id = data.get("roomid")
    room_db.delete(data_account)
    leave_room(data_room_id)
    print("删除成功")
    emit('server_response','退出房间成功')
    ######################################
    # 获取所有键
    keys = room_db.keys()
    print("删除后数据库内容")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = room_db.get(key)
        print(key.decode(), "->", value.decode())
    ######################################
    return True




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

    global code5minute
    code5minute = code

    mail.send_email('18607706274@163.com','JNCMBLONBOPNOFTW',mail.write_email('18607706274@163.com',mailData,code),mailData)
    return str(code5minute)

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
    global code5minute
    if str(codeData) == code5minute:
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
        Loginresult = False
    else:
        Loginresult = True
    return jsonify(result = Loginresult)

@app.route('/passwordforget',methods = ["POST"])#找回密码（验证是否发生过注册）
def PasswordForgetPost():
    PasswordForgetData = request.get_json()
    print(PasswordForgetData)
    Findingmail = PasswordForgetData.get("mail")
    Findingcode = PasswordForgetData.get("code")

    FindingNewpassword = PasswordForgetData.get("password")
    print("code",Findingcode)
    FindingLanguage = '''SELECT Umail FROM UserTable WHERE Umail like ?'''
    cursor.execute(FindingLanguage,[Findingmail])
    queryresult = cursor.fetchall()
    print(queryresult)
    global code5minute
    print("code5minute",code5minute)

    if len(queryresult) != 0 and Findingcode == code5minute :
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
    global code5minute
    code5minute = code
    mail.send_email('18607706274@163.com','JNCMBLONBOPNOFTW',mail.write_email('18607706274@163.com',Findingmail,code),Findingmail)

    return str(code5minute)   






cursor = UserData.cursor()
print("userdata")
CreateTable = '''CREATE TABLE UserTable (Uusername char(20),Uaccount char(20),Umail char(50),Upassword char(20),primary key(Uaccount))'''
#cursor.execute(CreateTable)

    

socketio.run(app,port=22222,debug= True)

UserData.close()