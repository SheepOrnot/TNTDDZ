import redis_data
from flask_socketio import SocketIO, emit, disconnect, join_room, leave_room
from flask import jsonify
import lordevent
import battlestatus
import json

def rob_and_ask(account,roomid,ask,rob,seat):
    battle_data = battlestatus.BattleStatus()
    key = str(roomid)+"_battle_data"
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    battle_data.get_battle_status(battle_status)

    redis_data.redis_db.get(str(roomid)+'_ask_rob').decode()
    now_double = redis_data.redis_db.get(str(roomid)+"_double").decode()
    
    status = 0
    print("int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode())",int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()))
    if int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) < 2:
        redis_data.count_value(str(roomid)+'_lord_rob_times')
        if int(rob) == 1 or int(ask) == 1:
            print("------------------========================",redis_data.count_value(str(roomid)+"_ask_or_rob_times"))
            rob_lord_double(rob,roomid)
            now_double = redis_data.redis_db.get(str(roomid)+"_double").decode()
            if int(now_double) == 1:
                status = 0
            else:
                status = 1
            redis_data.redis_db.rpush(str(roomid)+'_lord_list',str(seat))
            list_length = redis_data.redis_db.llen(str(roomid)+'_lord_list')
            
            print("push_list_length",list_length,seat)
            if int(seat) == 1:   redis_data.redis_db.set(str(roomid)+'_ask_rob','100')
            elif int(seat) == 2: redis_data.redis_db.set(str(roomid)+'_ask_rob','010')
            elif int(seat) == 3: redis_data.redis_db.set(str(roomid)+'_ask_rob','001')
            emit('server_response',jsonify(type = 29,ask_or_rob_type = ask_or_rob_type(roomid),ask_or_rob_type_next = ask_or_rob_type_next(ask,rob,judge_status(roomid)),next_seat = lordevent.find_next_seat(int(seat)),now_seat = seat,rob = int(rob),ask = int(ask)).data.decode(),room =roomid)
        if int(rob) == 0 and int(ask) == 0:
            emit('server_response',jsonify(type = 29,ask_or_rob_type = ask_or_rob_type(roomid),ask_or_rob_type_next = ask_or_rob_type_next(ask,rob,judge_status(roomid)),next_seat = lordevent.find_next_seat(int(seat)),now_seat = seat,rob = int(rob),ask = int(ask)).data.decode(),room = roomid)
    elif int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) == 2:
        redis_data.count_value(str(roomid)+'_lord_rob_times')
        if int(rob) == 1 or int(ask) == 1:
            rob_lord_double(rob,roomid)
            print("------------------========================",redis_data.count_value(str(roomid)+"_ask_or_rob_times"))

            now_double = redis_data.redis_db.get(str(roomid)+"_double").decode()
            if int(now_double) == 1:
                status = 0
            else:
                status = 1

            redis_data.redis_db.rpush(str(roomid)+'_lord_list',str(seat))
            list_length = redis_data.redis_db.llen(str(roomid)+'_lord_list')
            
            print("push_list_length",list_length,seat)
            if int(seat) == 1:   redis_data.redis_db.set(str(roomid)+'_ask_rob','100')
            elif int(seat) == 2: redis_data.redis_db.set(str(roomid)+'_ask_rob','010')
            elif int(seat) == 3: redis_data.redis_db.set(str(roomid)+'_ask_rob','001')
           
        
        list_length = redis_data.redis_db.llen(str(roomid)+'_lord_list')

        if int(list_length) == 2:
            emit('server_response',jsonify(type = 30).data.decode(),room = lordevent.find_seat_fit_account(redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[-1].decode(),roomid))
        else:
            print("===================",redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1])
            print("===================",redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1].decode())
            print("--------------------",lordevent.find_seat_fit_account(redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1].decode(),roomid))
            print("--------------------",lordevent.find_seat_fit_account(redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1],roomid))

            emit('server_response',jsonify(type = 29,ask_or_rob_type = ask_or_rob_type(roomid),ask_or_rob_type_next = ask_or_rob_type_next(ask,rob,judge_status(roomid)),next_seat = redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1].decode(),now_seat = seat,rob = int(rob),ask = int(ask)).data.decode(),room = roomid)
    elif int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) == 3:
        emit('server_response',jsonify(type = 29,ask_or_rob_type = ask_or_rob_type(roomid),ask_or_rob_type_next = ask_or_rob_type_next(ask,rob,judge_status(roomid)),next_seat = 0,now_seat = seat,rob = int(rob),ask = int(ask)).data.decode(),room = roomid)
        if int(rob) == 1 or int(ask) == 1:
            rob_lord_double(rob,roomid)

            print("------------------========================",redis_data.count_value(str(roomid)+"_ask_or_rob_times"))
            redis_data.redis_db.rpush(str(roomid)+'_lord_list',str(seat))
            if int(seat) == 1:   redis_data.redis_db.set(str(roomid)+'_ask_rob','100')
            elif int(seat) == 2: redis_data.redis_db.set(str(roomid)+'_ask_rob','010')
            elif int(seat) == 3: redis_data.redis_db.set(str(roomid)+'_ask_rob','001')
        if redis_data.redis_db.get(str(roomid)+'_ask_rob').decode() == '100':
            emit('server_response',jsonify(type = 32,lordseat = 1).data.decode(),room = roomid)
            return 1
        elif redis_data.redis_db.get(str(roomid)+'_ask_rob').decode() == '010':
            emit('server_response',jsonify(type = 32,lordseat = 2).data.decode(),room = roomid)
            return 2
        elif redis_data.redis_db.get(str(roomid)+'_ask_rob').decode() == '001':
            emit('server_response',jsonify(type = 32,lordseat = 3).data.decode(),room = roomid)
            return 3

def judge_status(roomid):
    times = redis_data.redis_db.get(str(roomid)+"_ask_or_rob_times").decode()
    if int(times) == 0:
        return 0
    else:
        return 1
def ask_or_rob_type(roomid):
    times = redis_data.redis_db.get(str(roomid)+"_ask_or_rob_times").decode()
    print("================",times)
    if int(times) == 0 or int(times) == 1:
        return 0
    else :
        return 1
def ask_or_rob_type_next(ask,rob,status):
    if int(ask) == 0 and int(rob) == 0 and int(status) == 0:
        return 0#叫地主状态
    elif  int(ask) == 0 and int(rob) == 0 and int(status) == 1:
        return 1 
    elif  int(ask) == 0 and int(rob) == 1 and int(status) == 1:
        return 1
    elif  int(ask) == 1 and int(rob) == 0 and int(status) == 0:
        return 1
    elif  int(ask) == 1 and int(rob) == 0 and int(status) == 1:
        return 1
    else:
        return 1


def rob_lord_double(rob,roomid):
    if int(rob) == 1:
        redis_data.count_value(str(roomid)+"_double")
        now_double = redis_data.redis_db.get(str(roomid)+"_double").decode()
        emit('server_response',jsonify(type = 31,now_double = int(now_double)).data.decode(),room = roomid)