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
import time

redis_db = redis.Redis(host='127.0.0.1', port=6379, db=0)
db = 'room_dbase'



room_id = 1
app = Flask(__name__)
socketio = SocketIO()
socketio.init_app(app, cors_allowed_origins='*')


UserData = sl.connect('D:\\server\\userdata.db',check_same_thread=False)

class Player(threading.local):
    def __init__(self):
        self.handcards = 0
        self.lord = 0
        self.account = ""
        self.double = 0
        self.handcards_num = 0
        self.situation = 0
        self.leaveroomtimes = 0
    def setlord(self,becomelord):
        self.lord = becomelord
    def sethandcards(self,cards):
        self.handcards = cards
    def setdouble(self,becomedouble):
        self.double = becomedouble
    def setnext_player(self,becomenext_player):
        self.next_player = becomenext_player
    def setprevious_player(self,becomeprevious_player):
        self.previous_player = becomeprevious_player
    def sethandcards_num(self,becomehandcards_num):
        self.handcards_num = becomehandcards_num
    def find_next_player(self):
        return self.next_player
    def change_handcards(self,cards):
        result = int(self.handcards, 2) ^ int(cards, 2)
        binary_result = bin(result)[2:].zfill(max(len(self.handcards), len(cards)))
        return binary_result
class AccountSituation(threading.local):
    def __init__(self,account,situation):
        self.account = account
        self.situation = situation


class BattleStatus(threading.local):
    def __init__(self):
        global room_id
        self.room_id = room_id
        self.room_count = 0
        self.player_1 = Player()

        self.player_2 = Player()

        self.player_3 = Player()

        self.account_list = [AccountSituation("",0),AccountSituation("",0),AccountSituation("",0)]
        self.room_status = 0 #房间当前状态号码，暂且定义1为游戏已经开始，0为游戏没有开始

    def set_account_list(self,account,situation):
        accountsituation = AccountSituation(account,situation)
        if accountsituation not in self.account_list:
            
            self.account_list[int(situation)-1] = accountsituation
    def find_situation(self,account):
        for i in range(0,3):
            if self.account_list[i].account == account:
                return self.account_list[i].situation
        
    def del_account_list(self,account,situation):
        accountsituation = AccountSituation(account,situation)
        self.account_list.remove(accountsituation)

    def someone_join_room(self):
        self.room_count += 1
    def someone_leave_room(self):
        self.room_count -= 1
    def player_enter_room(self,player):
        if self.room_count == 1:
            self.player_2 = player
            return 2
        elif self.room_count == 2:
            self.player_3 = player
            return 3

    def to_dict(self):
        return {'roomid':self.room_id,'player_1_account':self.player_1.account,
                'player_2_account':self.player_2.account,'player_3_account':self.player_3.account,
                'player_1_handcards':self.player_1.handcards,'player_2_handcards':self.player_2.handcards,
                'player_3_handcards':self.player_3.handcards,'room_status':self.room_status,
                'player_1_lord':self.player_1.lord,'player_2_lord':self.player_2.lord,
                'player_3_lord':self.player_2.lord,'room_status':self.room_status,
                'player_1_leavetimes':self.player_1.leaveroomtimes,'player_2_leavetimes':self.player_2.leaveroomtimes,
                'player_3_leavetimes':self.player_3.leaveroomtimes,'room_count':self.room_count
                }
def inform_room_status(relink_account,situation,room_id):
    situation_new = situation
    battle_data = BattleStatus()
    key = room_id+"_battle_data"
    battle_status = redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    roomid = battle_status.get("roomid")
    player_1_account = battle_status.get("player_1_account")
    player_2_account = battle_status.get("player_2_account")
    player_3_account = battle_status.get("player_3_account")
    player_1_handcards = battle_status.get("player_1_handcards")
    player_2_handcards = battle_status.get("player_2_handcards")
    player_3_handcards = battle_status.get("player_3_handcards")
    room_status = battle_status.get("room_status")
    player_1_lord = battle_status.get("player_1_lord")
    player_2_lord = battle_status.get("player_2_lord")
    player_3_lord = battle_status.get("player_3_lord")
    player_1_leavetimes = battle_status.get("player_1_leavetimes")
    player_2_leavetimes = battle_status.get("player_2_leavetimes")
    player_3_leavetimes = battle_status.get("player_3_leavetimes")
    room_count = battle_status.get("room_count")
 
    battle_data.room_id = roomid
    battle_data.player_1.account = player_1_account
    battle_data.player_2.account = player_2_account
    battle_data.player_3.account = player_3_account
    battle_data.player_1.handcards = player_1_handcards
    battle_data.player_2.handcards = player_2_handcards
    battle_data.player_3.handcards = player_3_handcards
    battle_data.room_status = room_status
    battle_data.player_1.lord = player_1_lord
    battle_data.player_2.lord = player_2_lord
    battle_data.player_3.lord = player_3_lord
    battle_data.player_1.leaveroomtimes = player_1_leavetimes
    battle_data.player_2.leaveroomtimes = player_2_leavetimes
    battle_data.player_3.leaveroomtimes = player_3_leavetimes
    battle_data.room_count = room_count       
 
    print("--------------------",situation_new)
    print("-----------------",battle_data.account_list)
    relink_player = Player()
    if situation_new == 1:
        relink_player = battle_data.player_1
    elif situation_new == 2:
        relink_player = battle_data.player_2
    elif situation_new == 3:
        relink_player = battle_data.player_3
    print("battle_data.room_id",battle_data.room_id)
    print("relink_player.handcards",relink_player.handcards)
    emit('server_response',jsonify(roomid = battle_data.room_id,situation = situation_new,
                                   handcards = relink_player.handcards,
                                   lord = relink_player.lord,double = relink_player.double).data.decode(),room = relink_account)
    emit('server_response',jsonify(roomid = battle_data.room_id,situation = situation_new,
                                   lord = relink_player.lord,double = relink_player.double).data.decode(),room = room_id)

