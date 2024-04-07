#ifndef ROBOT_H
#define ROBOT_H

#include "common.h"
#include "cardprocess.h"

class robot
{
public:
    robot();
    std::pair<std::bitset<54>, CardTypeStruct> OutCardAction(CardTypeStruct PreOutCardType);  //return CardAction;
    void sethandcard(std::bitset<54> _handcard);
    int GetlandlordAction();
private:
    std::bitset<54> handcard;
};

#endif // ROBOT_H
