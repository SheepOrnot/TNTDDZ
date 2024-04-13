import transfercards
import redis_data
import battlestatus
import random
from flask import jsonify
import json
from time import sleep
from flask_socketio import SocketIO, emit, disconnect, join_room, leave_room
def decide_lord(data_lord,data_account,data_room_id,data_seat):
    if data_lord == 1:
        lord_cards = redis_data.redis_db.get(str(data_room_id)+"_lord_cards").decode()
        #生成地主牌，并修改地主数据
        print('lord_cards-=-=-=--------=-=-=-=-=-',data_account)
        lord_handcards =  change_handcards_data(data_account,data_room_id,data_seat)
        change_lord_data(data_account,data_room_id,lord_handcards)
        print("叫地主！！！！",lord_handcards)
        #广播地主牌
        broadcast_information(data_account,data_room_id,data_seat,int(lord_cards))
        #通知是否加倍
        sleep(3)
        emit('server_response',jsonify(type = 14).data.decode(),room = data_room_id)
        return 0 
    elif data_lord == 0:
        #通知下一名玩家叫地主
        print("下一名玩家的座位号：",find_next_seat(data_seat))
        emit('server_response',jsonify(type = 15).data.decode(),room = next_account(data_seat,data_room_id))
        return 0 

def next_account(data_seat,data_room_id):
    return find_seat_fit_account(find_next_seat(data_seat),data_room_id)


def find_next_seat(data_seat):
    if data_seat == 1:
        next_seat = 2
    elif data_seat == 2:
        next_seat = 3
    elif data_seat == 3:
        next_seat = 1
    return next_seat
def find_seat_fit_account(data_seat,data_room_id):

    key = str(data_room_id)+"_battle_data"
    print("key",key)
    battle_data = battlestatus.BattleStatus()
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status.decode('utf-8'))

    battle_data.player_1.account = battle_status.get("player_1_account")
    battle_data.player_2.account = battle_status.get("player_2_account")
    battle_data.player_3.account = battle_status.get("player_3_account")

    if int(data_seat) == 1:
        return battle_data.player_1.account
    elif int(data_seat) == 2:
        return battle_data.player_2.account
    elif int(data_seat) == 3:
        return battle_data.player_3.account
    
def broadcast_information(data_account,data_room_id,data_seat,data_lord_cards):

    emit('server_response',jsonify(type = 13,seat = data_seat,account =data_account,lord_cards = data_lord_cards).data.decode(),room = data_room_id)

def change_handcards_data(data_account,data_room_id,data_seat):
    print(str(data_room_id)+"_"+str(data_account)+"_player_"+str(data_seat)+"_handcards")
    handcards = int(redis_data.redis_db.get(str(data_room_id)+"_"+str(data_account)+"_player_"+str(data_seat)+"_handcards").decode())
    transfered_handcards = transfercards.transfer_int_to_str(handcards)

    lord_cards = redis_data.redis_db.get(str(data_room_id)+"_lord_cards").decode()
    transfered_lord_cards = transfercards.transfer_int_to_str(int(lord_cards))
    print(transfered_lord_cards)
    print(transfered_handcards)
    lord_handcards = int(transfercards.add_cards(transfered_handcards,transfered_lord_cards),2)

    redis_data.redis_db.set(str(data_room_id)+"_"+str(data_account)+"_player_"+str(data_seat)+"_handcards",lord_handcards)
    return lord_handcards

def change_lord_data(data_account,data_room_id,lord_handcards):

    key = data_room_id+"_battle_data"

    battle_data = battlestatus.BattleStatus()
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status.decode('utf-8'))

    battle_data.room_id = data_room_id
    battle_data.get_battle_status(battle_status)

    seat = find_fit_seat(data_account,battle_data.player_1.account,battle_data.player_2.account,battle_data.player_3.account)
    print("data_account",data_account)
    print("___+===+_+_+_+_",seat)
    if seat == 1:
        battle_data.player_1.handcards = lord_handcards
        battle_data.player_1.lord = 1
    elif seat == 2:
        battle_data.player_2.handcards = lord_handcards
        battle_data.player_2.lord = 1
    elif seat == 3:
        battle_data.player_3.handcards = lord_handcards
        battle_data.player_3.lord = 1
    print("lord_----------------",battle_data.player_1.lord)
    print("lord_----------------",battle_data.player_2.lord)
    print("lord_----------------",battle_data.player_3.lord)
    redis_data.redis_db.set(str(battle_data.room_id)+'_battle_data',json.dumps(battle_data.to_dict(),ensure_ascii=False))
    emit('server_response',jsonify(type = 35,handcards = lord_handcards).data.decode(),room = battle_data.find_lord_account())




def find_fit_seat(data_account,player_1_account,player_2_account,player_3_account):
    if data_account == player_1_account:
        seat = 1
    elif data_account == player_2_account:
        seat = 2
    elif data_account == player_3_account:
        seat = 3
    return seat

def random_lord(data_room_id):
    lord_seat = random.randint(1,3)
    key = data_room_id+"_battle_data"

    battle_data = battlestatus.BattleStatus()
    battle_status = redis_data.redis_db.get(key).decode()
    battle_status = json.loads(battle_status.decode('utf-8'))

    battle_data.room_id = data_room_id
    battle_data.get_battle_status(battle_status)
    print("------",lord_seat)
    print("------",battle_data.player_1.seat)
    if int(battle_data.player_1.seat) == lord_seat:
        data_account = battle_data.player_1.account
    elif int(battle_data.player_2.seat) == lord_seat:
        data_account = battle_data.player_2.account
    elif int(battle_data.player_3.seat) == lord_seat:
        data_account = battle_data.player_3.account
    
    lord_handcards =  change_handcards_data(data_account,data_room_id,lord_seat)
    print("lord_handcards",lord_handcards)
    print("data_room",data_room_id)
    change_lord_data(data_account,data_room_id,lord_handcards)
    lord_cards = redis_data.redis_db.get(str(data_room_id)+"_lord_cards").decode()
    broadcast_information(data_account,data_room_id,lord_seat,int(lord_cards))

