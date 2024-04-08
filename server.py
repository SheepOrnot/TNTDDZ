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
from flask import render_template
import json
import battlestatus
import random
import lordevent
import time
import redis_data
import transfercards
import eventlet
import countdown
import CardCheck


db = 'room_dbase'


app = Flask(__name__)
socketio = SocketIO()
socketio.init_app(app, cors_allowed_origins='*')


UserData = sl.connect('userdata.db',check_same_thread=False)
UserData = sl.connect('userdata.db',check_same_thread=False)


def inform_room_status(relink_account,seat,room_id):
    seat_new = seat
    battle_data = battlestatus.BattleStatus()
    key = room_id+"_battle_data"
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)

    battle_data.room_id = battle_status.get("roomid")
    battle_data.get_battle_status(battle_status)
 
    relink_player = battlestatus.Player()
    if seat_new == 1:
        relink_player = battle_data.player_1
    elif seat_new == 2:
        relink_player = battle_data.player_2
    elif seat_new == 3:
        relink_player = battle_data.player_3
    print("battle_data.room_id",battle_data.room_id)

    if redis_data.redis_db.get(str(battle_data.room_id)+"_"+str(relink_player.account)+"_player_"+str(seat_new)+"_handcards") is not None:
        relink_player.handcards = redis_data.redis_db.get(str(battle_data.room_id)+"_"+str(relink_player.account)+"_player_"+str(seat_new)+"_handcards").decode()
    print("relink_player手牌:",relink_player.handcards)
    print("relink_player.handcards",relink_player.handcards)
    emit('server_response',jsonify(roomid = battle_data.room_id,seat = seat_new,
                                   handcards = int(relink_player.handcards),
                                   lord = relink_player.lord,double = relink_player.double).data.decode(),room = relink_account)
    emit('server_response',jsonify(account = relink_player.account,roomid = battle_data.room_id,seat = seat_new,
                                   lord = relink_player.lord,double = relink_player.double).data.decode(),room = room_id)




@app.route('/')
def index():
     return render_template('test.html')



@socketio.on('create_room')
def Create_room(data):
    # global battle_data
    print(f"接收到创建房间请求: {data}")
    battle_data = battlestatus.BattleStatus()
    battle_data.someone_join_room()
    data_room_id = str(battle_data.room_id)
    print("Battle_data:",battle_data.room_id)
    data = json.loads(data)
    data_account = data.get('account')
    roomhost = battlestatus.Player()
    roomhost.account = data_account
    roomhost.seat = 1
    battle_data.player_1 = roomhost

    redis_data.redis_db.set(str(data_room_id)+"_ask_lord_times",0)
    battle_data.set_account_list(data_account,roomhost.seat)
    redis_data.redis_db.set(str(data_room_id)+"_ready_count",0)
    redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
    redis_data.redis_db.set(data_account,data_room_id)
#########################################################
    print("data_room_id",data_room_id,"\n","battle_data.player_1.account",battle_data.player_1.account)    


#########################################################
    join_room(data_account)#用户自己的房间用于服务器区分用户
    join_room(data_room_id)

    check_room = str(data_room_id)+"_count_room"
    exist_room = str(data_room_id)+"_exist_room"
    redis_data.redis_db.set(check_room,0)
    redis_data.redis_db.set(exist_room,1)
    redis_data.count_value(check_room)
#################################################################
    keys = redis_data.redis_db.keys()

    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_data.redis_db.get(key)
        print(key.decode(), "->", value.decode())
#################################################################
    emit('server_response',jsonify(type = 4,status = 1, roomid = data_room_id,seat = roomhost.seat).data.decode(),room = data_account)
    
    
    battlestatus.room_id = battlestatus.room_id+1
    return str(battlestatus.room_id - 1) 



