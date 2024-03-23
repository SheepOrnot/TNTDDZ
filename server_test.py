from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your-secret-key'

socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

@socketio.on('connect')
def on_connect():
    print('有客户端连接到服务器')

@socketio.on('client_message')
def on_client_message(data):
    print('收到客户端消息:', data)
    emit('server_response', {'message': '服务器响应'})

@socketio.on('disconnect')
def on_disconnect():
    print('有客户端断开与服务器的连接')

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=22222,debug= True)