class ReadyPlayer(threading.local):
    def __init__(self):
        self.num = 0
        self.account = []
ready_player = ReadyPlayer()


class HandCards(threading.local):
    def __init__(self):
        self.all_cards = list(range(1,55))
        self.player_1_cards = []
        self.player_2_cards = []
        self.player_3_cards = []
        self.lord_cards = []
cards = HandCards()

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
    # global battle_data
    battle_data = BattleStatus()
    battle_data.someone_join_room()
    data_room_id = str(battle_data.room_id)
    print("Battle_data:",battle_data.room_id)
    data = json.loads(data)
    data_account = data.get('account')
    roomhost = Player()
    roomhost.account = data_account
    roomhost.situation = 1
    battle_data.player_1 = roomhost
    
    battle_data.set_account_list(data_account,roomhost.situation)
    redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
    redis_db.set(data_account,data_room_id)
#########################################################
    print("data_room_id",data_room_id,"\n","battle_data.player_1.account",battle_data.player_1.account)    


#########################################################
    join_room(data_account)#用户自己的房间用于服务器区分用户
    join_room(data_room_id)

    check_room = str(data_room_id)+"_count_room"
    exist_room = str(data_room_id)+"_exist_room"
    redis_db.set(check_room,0)
    redis_db.set(exist_room,1)
    count_value(check_room)
#################################################################
    keys = redis_db.keys()

    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())
#################################################################
    emit('server_response',jsonify(type = 4,roomid = data_room_id).data.decode(),room = data_account)
    
    global room_id
    room_id = room_id+1
    return str(room_id - 1) 



