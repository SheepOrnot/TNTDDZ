import redis
redis_db = redis.Redis(host='127.0.0.1', port=6379, db=0)
# 对特定值进行计数
def count_value(key):
    count = redis_db.incr(key)
    return count

def decrease_value(key):
    count = redis_db.decr(key)
    return count

def get_ask_lord_times(room_id):
    key = str(room_id)+"_ask_lord_times"
    return redis_db.get(key).decode()
