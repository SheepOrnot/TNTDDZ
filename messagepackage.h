#ifndef MESSAGEPACKAGE_H
#define MESSAGEPACKAGE_H


#include "common.h"

class Message
{
public:
    Message(MESSAGE_TYPE _message_type) : message_type(_message_type) {};
    MESSAGE_TYPE message_type;
};
class MessageLogin : public Message
{
public:
    MessageLogin(LOGIN_OPCODE _opcode, std::string _mail, std::string _accout, std::string _password, std::string _code)
        : Message(MESSAGE_TYPE::LOGIN),
        opcode(_opcode),
        mail(_mail),
        accout(_accout),
        password(_password),
        code(_code)
        {};
    LOGIN_OPCODE opcode;
    std::string mail;
    std::string accout;
    std::string password;
    std::string code;
};
class MessagePlayer : public Message
{
public:
    MessagePlayer() : Message(MESSAGE_TYPE::PLAYER) {};
};
class MessageCard : public Message
{
public:
    MessageCard() : Message(MESSAGE_TYPE::CARD) {};
};
class MessageRoom : public Message
{
public:
    MessageRoom() : Message(MESSAGE_TYPE::ROOM) {};
};
class MessageStatus : public Message
{
public:
    MessageStatus() : Message(MESSAGE_TYPE::STATUS) {};
};

class MessageVerifyStatus : public Message
{
public:
    MessageVerifyStatus(VERIFY_TYPE _type, int _code) : Message(MESSAGE_TYPE::VERIFY), type(_type), code(_code) {};
    VERIFY_TYPE type;
    int code;
};

class MessagePackage
{
public:
    MessagePackage()
    {
        package = nullptr;
    }
    ~MessagePackage()
    {
        if(package) delete package;
    }
    void* package;
    MESSAGE_TYPE message_type;

    template<typename MessageType, typename... Args>
    void packMessage(Args&&... args)
    {
        MessageType* msg_ptr = new MessageType(std::forward<Args>(args)...);
        package = static_cast<void*>(msg_ptr);
        message_type = msg_ptr->message_type;
    }
};

#endif // MESSAGEPACKAGE_H