@socketio.on('join_room')
def Join_room(data):

    data = json.loads(data)
    data_room_id = data.get("roomid")
    print("data_room_id",data_room_id)
    key = data_room_id+"_battle_data"

    battle_data = battlestatus.BattleStatus()
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)

    battle_data.room_id = data_room_id
    battle_data.get_battle_status(battle_status)

    check_room = str(battle_data.room_id)+"_count_room"

    
    count = redis_data.redis_db.get(check_room)

    if count == None:
        count = b'0'

    data_account = data.get("account")
    join_room(data_account)

    print("redis_db.get(str(room_id)+)",redis_data.redis_db.get(str(battle_data.room_id)+"_exist_room"))
    if int(count.decode()) >= 3:
        print("当前房间已满")
        print("data_account",data_account)
        emit('server_response',jsonify(type = 5,status = 2).data.decode(),room = data_account)
        return False
    elif redis_data.redis_db.get(str(battle_data.room_id)+"_exist_room") == None:
        print("加入的房间不存在")
        emit('server_response',jsonify(type = 5,status = 0).data.decode(),room = data_account)
        
    else:
        
        joiner = battlestatus.Player()
        joiner.account = data_account
        print("joiner_account:",joiner.account)

        if str(joiner.account) == str(battle_data.player_1.account):
            joiner.seat = 1
        elif str(joiner.account) == str(battle_data.player_2.account):
            joiner.seat = 2
        elif str(joiner.account) == str(battle_data.player_3.account):
            joiner.seat = 3
        print("joiner.seat:",joiner.seat)
        if joiner.seat == 0:
            selectplayer = battle_data.player_enter_room(joiner)
            print("======================================",selectplayer)
            if selectplayer == 2:
                joiner.seat = 2
            elif selectplayer == 3:
                joiner.seat = 3
            else:
                joiner.seat = 1
        if joiner.seat == 1:
            battle_data.player_1.account = joiner.account
            battle_data.player_1.seat = joiner.seat
            joiner.leaveroomtimes = battle_data.player_1.leaveroomtimes
        elif joiner.seat ==2:
            battle_data.player_2.account = joiner.account
            battle_data.player_2.seat = joiner.seat
            joiner.leaveroomtimes = battle_data.player_2.leaveroomtimes
        elif joiner.seat ==3:
            battle_data.player_3.account = joiner.account   
            battle_data.player_3.seat = joiner.seat
            joiner.leaveroomtimes = battle_data.player_3.leaveroomtimes
        if joiner.leaveroomtimes == 0:
            battle_data.set_account_list(data_account,joiner.seat)
        battle_data.someone_join_room()
        
        print("json.dumps(battle_data.to_dict()",joiner.account)
        redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
        inform_room_status(data_account,joiner.seat,data_room_id)
        
        redis_data.count_value(check_room)
        join_room(data_room_id)
        redis_data.redis_db.set(data_account,data_room_id)
#################################################################
        keys = redis_data.redis_db.keys()

        # 遍历每个键，并输出键和对应的值
        for key in keys:
            value = redis_data.redis_db.get(key)
            print(key.decode(), "->", value.decode())
#################################################################
        emit('server_response',jsonify(type = 5,status = 1,account = data_account,seat = joiner.seat).data.decode(),room = data_room_id)
        print("--------------------",redis_data.redis_db.get(data_account))
        return True

    
    
@socketio.on('leave_room')
def Leave_room(data):

    battle_data = battlestatus.BattleStatus()
    data = json.loads(data)
    print("要断开连接的数据是",data)
    data_account = data.get("account")
    data_room_id = data.get("roomid")
    check_room = str(data_room_id)+"_count_room"
    

    key = data_room_id+"_battle_data"
    
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)

    battle_data.room_id = data_room_id
    battle_data.get_battle_status(battle_status)
    
    redis_data.decrease_value(check_room)
    redis_data.redis_db.delete(data_account)

    
    print("删除成功")
    
    quiter = battlestatus.Player()
    quiter.account = data_account
    quiter.leaveroomtimes +=1
    if str(quiter.account) == str(battle_data.player_1.account):
        seat = 1
    elif str(quiter.account) == str(battle_data.player_2.account):
        seat = 2
    elif str(quiter.account) == str(battle_data.player_3.account):
        seat = 3

    if seat == 1 :
        battle_data.player_1.account = quiter.account
        battle_data.player_1.leaveroomtimes = quiter.leaveroomtimes
    elif seat == 2:
        battle_data.player_2.account = quiter.account
        battle_data.player_2.leaveroomtimes = quiter.leaveroomtimes
    elif seat == 3:
        battle_data.player_3.account = quiter.account
        battle_data.player_3.leaveroomtimes = quiter.leaveroomtimes

    battle_data.someone_leave_room()
    redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
    print("*********************",jsonify( type = 6 ,status = 1).data.decode())
    emit('server_response',jsonify( type = 6 ,status = 1,account = data_account).data.decode(),room = data_room_id)
   
    leave_room(data_room_id)
   
    ######################################
    # 获取所有键
    keys = redis_data.redis_db.keys()
    print("-----------------------删除后数据库内容")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_data.redis_db.get(key)
        print(key.decode(), "->", value.decode())
    print("------------------------删除后数据库内容")
    ######################################
    return True


