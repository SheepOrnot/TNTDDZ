#ifndef MESSAGEPACKAGE_H
#define MESSAGEPACKAGE_H


#include "common.h"

class Message
{
public:
    Message(MESSAGE_TYPE _message_type, int _singlemode = 0) : message_type(_message_type), singlemode(_singlemode) {};
    MESSAGE_TYPE message_type;
    int singlemode;
};
class MessageAccount : public Message
{
public:
    MessageAccount(ACCOUNT_OPCODE _opcode, std::string _mail, std::string _accout, std::string _password, std::string _username, std::string _code)
        : Message(MESSAGE_TYPE::ACCOUNT),
        opcode(_opcode),
        mail(_mail),
        accout(_accout),
        password(_password),
        code(_code),
        username(_username)
        {};
    ACCOUNT_OPCODE opcode;
    std::string mail;
    std::string accout;
    std::string password;
    std::string code;
    std::string username;
};
class MessagePlayer : public Message
{
public:
    MessagePlayer(PLAYER_OPCODE _opcode, int _pos, int _profileindex, int _beannum, std::string _account, std::string _roomid, int _iscall = 0, int _singlemode = 0)
        : Message(MESSAGE_TYPE::PLAYER, _singlemode),
        opcode(_opcode),
        pos(_pos),
        profileindex(_profileindex),
        beannum(_beannum),
        account(_account),
        roomid(_roomid),
        iscall(_iscall)
    {}

    PLAYER_OPCODE opcode;
    int pos;
    int profileindex;
    int beannum;
    int iscall;
    std::string account;
    std::string roomid;
};
class MessageCard : public Message
{
public:
    MessageCard(CARD_OPCODE _opcode, int _pos, int _leftcards, int _cardtype, int _point, int _succ, std::bitset<54> _OutCard, std::bitset<54> _HandCard, int _singlemode)
        : Message(MESSAGE_TYPE::CARD, _singlemode),
        opcode(_opcode),
        pos(_pos),
        leftcards(_leftcards),
        cardtype(_cardtype),
        point(_point),
        succ(_succ),
        OutCard(_OutCard),
        HandCard(_HandCard)
    {}
    CARD_OPCODE opcode;
    int pos;
    int point;
    int succ;
    int leftcards;
    int cardtype;
    std::bitset<54> OutCard;
    std::bitset<54> HandCard;
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

class MessageGameStart : public Message
{
public:
    MessageGameStart() : Message(MESSAGE_TYPE::GAME_START) {};
};

class MessageGameEnd : public Message
{
public:
    MessageGameEnd() : Message(MESSAGE_TYPE::GAME_END) {};
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
