import socketio

# 创建SocketIO实例
sio = socketio.Client()

@sio.event
def create_room():
    print('已连接到服务器')

@sio.on('server_response')
def on_server_response(data):
    print('收到服务器响应:', data)

@sio.event
def leave_room():
    print('已断开与服务器的连接')

# 连接到服务器
sio.connect('http://127.0.0.1:22222')



#发送JSON数据到服务器
# print("输入1创建房间，输入2加入房间")
# select = input()
# print("select",select)


# elif select  == 2:
print("加入房间")
json_data_join = '{\"account\":\"00000000003\",\"roomid\":\"1\"}'
sio.emit('join_room', json_data_join)    

# print("离开房间")
# json_data_leave = '{\"account\":\"00000000002\",\"roomid\":\"1\"}'
# sio.emit('leave_room',json_data_leave)

json_data_ready = '{\"account\":\"00000000003\"}'
sio.emit('ready',json_data_ready)
sio.wait()
# 等待连接关闭