@socketio.on('join_room')
def Join_room(data):
    # global battle_data
    data = json.loads(data)
    data_room_id = data.get("roomid")
    print("data_room_id",data_room_id)
    key = data_room_id+"_battle_data"
    print("key--------==-=-=-=-=-=-=-=-=-=",key)
    battle_data = BattleStatus()
    
    
    
    battle_status = redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    roomid = battle_status.get("roomid")
    player_1_account = battle_status.get("player_1_account")
    player_2_account = battle_status.get("player_2_account")
    player_3_account = battle_status.get("player_3_account")
    player_1_handcards = battle_status.get("player_1_handcards")
    player_2_handcards = battle_status.get("player_2_handcards")
    player_3_handcards = battle_status.get("player_3_handcards")
    room_status = battle_status.get("room_status")
    player_1_lord = battle_status.get("player_1_lord")
    player_2_lord = battle_status.get("player_2_lord")
    player_3_lord = battle_status.get("player_3_lord")
    player_1_leavetimes = battle_status.get("player_1_leavetimes")
    player_2_leavetimes = battle_status.get("player_2_leavetimes")
    player_3_leavetimes = battle_status.get("player_3_leavetimes")
    room_count = battle_status.get("room_count")

    battle_data.room_id = roomid
    battle_data.player_1.account = player_1_account
    battle_data.player_2.account = player_2_account
    battle_data.player_3.account = player_3_account
    battle_data.player_1.handcards = player_1_handcards
    battle_data.player_2.handcards = player_2_handcards
    battle_data.player_3.handcards = player_3_handcards
    battle_data.room_status = room_status
    battle_data.player_1.lord = player_1_lord
    battle_data.player_2.lord = player_2_lord
    battle_data.player_3.lord = player_3_lord
    battle_data.player_1.leaveroomtimes = player_1_leavetimes
    battle_data.player_2.leaveroomtimes = player_2_leavetimes
    battle_data.player_3.leaveroomtimes = player_3_leavetimes
    battle_data.room_count = room_count


    
    global room_id
    check_room = str(battle_data.room_id)+"_count_room"

    
    count = redis_db.get(check_room)

    if count == None:
        count = b'0'

    data_account = data.get("account")
    join_room(data_account)
    print("str(room_id)",roomid)
    print("redis_db.get(str(room_id)+)",redis_db.get(str(battle_data.room_id)+"_exist_room"))
    if int(count.decode()) >= 3:
        print("当前房间已满")
        print("data_account",data_account)
        emit('server_response',jsonify(type = 5,status = 2).data.decode(),room = data_account)
        return False
    elif redis_db.get(str(battle_data.room_id)+"_exist_room") == None:
        print("加入的房间不存在")
        emit('server_response',jsonify(type = 5,status = 0).data.decode(),room = data_account)
        
    else:
        
        joiner = Player()
        joiner.account = data_account
        if joiner.account == player_1_account:
            joiner.situation = 1
        elif joiner.account == player_2_account:
            joiner.situation = 2
        elif joiner.situation == player_3_account:
            joiner.situation = 3
        print("joiner.situation:",joiner.situation)
        if joiner.situation == 0:
            selectplayer = battle_data.player_enter_room(joiner)
            print("======================================",selectplayer)
            if selectplayer == 2:
                joiner.situation = 2
            elif selectplayer == 3:
                joiner.situation = 3
            else:
                joiner.situation = 1
        if joiner.situation == 1:
            battle_data.player_1.account = joiner.account
            battle_data.player_1.situation = joiner.situation
            joiner.leaveroomtimes = player_1_leavetimes
        elif joiner.situation ==2:
            battle_data.player_2.account = joiner.account
            battle_data.player_2.situation = joiner.situation
            joiner.leaveroomtimes = player_2_leavetimes
        else:
            battle_data.player_3.account = joiner.account   
            battle_data.player_3.situation = joiner.situation
            joiner.leaveroomtimes = player_3_leavetimes
        if joiner.leaveroomtimes == 0:
            battle_data.set_account_list(data_account,joiner.situation)
        battle_data.someone_join_room()
        
        print("json.dumps(battle_data.to_dict()",joiner.account)
        redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
        inform_room_status(data_account,joiner.situation,data_room_id)
        
        count_value(check_room)
        join_room(data_room_id)
        redis_db.set(data_account,data_room_id)
#################################################################
        keys = redis_db.keys()

        # 遍历每个键，并输出键和对应的值
        for key in keys:
            value = redis_db.get(key)
            print(key.decode(), "->", value.decode())
#################################################################
        emit('server_response',jsonify(type = 5,status = 1,account = data_account).data.decode(),room = data_room_id)
        print("--------------------",redis_db.get(data_account))
        return True

    
    
