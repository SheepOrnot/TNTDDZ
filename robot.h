#ifndef ROBOT_H
#define ROBOT_H

#include "common.h"
#include "messagecenter.h"
#include "cardprocess.h"

class robot
{
public:
    robot();
    std::bitset<54> OutCardAction(CardTypeStruct PreOutCardType);  //return CardAction;
    void sethandcard(std::bitset<54> _handcard);
    int GetlandlordAction();
private:
    std::bitset<54> handcard;
};

#endif // ROBOT_H
