#ifndef WIDGETARGPACKAGE_H
#define WIDGETARGPACKAGE_H



#include <string>
#include <vector>
#include <bitset>

class WidgetArg
{
public:
    WidgetArg(int _widget_arg_type)
        : widget_arg_type(_widget_arg_type)
    {}
    int widget_arg_type;
};

class WidgetArgLogin : public WidgetArg
{
public:
    WidgetArgLogin(std::string _mail, std::string _accout, std::string _password, std::string _code = "")
        : WidgetArg(1),
        mail(_mail),
        accout(_accout),
        password(_password),
        code(_code)
    {}

    std::string mail;
    std::string accout;
    std::string password;
    std::string code = "";
};

class WidgetArgPlayer : public WidgetArg
{
public:
    WidgetArgPlayer(int _opcode, int _addition_data)
        : WidgetArg(2),
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
        : WidgetArg(3),
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
    WidgetArgRoom(int _opcode, std::vector<int> _addition_data)
        : WidgetArg(4),
        opcode(_opcode),
        addition_data(_addition_data)
    {}

    int opcode;
    std::vector<int> addition_data;
};

class WidgetArgStatus : public WidgetArg
{
public:
    WidgetArgStatus(int _opcode, int _status)
        : WidgetArg(5),
        opcode(_opcode),
        status(_status)
    {}
    int opcode;
    int status;
};


class WidgetArgPackage
{
public:
    WidgetArgPackage(){}
    void* package;
    int widget_arg_type;

    template<typename WidgetArgType, typename... Args>
    void packMessage(Args&&... args)
    {
        WidgetArgType* arg_ptr = new WidgetArgType(std::forward<Args>(args)...);
        package = static_cast<void*>(arg_ptr);
        widget_arg_type = arg_ptr->widget_arg_type;
    }
};


#endif // WIDGETARGPACKAGE_H