def package_cards(group):
    return int(sendcard.transfercard(group),2)

 
@socketio.on('ready')
def ready(data):
    battle_data = battlestatus.BattleStatus()
    
    data = json.loads(data)
    data_account = data.get("account")
    data_room_id = data.get("roomid")
    redis_data.redis_db.set(str(data_room_id)+"_double_num",0)
    redis_data.count_value(data_room_id+"_ready_count")

    room_now = data_room_id
    print("------------------room_id",room_now)

    print(data_account + "已经准备")

    key = data_room_id+"_battle_data"
    
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    roomid = battle_status.get("roomid")

    battle_data.room_id = roomid
    battle_data.get_battle_status(battle_status)

    seat = 0
    if data_account == battle_data.player_1.account:
        seat = 1
    elif data_account == battle_data.player_2.account:
        seat = 2
    elif data_account == battle_data.player_3.account:
        seat = 3

    redis_data.redis_db.set(str(data_room_id)+"_"+str(seat)+"_ready_account",data_account)

    print("redis_data.redis_db.get(str(data_room_id)",redis_data.redis_db.get(str(data_room_id)+"_ready_count").decode())
    if redis_data.redis_db.get(str(data_room_id)+"_ready_count").decode() == '3':
        cards = battlestatus.HandCards()
        cards.wash_cards()
        battle_data.player_1.handcards = package_cards(cards.player_1_cards)
        redis_data.redis_db.set(str(data_room_id)+"_"+str(battle_data.player_1.account)+"_player_1_handcards",battle_data.player_1.handcards)
        battle_data.player_2.handcards = package_cards(cards.player_2_cards)
        redis_data.redis_db.set(str(data_room_id)+"_"+str(battle_data.player_2.account)+"_player_2_handcards",battle_data.player_2.handcards)
        battle_data.player_3.handcards = package_cards(cards.player_3_cards)
        redis_data.redis_db.set(str(data_room_id)+"_"+str(battle_data.player_3.account)+"_player_3_handcards",battle_data.player_3.handcards)
        
        first_lord_seat = who_start_first_lord()#选择谁第一个叫地主
        if first_lord_seat == 1:
            player_1_first_lord = 1
            player_2_first_lord = 0
            player_3_first_lord = 0
        elif first_lord_seat == 2:
            player_1_first_lord = 0
            player_2_first_lord = 1
            player_3_first_lord = 0
        elif first_lord_seat == 3:
            player_1_first_lord = 0
            player_2_first_lord = 0
            player_3_first_lord = 1
      
        print("一号玩家的手牌是",battle_data.player_1.handcards,"一号玩家的account:",cards.player_1_cards)
        print("二号玩家的手牌是",battle_data.player_2.handcards,"二号玩家的account:",sendcard.transfercard(cards.player_2_cards))
        print("三号玩家的手牌是",battle_data.player_3.handcards,"三号玩家的account:",sendcard.transfercard(cards.player_3_cards))

        emit('server_response',jsonify(type = 8,first_lord = player_1_first_lord,handcards = battle_data.player_1.handcards,account = redis_data.redis_db.get(str(data_room_id)+"_1_ready_account").decode()).data.decode(),room = redis_data.redis_db.get(str(data_room_id)+"_1_ready_account").decode())
        emit('server_response',jsonify(type = 8,first_lord = player_2_first_lord,handcards = battle_data.player_2.handcards,account = redis_data.redis_db.get(str(data_room_id)+"_2_ready_account").decode()).data.decode(),room = redis_data.redis_db.get(str(data_room_id)+"_2_ready_account").decode())
        emit('server_response',jsonify(type = 8,first_lord = player_3_first_lord,handcards = battle_data.player_3.handcards,account = redis_data.redis_db.get(str(data_room_id)+"_3_ready_account").decode()).data.decode(),room = redis_data.redis_db.get(str(data_room_id)+"_3_ready_account").decode())
        redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
        redis_data.redis_db.set(str(battle_data.room_id)+'_lord_cards',package_cards(cards.lord_cards))
        ######################################
        # 获取所有键
        keys = redis_data.redis_db.keys()
        print("-----------------------")
        # 遍历每个键，并输出键和对应的值
        for key in keys:
            value = redis_data.redis_db.get(key)
            print(key.decode(), "->", value.decode())
        print("------------------------")
        ######################################

    return data_account + "已经准备" 
