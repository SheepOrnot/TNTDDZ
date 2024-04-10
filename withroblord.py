import redis_data
from flask_socketio import SocketIO, emit, disconnect, join_room, leave_room
from flask import jsonify
import lordevent
import battlestatus
import json
def decide_lord(account,roomid,lord,seat):
    battle_data = battlestatus.BattleStatus()
    key = str(roomid)+"_battle_data"
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    battle_data.get_battle_status(battle_status)
    
    if int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) < 3:
        redis_data.count_value(str(roomid)+'_lord_rob_times')
        if int(lord) == 1:
            print("int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode())",int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()))
            redis_data.redis_db.rpush(str(roomid)+'_lord_list',str(seat))
            #通知下一个玩家是否进行抢地主操作
            emit('server_response',jsonify(type = 'ask next one rob').data.decode(),room = battle_data.find_account(lordevent.find_next_seat(seat)))
        elif int(lord) == 0:
            #通知下一个玩家进行叫地主
            print("int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode())",int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()))
            emit('server_response',jsonify(type = 'emit next lord').data.decode(),room = battle_data.find_account(lordevent.find_next_seat(seat)))
    if int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) == 3:
        list_length = list_length = redis_data.redis_db.llen(str(roomid)+'_lord_list')
        print(list_length)
        redis_data.count_value(str(roomid)+'_lord_rob_times')
        if int(list_length) == 2:
            print(str(redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)))
            print(str((redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1].decode().zfill(11))))
            emit('server_response',jsonify(type = 'head must',must = 1).data.decode(),room = lordevent.find_seat_fit_account(redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1].decode(),roomid))
        

            
def decide_rob(account,roomid,rob,seat):
    battle_data = battlestatus.BattleStatus()
    key = str(roomid)+"_battle_data"
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status)
    battle_data.get_battle_status(battle_status)

    if int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) < 3:
        redis_data.count_value(str(roomid)+'_lord_rob_times')
        if int(rob) == 1:
            redis_data.redis_db.rpush(str(roomid)+'_lord_list',str(seat))
            emit('server_response',jsonify(type = 'ask next one rob').data.decode(),room = battle_data.find_account(lordevent.find_next_seat(seat)))
        elif int(rob) == 0:
            emit('server_response',jsonify(type = 'ask next one rob').data.decode(),room = battle_data.find_account(lordevent.find_next_seat(seat)))
    elif int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) == 4:
        emit('server_response',jsonify(type = 'lord finish',lord = seat).data.decode(),room = roomid)
    
    if int(redis_data.redis_db.get(str(roomid)+'_lord_rob_times').decode()) == 3:
        redis_data.count_value(str(roomid)+'_lord_rob_times')
        emit('server_response',jsonify(type = 'send to head').data.decode(),room = lordevent.find_seat_fit_account(redis_data.redis_db.lrange(str(roomid)+'_lord_list',0,-1)[1].decode(),roomid))
