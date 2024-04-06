#include "robot.h"

robot::robot() {}

void robot::sethandcard(std::bitset<54> _handcard)
{
    handcard = _handcard;
}

std::bitset<54> robot::OutCardAction(CardTypeStruct PreOutCardType)
{
    ActionVector Action = CardProcess::EnumerateCardOutAction(handcard);
    for(auto& action : Action)
    {
        CardTypeStruct curCardType = {action.cardtype, action.point};
        if(CardCheck_tiny(PreOutCardType))
        {
            return action.action;
        }
    }
    return 0;
}

int robot::Getlandlord()
{
    return 1;
}