def who_start_first_lord():
    first_lord_seat = random.randint(1,3)
    return first_lord_seat

@socketio.on('double')
def double(data):
    data = json.loads(data)
    data_room_id = data.get("roomid")
    data_double = data.get("double")
    data_seat = data.get("seat")
    key = data_room_id+"_battle_data"
    
    battle_data = battlestatus.BattleStatus()
    battle_data.room_id = data_room_id
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    battle_data.get_battle_status(battle_status)

    redis_data.redis_db.set(str(data_room_id)+'_'+str(data_seat)+"_output_handcards_signal",0)
    redis_data.count_value(str(data_room_id)+"_double_num")
    if int(data_seat) == 1:
        battle_data.player_1.double = int(data_double)

        emit('server_response',jsonify(seat = data_seat,double = int(data_double),account = battle_data.player_1.account,type = 1).data.decode(),room = data_room_id)
    elif int(data_seat) == 2:
        battle_data.player_2.double = int(data_double)

        emit('server_response',jsonify(seat = data_seat,double = int(data_double),account = battle_data.player_2.account,type = 1).data.decode(),room = data_room_id)
    elif int(data_seat) == 3:
        battle_data.player_3.double = int(data_double)

        emit('server_response',jsonify(seat = data_seat,double = int(data_double),account = battle_data.player_3.account,type = 1).data.decode(),room = data_room_id)
    redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
    #当服务器收到了三条加倍后通知地主进行出牌

    print("========================",redis_data.redis_db.get(str(data_room_id)+"_double_num").decode())
    if int(redis_data.redis_db.get(str(data_room_id)+"_double_num").decode()) == 3:
        emit('server_response',jsonify(type = 1000000).data.decode(),room = battle_data.find_lord_account())
        print("叫地主的账户是：",battle_data.find_lord_account())






@socketio.on('bigger_cards')
def 管牌(data):
    data = json.loads(data)
    data_room_id = data.get("roomid")
    data_tablecards = data.get("tablecards")
    data_can_cannot = data.get("canorcannot")
    data_seat = data.get("seat")
    data_account = data.get("account")
    if int(data_can_cannot) == 1:
        data_outputcards = data.get("outputcards")
        check_result = CardCheck.CardCheck(int(data_outputcards,data_tablecards))
        if check_result[1] == False:
            emit('server_response',jsonify(type = 1111,checkresult = 0).data.decode(),room = data_account)
        else:
            key = data_room_id+"_battle_data"
            battle_data = battlestatus.BattleStatus()
            battle_data.room_id = data_room_id
            battle_status = redis_data.redis_db.get(key).decode()
            battle_status = json.loads(battle_status)
            battle_data.get_battle_status(battle_status)
            
            handcards = battle_data.find_handcards(data_seat)
            bitsite_handcards = transfercards.transfer_int_to_str(int(handcards))
            bitsite_output_cards = transfercards.transfer_int_to_str(int(data_outputcards))
            updated_handcards = transfercards.xor_cards(bitsite_handcards,bitsite_output_cards)
            int_updated_handcards = int(updated_handcards,2)

            if int_updated_handcards == 0:
                if battle_data.find_lord_num(data_seat) == 1:
                    emit('server_response',jsonify(type = 1,win_result = 0).data.decode(),room = battle_data.find_farmer_account()[0])
                    emit('server_response',jsonify(type = 1,win_result = 0).data.decode(),room = battle_data.find_farmer_account()[1])
                    emit('server_response',jsonify(type = 1,win_result = 1).data.decode(),room = battle_data.find_lord_account())
                elif battle_data.find_lord_num(data_seat) == 0:
                    emit('server_response',jsonify(type = 1,win_result = 1).data.decode(),room = battle_data.find_farmer_account()[0])
                    emit('server_response',jsonify(type = 1,win_result = 1).data.decode(),room = battle_data.find_farmer_account()[1])
                    emit('server_response',jsonify(type = 1,win_result = 0).data.decode(),room = battle_data.find_lord_account())
                return 0 
            
            
            battle_data.renew_handcards(data_seat,int_updated_handcards)
            redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
            emit('server_response',jsonify(type = 999,tablecards = data_outputcards,seat = data_seat).data.decode(),room = data_room_id)
            time.sleep(1)
            emit('server_response',jsonify(type = 999).data.decode(),room = lordevent.find_seat_fit_account(lordevent.find_next_seat(data_seat),data_room_id))
    elif int(data_can_cannot) == 0:
        emit('server_response',jsonify(type = 999).data.decode(),room = lordevent.find_seat_fit_account(lordevent.find_next_seat(data_seat),data_room_id))





