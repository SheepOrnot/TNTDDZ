功能一：创建房间功能
    客户端传出json包
        json包格式如下
        '{\"account\":\"00000000000\"}'
    服务器获取json包后，取得其中account数据，将其和roomid一起存入redis_db数据库中，roomid是全局变量（这点有待考究，因为服务器是多线程使用，可能会出现线程之间的冲突问题，但是roomid这个全局变量确实是需要多线程之间共同使用的）我们将roomid作为房间号码，让触发的客户端加入其中，随后给客户端一个返回的信号告知客户端已经成功加入以及其加入的roomid。
功能二：加入房间功能
    客户端传出加入房间的json包
        格式如下：
        '{\"account\":\"00000000001\",\"roomid\":\"1\"}'
    包含加入的account以及要加入房间的roomid
    首先要检查目标房间是否存在，为此我们首先要遍历redis数据库，看是否已经创建好了房间，如果不存在，那么返回客户端一个寻找的房间不存在的信号，为此我使用了Finding来辨别，若成功找到房间，Finding会设置为True，反之则是False
    还要检查目标房间的当前的人数，同样遍历的同时使用count计数，若遍历结果大于等于三代表当前房间已经满员，无法加入，同样返回客户端一个信号
    可能出现的问题：
    在初步测试中没有验证服务器和客户端是否实现点对点的信息传输，我怀疑是没有实现，对于房间不存在和人员已经满了，现阶段服务器应该是以广播的形式进行回复，后续如果真的出现问题，我打算使用客户端的account作为room，来进行点对点的信息传输。
    在满足了搜索房间存在和房间未满的条件下，可以成功加入房间，将json中的accout和roomid存入redis中，并使用join_room（）函数将连接的客户端加入到roomid的房间中去，随后返回加入房间成功的信息。（这个目前也应该是广播的形式）
功能三：离开房间功能
    客户端传入json包
        格式如下:
        '{\"account\":\"00000000002\",\"roomid\":\"1\"}'
    从redis中删除account对应的键值对，调用leave_room函数，使之离开roomid的房间，随后返回离开房间成功的信号给客户端
功能四：准备功能
    这个功能需要三个客户端进行
    三个客户端分别向服务器发送一个json包
    格式如下
        '{\"account\":\"00000000002\"}'    
    为了记录连接客户端的数量和当前已经准备的客户端，在这里使用了一个线性局部变量的技术，用于规避多线程之间的数据冲突，一个线程用于服务三个客户端，线性局部变量只是为了这个线程服务，线程和线程之间线性局部变量互相不会影响，用    ready_player.account这个列表来记录当前已经准备的客户端，
    ready_player.num这个变量来记录当前准备客户端的个数，当ready_player.num==3时候向房间内部的三个客户端发出所有玩家都已经准备的信号
功能五：发牌
    发牌功能目前的计划是在ready函数中进行实现，当服务器收到客户端的准备信号的数量达到三时候，直接先向三个客户端发送全体玩家都已经准备的消息，随后进行发牌
功能六：叫地主
    为了叫地主的开始的随机性，计划在叫地主的前一步中服务器回复给客户端的json中添加一个决定谁先开始叫地主的key，目前拟定叫“firstlord”，这个key为1的时候，就由这台客户端向服务器发出叫地主请求，然后对于叫地主请求，准备一个first_lord接口
    叫地主，叫地主第一个人
            下一个叫地主，线性局部变量
            room
            {
                room_id
                room_count
                player
                {   
                    handcards,
                    lord,
                    next_player,
                    previous_player,
                    account，
                    double
                }    
            }



class Player(threading.local):
    def __init__(self):
        self.handcards = ""
        self.lord = 0
        self.account = ""
        self.double = 0
        self.next_player  = None
        self.previous_player = None
        self.handcards_num = 0
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

class BattleStatus:
    def __init__(self):
        global room_id
        self.room_id = room_id
        self.room_count = 0
        self.player_1 = None
        self.player_2 = None
        self.player_3 = None
        self.account_list = []
        self.room_status = 0 #房间当前状态号码，暂且定义1为游戏已经开始，0为游戏没有开始
    def set_account_list(self,account):
        self.account_list.append(account)
    def someone_join_room(self):
        self.room_count += 1
    def someone_leave_room(self):
        self.room_count -= 1

    {
        roomid:room_id
        
    }

游戏是否开局
游戏阶段
时钟
<!-- 房间满了没告诉我
房间不存在没告诉我 -->
{
    account
}