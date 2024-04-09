#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#include <map>
#include <functional>
#include <sio_client.h>
#include <sio_message.h>
#include <sio_socket.h>
#include <random>

#include <mutex>
#include <memory>
#include <thread>

#include <queue>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32

// 定义函数指针类型
typedef void (*PluginFuncPtr)();

const std::string SERVER_IP = "127.0.0.1";
const std::string SERVER_PORT = "22222";

enum class WIDGET_ARG_TYPE {
    ACCOUNT = 1,
    PLAYER = 2,
    CARD = 3,
    ROOM = 4,
    STATUS = 5, //server -> widget
    VERIFY = 6, //widget -> server
    GAME_START
};
enum class ACCOUNT_OPCODE {
    LOGIN = 1,
    REGISTER_MAIL = 2,
    REGISTER = 3,
    FORGET_PASSWORD_MAIL = 4,
    FORGET_PASSWORD = 5,
    REGISTER_MAIL_CODE_VERIFY = 6,
    FORGET_PASSWORD_MAIL_CODE_VERIFY = 7
};
enum class MESSAGE_TYPE {
    ACCOUNT = 1,
    PLAYER = 2,
    CARD = 3,
    ROOM = 4,
    STATUS = 5,
    VERIFY = 6,
    MessageRoomVerifyStatus = 7,
    GAME_START = 8,
    GAME_END = 9
};
enum class VERIFY_TYPE {
    LOGIN,
    REGISTER,
    FORGET_PASSWORD,
    REGISTER_MAIL,
    FORGET_PASSWORD_MAIL,
    CREATE_ROOM,
    JOIN_ROOM,
    LEAVE_ROOM,
    READY
};
enum class NETWORK
{
    LOGIN = 1,
    REGISTER = 2,
    FORGET_PASSWORD = 3,
    CREATE_ROOM = 4,
    JOIN_ROOM = 5,
    LEAVE_ROOM = 6,
    READY = 7,
    SEND_CARD = 8,
    REGISTER_MAIL_CODE_VERIFY = 9,
    FORGET_PASSWORD_MAIL_CODE_VERIFY = 10
};
enum class CARD_OPCODE
{
    OUTCARD
};
enum class PLAYER_OPCODE
{
    ENTER,
    CREATE_ROOM,
    JOIN_ROOM,
    LEAVE_ROOM,
    READY,
    LANDLORD,
    PLAY
};
#endif // COMMON_H
