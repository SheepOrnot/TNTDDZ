#ifndef COMMON_H
#define COMMON_H

#include <boost/beast.hpp>
#include <boost/json.hpp>
//#include <boost/json/src.hpp>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>

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
    GAME_START,
    GAME_OVER,
    NETWORK
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
    GAME_END = 9,
    NETWORK
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
    READY,
    ASK_OR_ROB,
    LORD_DOUBLE,
    MUST_ROB,
    LORD_CARD_BROADCAST,
    LORD_CARD_UPDATE,
    CALL_DOUBLE,
    PLAYER_IS_DOUBLE,
    PLAYER_NOT_DOUBLE,
    CALL_OUTCARD,
    OUTCARD_UPDATE,
    GAMEEND,
    SENDCARD,
    PLAYER_INFO
};
enum class NETWORK
{
    LOGIN = 1,
    REGISTER = 2,
    FORGET_PASSWORD = 3,
    CREATE_ROOM = 4,
    JOIN_ROOM = 5,
    REJOIN = 8,
    REGISTER_MAIL_CODE_VERIFY = 9,
    FORGET_PASSWORD_MAIL_CODE_VERIFY = 10,
    READY = 11,
    SENDCARD = 12,
    LORD_CARD_BROADCAST = 13,
    CALL_DOUBLE = 14,
    PLAYER_DOUBLE = 16,
    GAMEEND = 18,
    OUTCARD_UPDATE = 22,
    LEAVE_ROOM = 28,
    ASK_OR_ROB = 29,
    MUST_ROB = 30,
    LORD_DOUBLE = 31,
    PLAYER_INFO = 33,
    CALL_OUTCARD = 34,
    LORD_CARD_UPDATE = 35,
    DOUBLE,
    OUTPUT_HANDCARDS,
    BIGGER_CARDS,
    TIMEOUT
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
    PLAY,
    DOUBLE,

};
#endif // COMMON_H
