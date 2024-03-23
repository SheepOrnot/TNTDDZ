from flask import Flask, render_template
from flask_socketio import SocketIO, emit,send,join_room,leave_room
from flask import request

rooms = []
room_id = 0


app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret_key'
socketio = SocketIO()
socketio.init_app(app, cors_allowed_origins='*')
name_space = '/dcenter'


@socketio.on('create_room')
def create_room():
    data = request.get_json()
    host = data.get("username")
    host_id = data.get("account")
    global rooms
    global room_id
    rooms.append(room_id)
    room_id = room_id+1
    

@app.route('/push')
def push_once():
    # event_name = 'dcenter'
    # broadcasted_data = {'data': "test message!"}
    # socketio.emit(event_name, broadcasted_data, broadcast=False, namespace=name_space)
    return 'done!'

@socketio.on('connect', namespace=name_space)
def connected_msg():
    print('client connected.')

@socketio.on('disconnect', namespace=name_space)
def disconnect_msg():
    print('client disconnected.')


@socketio.on('my_event', namespace=name_space)
def mtest_message(message):
    print(message)
    emit('my_response',
         {'data': message['data'], 'count': 1})
    


if __name__ == '__main__':
    socketio.run(app, port=5000, debug=True)