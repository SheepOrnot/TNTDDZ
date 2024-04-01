import socketio
from time import sleep

class player():
    def __init__(self, account) -> None:
        self.sio = socketio.Client()
        self.account = account

        @self.sio.on('server_response')
        def on_server_response(data):
            print(f'{account} 收到服务器响应: {data}')

        self.sio.connect('http://127.0.0.1:22222')

    def create_room(self):
        json_data = '{\"account\":\"' + self.account + '\"}'
        self.sio.emit('create_room', json_data)

    def join_room(self, roomid):
        json_data = '{\"account\":\"' + self.account + '\",\"roomid\":\"' + str(roomid) + '\"}'
        self.sio.emit('join_room', json_data)

    def leave_room(self, roomid):
        json_data = '{\"account\":\"' + self.account + '\",\"roomid\":\"' + str(roomid) + '\"}'
        self.sio.emit('leave_room', json_data)

    def ready(self, roomid):
        json_data = '{\"account\":\"' + self.account + '\",\"roomid\":\"' + str(roomid) + '\"}'
        self.sio.emit('ready', json_data)

testsio = socketio.Client()
testsio.connect('http://127.0.0.1:22222')

sleep(1)
print("test connect done")

# 玩家连接    
player_list = [0]
for i in range(6):
    player_list.append(player("0000000000" + str(i)))

print("p1-p6 已连接")
sleep(1)


# 创建房间
player_list[1].create_room()
player_list[4].create_room()

print("p1,p4 创建房间")
sleep(3)


# 加入房间
player_list[2].join_room(1)
player_list[3].join_room(1)
player_list[5].join_room(2)
player_list[6].join_room(2)

print("p2,p3,p5,p6 加入房间")
sleep(3)

# 准备
player_list[1].ready(1)
player_list[2].ready(1)
player_list[3].ready(1)
player_list[4].ready(2)
player_list[5].ready(2)
player_list[6].ready(2)

print("p1-p6 准备")
sleep(3)

# 断线重连
player_list[1].leave_room(1)
sleep(1)
player_list[1].join_room(1)

'''
player_list[4].leave_room(2)
sleep(1)
player_list[4].join_room(2)

player_list[5].leave_room(2)
sleep(1)
player_list[5].join_room(2)
'''

print("p1 断线重连")
sleep(1)