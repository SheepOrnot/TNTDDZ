#ifndef ROBOT_H
#define ROBOT_H

#include "common.h"
#include "cardprocess.h"

static std::random_device rd;
static std::mt19937 gen;

class robot
{
public:
    robot(std::string _name = "");
    void setname(std::string _name) {name = _name;}
    static void init(){gen.seed(rd());};
    std::pair<std::bitset<54>, CardTypeStruct> OutCardAction(CardTypeStruct PreOutCardType, int mustOut);  //return CardAction;
    void sethandcard(std::bitset<54> _handcard);
    std::bitset<54> showhandcard(){return handcard;}
    int GetlandlordAction();

    static void sleepcp(int milliseconds) // 跨平台 sleep 函数
    {
#ifdef _WIN32
        Sleep(milliseconds);
#else
        usleep(milliseconds * 1000);
#endif // _WIN32
    }
private:
    std::string name;
    std::bitset<54> handcard;

    std::string ANTI_index = "3456789TJQKA2BR";
    int index(char c);
    void pick_chain(std::vector<std::string> *v,std::string &hand,int count,int lim);
    std::string COMBINE_CARD(std::string hand);
    std::string BitsetTOString(std::bitset<54> _card);
};

#endif // ROBOT_H