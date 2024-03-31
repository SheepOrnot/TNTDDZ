import json
room_id = 1
class BattleStatus():
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
    def inform_room_status(self,relink_account):
        situation_new = self.find_situation(relink_account)

        print("--------------------",situation_new)
        print("-----------------",self.account_list)
        relink_player = Player()
        if situation_new == 1:
            relink_player = self.player_1
        elif situation_new == 2:
            relink_player = self.player_2
        elif situation_new == 3:
            relink_player = self.player_3
        print("self.room_id",self.room_id)
        print("relink_player.handcards",relink_player.handcards)
        emit('server_response',jsonify(roomid = self.room_id,situation = situation_new,
                                       handcards = relink_player.handcards,
                                       lord = relink_player.lord,double = relink_player.double).data.decode(),room = relink_account)
        emit('server_response',jsonify(roomid = self.room_id,situation = situation_new,
                                       lord = relink_player.lord,double = relink_player.double).data.decode(),room = self.room_id)
    def to_dict(self):
        return {'roomid':self.room_id,'player_1':self.player_1.}
def Player_to_json(data):
    json_string = json.dumps(data.__dict__)
    return json_string
def Battledata_to_json(data):

person = BattleStatus()
print(Player_to_json(person))