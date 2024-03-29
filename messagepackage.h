#ifndef MESSAGEPACKAGE_H
#define MESSAGEPACKAGE_H


#include "common.h"

class Message
{
public:
    Message(int _message_type) : message_type(_message_type) {};
    int message_type;
};
class MessageLogin : public Message
{
public:
    MessageLogin(std::string _mail, std::string _accout, std::string _password)
        : Message(1),
        mail(_mail),
        accout(_accout),
        password(_password)
        {};
    std::string mail;
    std::string accout;
    std::string password;
};
class MessageCard : public Message
{
public:
    MessageCard() : Message(2) {};
};
class MessagePlayer : public Message
{
public:
    MessagePlayer() : Message(3) {};
};
class MessageRoom : public Message
{
public:
    MessageRoom() : Message(4) {};
};
class MessageError : public Message
{
public:
    MessageError() : Message(5) {};
};

class MessageStatus : public Message
{
public:
    MessageStatus(int _success) : Message(6), success(_success) {};
    int success;
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
    int message_type;

    template<typename MessageType, typename... Args>
    void packMessage(Args&&... args)
    {
        MessageType* msg_ptr = new MessageType(std::forward<Args>(args)...);
        package = static_cast<void*>(msg_ptr);
        message_type = msg_ptr->message_type;
    }
};

#endif // MESSAGEPACKAGE_H
