#include "robot.h"

robot::robot()
{

}

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
        if(CardProcess::CardCheck_tiny(curCardType, PreOutCardType))
        {
            return action.action;
        }
    }
    return 0;
}

int robot::GetlandlordAction()
{
    std::random_device rd;
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 算法生成随机数引擎

    // 创建一个 uniform_int_distribution 对象，用于生成 0 或 1
    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(gen);
}
