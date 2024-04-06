import time
import lordevent
from flask import jsonify
from flask_socketio import emit

def timeout_handler(seat,room_id):
    data_account = lordevent.find_seat_fit_account(lordevent.find_next_seat(seat),str(room_id))
    emit('server_response',jsonify(type = 100).data.decode(),room = data_account)
