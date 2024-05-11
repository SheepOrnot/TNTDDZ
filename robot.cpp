#include "robot.h"

robot::robot(std::string _name)
{
    name = name;
}

void robot::sethandcard(std::bitset<54> _handcard)
{
    handcard = _handcard;
}

std::pair<std::bitset<54>, CardTypeStruct> robot::OutCardAction(CardTypeStruct PreOutCardType, int mustOut)
{
    std::cout << "Robot thinking..." << PreOutCardType.cardtype << " " << PreOutCardType.point << " " << PreOutCardType.succ << std::endl; std::flush(std::cout);
    
    ActionVector Action = CardProcess::EnumerateCardOutAction(handcard);
    ActionVector legalAction;
    for(auto& action : Action)
    {
        CardTypeStruct curCardType(action.cardtype, action.point, action.succ);
        if(CardProcess::CardCheck_tiny(curCardType, PreOutCardType))
        {
            legalAction.push_back(action);
        }
    }

    legalAction.push_back(Action[0]);
    if(legalAction.size() == 1)
        return std::make_pair(0, CardTypeStruct(CardType::None, 0, 1));

    if(PreOutCardType.cardtype == 0 || mustOut)
    {
        std::uniform_int_distribution<int> distribution(0, legalAction.size()-2);
        auto& action = legalAction[distribution(gen)];
        CardTypeStruct curCardType(action.cardtype, action.point, action.succ);
        std::cout << name << ":  MustDo PreOutCardType.cardtype: " << PreOutCardType.cardtype << "  mustOut:" << mustOut << "  " << action.action.to_string() << std::endl;
        return std::make_pair(action.action, curCardType);
    }
    else
    {
        std::uniform_int_distribution<int> distribution(0, legalAction.size()-1);
        auto& action = legalAction[distribution(gen)];
        CardTypeStruct curCardType(action.cardtype, action.point, action.succ);
        std::cout << name << ":  PreOutCardType.cardtype: " << PreOutCardType.cardtype << "  mustOut:" << mustOut << "  " << action.action.to_string() << std::endl;
        return std::make_pair(action.action, curCardType);
    }
    
    return std::make_pair(0, CardTypeStruct(CardType::None, 0, 1));
}

int robot::GetlandlordAction()
{
    sleepcp(2000);

    std::uniform_int_distribution<int> distribution(0, 1);
    return distribution(gen);
}
