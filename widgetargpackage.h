#ifndef WIDGETARGPACKAGE_H
#define WIDGETARGPACKAGE_H


#include "common.h"
#include <string>
#include <vector>
#include <bitset>

class WidgetArg
{
public:
    WidgetArg(WIDGET_ARG_TYPE _widget_arg_type, int _singlemode = 0)
        : widget_arg_type(_widget_arg_type),
        singlemode(_singlemode)
    {}
    WIDGET_ARG_TYPE widget_arg_type;
    int singlemode;
};

class WidgetArgAccount : public WidgetArg
{
public:
    WidgetArgAccount(ACCOUNT_OPCODE _opcode, std::string _mail, std::string _accout, std::string _password, std::string _username, std::string _code = "")
        : WidgetArg(WIDGET_ARG_TYPE::ACCOUNT),
        opcode(_opcode),
        mail(_mail),
        accout(_accout),
        password(_password),
        code(_code),
        username(_username)
    {}
    ACCOUNT_OPCODE opcode;
    std::string mail;
    std::string accout;
    std::string password;
    std::string code = "";
    std::string username;
};

class WidgetArgPlayer : public WidgetArg
{
public:
    WidgetArgPlayer(PLAYER_OPCODE _opcode, int _pos, int _profileindex, int _beannum, std::string _username, std::string _account, std::string _roomid, int _iscall = 0, int _singlemode = 0)
        : WidgetArg(WIDGET_ARG_TYPE::PLAYER, _singlemode),
        opcode(_opcode),
        pos(_pos),
        profileindex(_profileindex),
        beannum(_beannum),
        username(_username),
        account(_account),
        roomid(_roomid),
        iscall(_iscall)
    {}

    PLAYER_OPCODE opcode;
    int pos;
    int profileindex;
    int beannum;
    int iscall;
    std::string username;
    std::string account;
    std::string roomid;
};

class WidgetArgCard : public WidgetArg
{
public:
    WidgetArgCard(CARD_OPCODE _opcode, int _pos, int _leftcards, int _cardtype, int _point, int _succ, std::bitset<54> _OutCard, std::bitset<54> _HandCard, int _singlemode)
        : WidgetArg(WIDGET_ARG_TYPE::CARD, _singlemode),
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
    int leftcards;
    int cardtype;
    int point;
    int succ;
    std::bitset<54> OutCard;
    std::bitset<54> HandCard;
};

class WidgetArgStatus : public WidgetArg
{
public:
    WidgetArgStatus(WIDGET_ARG_TYPE _opcode, int _status)
        : WidgetArg(WIDGET_ARG_TYPE::STATUS),
        opcode(_opcode),
        status(_status)
    {}
    WIDGET_ARG_TYPE opcode;
    int status;
};

class WidgetArgStartGame : public WidgetArg
{
public:
    WidgetArgStartGame(std::string _identity1,std::string _identity2,std::string _identity3,std::bitset<54> _handcards,std::bitset<54> _finalcards)
        : WidgetArg(WIDGET_ARG_TYPE::GAME_START),
        identity1(_identity1),
        identity2(_identity2),
        identity3(_identity3),
        handcards(_handcards),
        finalcards(_finalcards)
    {}
    
    std::string identity1;
    std::string identity2;
    std::string identity3;

    std::bitset<54> handcards;
    std::bitset<54> finalcards;
};

class WidgetArgGameOver : public WidgetArg
{
public:
    WidgetArgGameOver(int _result, int _times, int _Score1, int _Score2, int _Score3) :
        WidgetArg(WIDGET_ARG_TYPE::GAME_OVER),
        result(_result),
        times(_times),
        Score1(_Score1),
        Score2(_Score2),
        Score3(_Score3)
    {}

    int result;
    int times;
    int Score1;
    int Score2;
    int Score3;
};

class WidgetArgNetWork : public WidgetArg
{
public:
    WidgetArgNetWork(NETWORK _type,std::string _account,std::string _roomid,int _seat,int _decision,long long _outputcards,long long _tablecards,int _canorcannot)
        : WidgetArg(WIDGET_ARG_TYPE::NETWORK),
        type(_type),
        account(_account),
        roomid(_roomid),
        seat(_seat),
        decision(_decision),
        outputcards(_outputcards),
        tablecards(_tablecards),
        canorcannot(_canorcannot)
    {};

    NETWORK type;
    std::string account;
    std::string roomid;
    int seat;
    int decision;
    long long outputcards;
    long long tablecards;
    int canorcannot;
};

class WidgetArgPlayerInfo : public WidgetArg
{
public:
    WidgetArgPlayerInfo(std::string _account,std::string _username,int _peas,int _diamond, int _profile)
        : WidgetArg(WIDGET_ARG_TYPE::PLAYER),
        account(_account),
        username(_username),
        peas(_peas),
        diamond(_diamond),
        profile(_profile)
        {};

    std::string account;
    std::string username;
    int peas;
    int diamond;
    int profile;
};


class WidgetArgPackage
{
public:
    WidgetArgPackage(){}
    void* package;
    WIDGET_ARG_TYPE widget_arg_type;

    template<typename WidgetArgType, typename... Args>
    void packMessage(Args&&... args)
    {
        WidgetArgType* arg_ptr = new WidgetArgType(std::forward<Args>(args)...);
        package = static_cast<void*>(arg_ptr);
        widget_arg_type = arg_ptr->widget_arg_type;
    }
};


#endif // WIDGETARGPACKAGE_H
