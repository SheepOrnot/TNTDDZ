import eventlet

def interrupt_sleep(i):
    # 创建一个倒计时器，设置超时时间为5秒
    timer = eventlet.Timeout(5)
    try:
        while True:
            # 执行一些操作...

            # 检查是否需要中断 sleep
            if i ==1 :
                # 取消倒计时器
                timer.cancel()
                break

            # 继续执行其他逻辑...
            print(111111)
            eventlet.sleep(1)  # 休眠1秒
    except eventlet.Timeout:
        # 超时处理
        print("Timeout occurred")
    finally:
        # 清理资源
        timer.cancel()

# 调用中断 sleep 的函数
mail = input()
print(server.Findaccount(str(mail)))
print(server.FindPeas('00000000000'))
print(server.FindUsername('00000000000'))
