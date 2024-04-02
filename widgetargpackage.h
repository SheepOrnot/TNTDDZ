#ifndef WIDGETARGPACKAGE_H
#define WIDGETARGPACKAGE_H


#include "common.h"
#include <string>
#include <vector>
#include <bitset>

class WidgetArg
{
public:
    WidgetArg(WIDGET_ARG_TYPE _widget_arg_type)
        : widget_arg_type(_widget_arg_type)
    {}
    WIDGET_ARG_TYPE widget_arg_type;
};

class WidgetArgAccount : public WidgetArg
{
public:
    WidgetArgAccount(ACCOUNT_OPCODE _opcode, std::string _mail, std::string _accout, std::string _password, std::string _code = "")
        : WidgetArg(WIDGET_ARG_TYPE::ACCOUNT),
        opcode(_opcode),
        mail(_mail),
        accout(_accout),
        password(_password),
        code(_code)
    {}
    ACCOUNT_OPCODE opcode;
    std::string mail;
    std::string accout;
    std::string password;
    std::string code = "";
};

class WidgetArgPlayer : public WidgetArg
{
public:
    WidgetArgPlayer(int _opcode, int _addition_data)
        : WidgetArg(WIDGET_ARG_TYPE::PLAYER),
        opcode(_opcode),
        addition_data(_addition_data)
    {}

    int opcode;
    int addition_data;
};

class WidgetArgCard : public WidgetArg
{
public:
    WidgetArgCard(int _opcode, int _addition_data, std::bitset<54> _OutCard, std::bitset<54> _HandCard)
        : WidgetArg(WIDGET_ARG_TYPE::CARD),
        opcode(_opcode),
        addition_data(_addition_data),
        OutCard(_OutCard),
        HandCard(_HandCard)
    {}
    int opcode;
    int addition_data;
    std::bitset<54> OutCard;
    std::bitset<54> HandCard;
};

class WidgetArgRoom : public WidgetArg
{
public:
    WidgetArgRoom(ROOM_OPCODE _opcode, std::vector<int> _addition_data)
        : WidgetArg(WIDGET_ARG_TYPE::ROOM),
        opcode(_opcode),
        addition_data(_addition_data)
    {}

    ROOM_OPCODE opcode;
    std::vector<int> addition_data;
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
