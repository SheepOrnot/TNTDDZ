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

// 定义函数指针类型
typedef void (*PluginFuncPtr)();

enum class WIDGET_ARG_TYPE {
    ACCOUNT = 1,
    PLAYER = 2,
    CARD = 3,
    ROOM = 4,
    STATUS = 5, //server -> widget
    VERIFY = 6  //widget -> server
};
enum class ACCOUNT_OPCODE {
    LOGIN = 1,
    REGISTER_MAIL = 2,
    REGISTER = 3,
    FORGET_PASSWORD_MAIL = 4,
    FORGET_PASSWORD = 5
};
enum class MESSAGE_TYPE {
    ACCOUNT = 1,
    PLAYER = 2,
    CARD = 3,
    ROOM = 4,
    STATUS = 5,
    VERIFY = 6,
};
enum class VERIFY_TYPE {
    LOGIN = 1,
    REGISTER = 2,
    FORGET_PASSWORD = 3
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
    SEND_CARD = 8
};
enum class ROOM_OPCODE {
    JOIN = 1
};

#endif // COMMON_H