@socketio.on('leave_room')
def Leave_room(data):

    battle_data = BattleStatus()
    data = json.loads(data)
    print("要断开连接的数据是",data)
    data_account = data.get("account")
    data_room_id = data.get("roomid")
    check_room = str(data_room_id)+"_count_room"
    

    key = data_room_id+"_battle_data"
    
    battle_status = redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    roomid = battle_status.get("roomid")
    player_1_account = battle_status.get("player_1_account")
    player_2_account = battle_status.get("player_2_account")
    player_3_account = battle_status.get("player_3_account")
    player_1_handcards = battle_status.get("player_1_handcards")
    player_2_handcards = battle_status.get("player_2_handcards")
    player_3_handcards = battle_status.get("player_3_handcards")
    room_status = battle_status.get("room_status")
    player_1_lord = battle_status.get("player_1_lord")
    player_2_lord = battle_status.get("player_2_lord")
    player_3_lord = battle_status.get("player_3_lord")
    player_1_leavetimes = battle_status.get("player_1_leavetimes")
    player_2_leavetimes = battle_status.get("player_2_leavetimes")
    player_3_leavetimes = battle_status.get("player_3_leavetimes")
    room_count = battle_status.get("room_count")

    battle_data.room_id = roomid
    battle_data.player_1.account = player_1_account
    battle_data.player_2.account = player_2_account
    battle_data.player_3.account = player_3_account
    battle_data.player_1.handcards = player_1_handcards
    battle_data.player_2.handcards = player_2_handcards
    battle_data.player_3.handcards = player_3_handcards
    battle_data.room_status = room_status
    battle_data.player_1.lord = player_1_lord
    battle_data.player_2.lord = player_2_lord
    battle_data.player_3.lord = player_3_lord
    battle_data.player_1.leaveroomtimes = player_1_leavetimes
    battle_data.player_2.leaveroomtimes = player_2_leavetimes
    battle_data.player_3.leaveroomtimes = player_3_leavetimes
    battle_data.room_count = room_count

    
    decrease_value(check_room)
    redis_db.delete(data_account)
    print("account_list",battle_data.account_list)
    
    if ready_player.account != []:
        ready_player.account.remove(data_account)
    print("删除成功")
    
    quiter = Player()
    quiter.account = data_account
    quiter.leaveroomtimes +=1
    situation =  battle_data.find_situation(quiter.account)
    if situation == 1 :
        battle_data.player_1.account = quiter.account
        battle_data.player_1.leaveroomtimes = quiter.leaveroomtimes
    elif situation == 2:
        battle_data.player_2.account = quiter.account
        battle_data.player_2.leaveroomtimes = quiter.leaveroomtimes
    else:
        battle_data.player_3.account = quiter.account
        battle_data.player_3.leaveroomtimes = quiter.leaveroomtimes

    #battle_data.del_account_list(data_account,battle_data.account_list.index(data_account)+1)
    battle_data.someone_leave_room()
    redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
    print("*********************",jsonify( type = 6 ,status = 1).data.decode())
    emit('server_response',jsonify( type = 6 ,status = 1,account = data_account).data.decode(),room = data_room_id)
   
    leave_room(data_room_id)
   
    ######################################
    # 获取所有键
    keys = redis_db.keys()
    print("-----------------------删除后数据库内容")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_db.get(key)
        print(key.decode(), "->", value.decode())
    print("------------------------删除后数据库内容")
    ######################################
    return True





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
    battle_data = BattleStatus()

    data = json.loads(data)
    data_account = data.get("account")
    data_room_id = data.get("roomid")
    global ready_player
    if data_account not in ready_player.account:
        ready_player.account.append(data_account)
    print("========================",ready_player.account)
    ready_player.num = ready_player.num + 1
    room_now = data_room_id
    print("------------------room_id",room_now)
    emit('server_response',data_account,room = room_now)
    print(data_account + "已经准备")

    key = data_room_id+"_battle_data"
    
    battle_status = redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    roomid = battle_status.get("roomid")
    player_1_account = battle_status.get("player_1_account")
    player_2_account = battle_status.get("player_2_account")
    player_3_account = battle_status.get("player_3_account")
    player_1_handcards = battle_status.get("player_1_handcards")
    player_2_handcards = battle_status.get("player_2_handcards")
    player_3_handcards = battle_status.get("player_3_handcards")
    room_status = battle_status.get("room_status")
    player_1_lord = battle_status.get("player_1_lord")
    player_2_lord = battle_status.get("player_2_lord")
    player_3_lord = battle_status.get("player_3_lord")
    player_1_leavetimes = battle_status.get("player_1_leavetimes")
    player_2_leavetimes = battle_status.get("player_2_leavetimes")
    player_3_leavetimes = battle_status.get("player_3_leavetimes")
    room_count = battle_status.get("room_count")

    battle_data.room_id = roomid
    battle_data.player_1.account = player_1_account
    battle_data.player_2.account = player_2_account
    battle_data.player_3.account = player_3_account
    battle_data.player_1.handcards = player_1_handcards
    battle_data.player_2.handcards = player_2_handcards
    battle_data.player_3.handcards = player_3_handcards
    battle_data.room_status = room_status
    battle_data.player_1.lord = player_1_lord
    battle_data.player_2.lord = player_2_lord
    battle_data.player_3.lord = player_3_lord
    battle_data.player_1.leaveroomtimes = player_1_leavetimes
    battle_data.player_2.leaveroomtimes = player_2_leavetimes
    battle_data.player_3.leaveroomtimes = player_3_leavetimes
    battle_data.room_count = room_count


    
    if ready_player.num == 3:

        wash_cards()
        battle_data.player_1.handcards = package_cards(cards.player_1_cards)
        battle_data.player_2.handcards = package_cards(cards.player_2_cards)
        battle_data.player_3.handcards = package_cards(cards.player_3_cards)
        print("一号玩家的手牌是",battle_data.player_1.handcards,"一号玩家的account:",ready_player.account[0])
        print("二号玩家的手牌是",battle_data.player_2.handcards,"二号玩家的account:",ready_player.account[1])
        print("三号玩家的手牌是",battle_data.player_3.handcards,"三号玩家的account:",ready_player.account[2])
        emit('server_response',jsonify(type = 8,handcards = package_cards(cards.player_1_cards),account = ready_player.account[0]).data.decode(),room = ready_player.account[0])
        emit('server_response',jsonify(type = 8,handcards = package_cards(cards.player_2_cards),account = ready_player.account[1]).data.decode(),room = ready_player.account[1])
        emit('server_response',jsonify(type = 8,handcards = package_cards(cards.player_3_cards),account = ready_player.account[2]).data.decode(),room = ready_player.account[2])
        redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))


    return data_account + "已经准备" 

@socketio.on('first_lord')
def first_lord():
    return 0



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
redis_db.set("room_id",1)

socketio.run(app,port=22222,debug= True)

UserData.close()