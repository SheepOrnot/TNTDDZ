import threading
import random


room_id = 1

class Player(threading.local):
    def __init__(self):
        self.handcards = 0
        self.lord = 0
        self.account = ""
        self.double = 0
        self.handcards_num = 0
        self.seat = 0
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
class Accountseat(threading.local):
    def __init__(self,account,seat):
        self.account = account
        self.seat = seat


class BattleStatus(threading.local):
    def __init__(self):
        global room_id
        self.room_id = room_id
        self.room_count = 0
        self.player_1 = Player()

        self.player_2 = Player()

        self.player_3 = Player()

        self.account_list = [Accountseat("",0),Accountseat("",0),Accountseat("",0)]
        self.room_status = 0 #房间当前状态号码，暂且定义1为游戏已经开始，0为游戏没有开始

    def set_account_list(self,account,seat):
        accountseat = Accountseat(account,seat)
        if accountseat not in self.account_list:
            
            self.account_list[int(seat)-1] = accountseat
    def find_seat(self,account):
        for i in range(0,3):
            if self.account_list[i].account == account:
                return self.account_list[i].seat
        
    def del_account_list(self,account,seat):
        accountseat = Accountseat(account,seat)
        self.account_list.remove(accountseat)

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
        return {'roomid':self.room_id,                              'player_1_account':self.player_1.account,
                'player_2_account':self.player_2.account,           'player_3_account':self.player_3.account,
                'player_1_handcards':self.player_1.handcards,       'player_2_handcards':self.player_2.handcards,
                'player_3_handcards':self.player_3.handcards,       'room_status':self.room_status,
                'player_1_lord':self.player_1.lord,                 'player_2_lord':self.player_2.lord,
                'player_3_lord':self.player_3.lord,                 'room_status':self.room_status,
                'player_1_leavetimes':self.player_1.leaveroomtimes, 'player_2_leavetimes':self.player_2.leaveroomtimes,
                'player_3_leavetimes':self.player_3.leaveroomtimes, 'room_count':self.room_count,
                'player_1_seat':self.player_1.seat,                 'player_2_seat':self.player_2.seat,
                'player_3_seat':self.player_3.seat
                }
    def get_battle_status(self,battle_status):

        self.player_1.account = battle_status.get("player_1_account")
        self.player_2.account = battle_status.get("player_2_account")
        self.player_3.account = battle_status.get("player_3_account")
        self.player_1.handcards = battle_status.get("player_1_handcards")
        self.player_2.handcards = battle_status.get("player_2_handcards")
        self.player_3.handcards = battle_status.get("player_3_handcards")
        self.room_status = battle_status.get("room_status")
        self.player_1.lord = battle_status.get("player_1_lord")
        self.player_2.lord = battle_status.get("player_2_lord")
        self.player_3.lord = battle_status.get("player_3_lord")
        self.player_1.leaveroomtimes = battle_status.get("player_1_leavetimes")
        self.player_2.leaveroomtimes = battle_status.get("player_2_leavetimes")
        self.player_3.leaveroomtimes = battle_status.get("player_3_leavetimes")
        self.room_count = battle_status.get("room_count")
        self.player_1.seat = battle_status.get("player_1_seat")
        self.player_2.seat = battle_status.get("player_2_seat")
        self.player_3.seat = battle_status.get("player_3_seat")
    def find_lord_account(self):
        if self.player_1.lord == 1:
            return self.player_1.account
        elif self.player_2.lord == 1:
            return self.player_2.account
        elif self.player_3.lord == 1:
            return self.player_3.account
    def find_handcards(self,seat):
        if int(seat) == 1:
            return self.player_1.handcards
        elif int(seat) == 2:
            return self.player_2.handcards
        elif int(seat) == 3:
            return self.player_3.handcards
    def renew_handcards(self,seat,updated_handcards):
        if int(seat) == 1:
            self.player_1.handcards = updated_handcards
        elif int(seat) == 2:
            self.player_2.handcards = updated_handcards
        elif int(seat) == 3:
            self.player_3.handcards = updated_handcards

class ReadyPlayer(threading.local):
    def __init__(self):
        self.num = 0
        self.account = []



class HandCards(threading.local):
    def __init__(self):
        self.all_cards = list(range(1,55))
        self.player_1_cards = []
        self.player_2_cards = []
        self.player_3_cards = []
        self.lord_cards = []
    def wash_cards(self):
        
        random.shuffle(self.all_cards)
        self.player_1_cards = self.all_cards[:17]
            
        self.all_cards = self.all_cards[17:]
        self.player_2_cards = self.all_cards[:17]
        self.all_cards = self.all_cards[17:]
        self.player_3_cards = self.all_cards[:17]
        self.all_cards = self.all_cards[17:]
        self.lord_cards = self.all_cards
    