@socketio.on('output_handcards')
def output_handcards(data):
    data = json.loads(data)
    data_room_id = data.get("roomid")
    data_seat = data.get("seat")
    data_output_cards = int(data.get("outputcards"))        




    key = data_room_id+"_battle_data"
    battle_data = battlestatus.BattleStatus()
    battle_data.room_id = data_room_id
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    battle_data.get_battle_status(battle_status)
    handcards = battle_data.find_handcards(data_seat)
    bitsite_handcards = transfercards.transfer_int_to_str(int(handcards))
    bitsite_output_cards = transfercards.transfer_int_to_str(int(data_output_cards))
    updated_handcards = transfercards.xor_cards(bitsite_handcards,bitsite_output_cards)
    int_updated_handcards = int(updated_handcards,2)
    


    if int_updated_handcards == 0:
        if battle_data.find_lord_num(data_seat) == 1:
            emit('server_response',jsonify(type = 1,win_result = 0).data.decode(),room = battle_data.find_farmer_account()[0])
            emit('server_response',jsonify(type = 1,win_result = 0).data.decode(),room = battle_data.find_farmer_account()[1])
            emit('server_response',jsonify(type = 1,win_result = 1).data.decode(),room = battle_data.find_lord_account())
        elif battle_data.find_lord_num(data_seat) == 0:
            emit('server_response',jsonify(type = 1,win_result = 1).data.decode(),room = battle_data.find_farmer_account()[0])
            emit('server_response',jsonify(type = 1,win_result = 1).data.decode(),room = battle_data.find_farmer_account()[1])
            emit('server_response',jsonify(type = 1,win_result = 0).data.decode(),room = battle_data.find_lord_account())
        return 0 
    battle_data.renew_handcards(data_seat,int_updated_handcards)
    redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict()))
    emit('server_response',jsonify(type = 1,tablecards = data_output_cards).data.decode(),room = data_room_id)
    time.sleep(0.5)
    emit('server_response',jsonify(type = 900).data.decode(),room = battle_data.find_account(lordevent.find_next_seat(data_seat)))#通知下家进行管牌操作


@socketio.on('ask_for_lord')
def ask_for_lord(data):
    data = json.loads(data)
    data_account = data.get("account")
    data_room_id = data.get("roomid")
    data_lord = data.get("lord")
    data_seat = data.get("seat")
    print("data_account:",data_account)
    redis_data.count_value(str(data_room_id)+"_ask_lord_times")
    lord_times = redis_data.get_ask_lord_times(data_room_id)
    if int(lord_times) != 3: 
        lordevent.decide_lord(int(data_lord),data_account,data_room_id,int(data_seat))
    elif int(lord_times) == 3:
        lordevent.random_lord(data_room_id)

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

    redis_data.redis_db.setex(str(mailData)+"_signupmail",300,code)
    # 获取所有键
    keys = redis_data.redis_db.keys()

    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_data.redis_db.get(key)
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
    check_code = redis_data.redis_db.get(str(mailData)+"_signupmail")
    print("redis_data.redis_db.get(str(mailData)+_signupmail",check_code.decode())
    if str(codeData) == check_code.decode():
        passwordData = hashlib.md5(passwordData.encode()).digest().hex()
        UserDataDB = [usernameData,accountData,mailData,passwordData]
        print(UserDataDB)
        
        InsertLanguage = '''INSERT INTO UserTable values (?,?,?,?)'''
        cursor.execute(InsertLanguage,UserDataDB)
        global UserData
        UserData.commit()
        #UserData.close()
        return jsonify(type = 2, signupresult = 1)
    else :
        return jsonify(type = 2, signupresult = 0)


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

