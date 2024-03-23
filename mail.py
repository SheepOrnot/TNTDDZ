import random
import string
import redis
import random
import smtplib
from email.mime.multipart import MIMEMultipart
from email.header import Header
from email.mime.text import MIMEText


r = redis.Redis(host='localhost',port=6379,db=0)

def generate_verification_code():
    code = ''.join(random.choices(string.digits, k=6))
    return code

def store_verification_code(email, code):
    r.setex(email, 300, code)

def get_verification_code(email):
    code = r.get(email)
    return code.decode() if code else None


def write_email(user_name, to, code):
    """
    :param user_name: 发送者
    :param to: 接收者
    :return:
    """
    # 创建邮件对象
    email = MIMEMultipart()
    # 邮件的基础设置
    email['Subject'] = Header('斗地主验证码', 'utf-8').encode()
    email['To'] = to
    email['From'] = f'=?UTF-8?B?5Ya36ZSL56eR5oqA?= <{user_name}>'
    # 添加文本
    text = MIMEText('[冷锋科技]验证码：'+str(code)+'\n'+'您正在使用邮箱登录验证码注册/找回密码功能，该验证码五分钟内有效，请勿泄露给他人使用。', 'plain', 'utf-8')
    email.attach(text)
    return email


def send_email(user_name, pwd, message, to):
    """
    :param user_name: 发送者的用户名
    :param pwd: 密码
    :param message: 内容
    :param to: 发送给谁
    """
    # 连接邮件服务器 每个邮件的服务器地址不一样 这里使用163邮箱
    connect = smtplib.SMTP_SSL('smtp.163.com', 465)
    # 登陆
    connect.login(user_name, pwd)
    # 发送邮件
    connect.sendmail(user_name, to, message.as_string())
    # 关闭连接
    connect.quit()