@app.route('/passwordforget_code_verify',methods = ["POST"])
def PasswordForget_Code_Verify():
    PasswordForgetData = request.get_json()
    Findingmail = PasswordForgetData.get("mail")
    Findingcode = PasswordForgetData.get("code")
    code = redis_data.redis_db.get(str(Findingmail)+'_passwordforgetmail').decode()
    if code == str(Findingcode):
        Findingresult = 1
    else:
        Findingresult = 0
    return jsonify(type = 10,result = Findingresult)

@app.route('/signup_code_verify',methods = ["POST"])
def Signup_code_verify():
    Signup = request.get_json()
    Findingmail = Signup.get("mail")
    Findingcode = Signup.get("code")
    code = redis_data.redis_db.get(str(Findingmail)+'_signupmail').decode()
    if code == str(Findingcode):
        Findingresult = 1
    else:
        Findingresult = 0
    return jsonify(type = 9,result = Findingresult)

@app.route('/passwordforget',methods = ["POST"])#找回密码（验证是否发生过注册）
def PasswordForgetPost():
    PasswordForgetData = request.get_json()
    Findingmail = PasswordForgetData.get("mail")
    Findingcode = PasswordForgetData.get("code")
    
    print(redis_data.redis_db.get(str(Findingmail)+'_passwordforgetmail'))
    print(str(Findingcode))
    FindingNewpassword = PasswordForgetData.get("password")
    print("code",Findingcode)
    FindingLanguage = '''SELECT Umail FROM UserTable WHERE Umail like ?'''
    cursor.execute(FindingLanguage,[Findingmail])
    queryresult = cursor.fetchall()
    print(queryresult)

    check_code =redis_data.redis_db.get(str(Findingmail)+'_passwordforgetmail')
    print(" str(Findingcode):", str(Findingcode),"check_code:",check_code.decode())
    if len(queryresult) != 0 and str(Findingcode) == check_code.decode():
        Findingresult = 1
    else:
        Findingresult = 0
    if Findingresult == 1:
        ChangeLanguage = '''UPDATE UserTable SET Upassword = ? WHERE Umail like ?'''
        FindingNewpassword = hashlib.md5(FindingNewpassword.encode()).digest().hex()
        cursor.execute(ChangeLanguage,[FindingNewpassword,Findingmail])
        print("mail and new password",[FindingNewpassword,Findingmail])
        global UserData
        UserData.commit()
        print("修改成功")
    else:
        print("您的验证码错误或者邮箱不存在")


    return jsonify(type = 3,result = Findingresult)

@app.route('/passwordforgetmail',methods = ["POST"])#发送找回密码的验证码
def PasswordForgetMailPost():
    PasswordForgetData = request.get_json()
    Findingmail = PasswordForgetData.get("mail")
    print(Findingmail)

    FindingLanguage = '''SELECT Umail FROM UserTable WHERE Umail like ?'''
    cursor.execute(FindingLanguage,[Findingmail])

    code = mail.generate_verification_code()

    redis_data.redis_db.setex(str(Findingmail) + "_passwordforgetmail",300,code)
    ##################################
    # 获取所有键
    keys = redis_data.redis_db.keys()
    print("--------------------加入时候数据库内数据")
    # 遍历每个键，并输出键和对应的值
    for key in keys:
        value = redis_data.redis_db.get(key)
        print(key.decode(), "->", value.decode())
    ##################################
    mail.send_email('18607706274@163.com','JNCMBLONBOPNOFTW',mail.write_email('18607706274@163.com',Findingmail,code),Findingmail)
    
    return code 



cursor = UserData.cursor()
print("userdata")
CreateTable = '''CREATE TABLE UserTable (Uusername char(20),Uaccount char(20),Umail char(50),Upassword char(20),primary key(Uaccount))'''

redis_data.redis_db.flushdb()
redis_data.redis_db.set("room_id",1)

socketio.run(app,port=22222,debug= False)

UserData.close()