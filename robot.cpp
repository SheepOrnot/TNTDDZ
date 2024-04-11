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
        std::string tmp = robot::COMBINE_CARD(robot::BitsetTOString(robot::handcard));
        for(ActionVector::iterator it = legalAction.begin(); it != legalAction.end(); it++)
        if(robot::BitsetTOString(it->action)==tmp)
        {
            auto &action = *it;
            CardTypeStruct curCardType(action.cardtype, action.point, action.succ);
            std::cout << name << ":  PreOutCardType.cardtype: " << PreOutCardType.cardtype << "  mustOut:" << mustOut << "  " << action.action.to_string() << std::endl;
            return std::make_pair(action.action, curCardType);
        }
        std::uniform_int_distribution<int> distribution(0, legalAction.size()-2);
        auto& action = legalAction[distribution(gen)];
        CardTypeStruct curCardType(action.cardtype, action.point, action.succ);
        std::cout << name << ":  PreOutCardType.cardtype: " << PreOutCardType.cardtype << "  mustOut:" << mustOut << "  " << action.action.to_string() << std::endl;
        return std::make_pair(action.action, curCardType);
    }
    else
    {
        /*
        std::uniform_int_distribution<int> distribution(0, legalAction.size()-1);
        auto& action = legalAction[distribution(gen)];
        CardTypeStruct curCardType(action.cardtype, action.point, action.succ);
        std::cout << name << ":  PreOutCardType.cardtype: " << PreOutCardType.cardtype << "  mustOut:" << mustOut << "  " << action.action.to_string() << std::endl;
        return std::make_pair(action.action, curCardType);
        */
        legalAction.pop_back();
        ActionVector::iterator it1,it2;
        it1 = it2 = legalAction.begin(); ++it1;
        for(;it1!=legalAction.end(); ++it1)
        if(CardProcess::CardCheck_tiny(CardTypeStruct(it2->cardtype,it2->point,it2->succ),CardTypeStruct(it1->cardtype,it1->point,it1->succ)))
        it2 = it1;
        auto& action = *it2;
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

std::string robot::COMBINE_CARD(std::string hand)
{
    enum HANDCARDTYPE{TRIO,TRIO_CHAIN,PAIR_CHAIN,SOLO_CHAIN,PAIR,SOLO,BOMB,ROCKET};
    std::vector<std::string> combine_card[8];
    for(int i = 0; i < 8; ++i) while(!combine_card[i].empty())combine_card[i].pop_back();
    std::string _MINCHAR = std::string(1,hand[0]);
    //1.pick rocket
    if(hand.find("BR")!=std::string::npos)
    {
        combine_card[ROCKET].push_back("BR");
        hand.replace(hand.find("BR"),2,"");
    }
    //2.pick bomb
    for(int i = 0; i+3 < hand.length(); ++i)
    if(hand[i]==hand[i+3])
    {
        std::string tmp(4,hand[i]);
        combine_card[BOMB].push_back(tmp);
        hand.replace(hand.find(tmp),4,"");
    }
    //3.pick trio and rio_chain
    std::string hand_tmp = hand;
    std::vector<std::string> trio_tmp;
    for(int i = 0; i+2 < hand_tmp.length(); ++i)
    if(hand_tmp[i]==hand_tmp[i+2])
    {
            std::string tmp(3,hand_tmp[i]);
        if(!trio_tmp.empty() && index(hand_tmp[i])<12 && ((index(hand_tmp[i])-1)==index(trio_tmp.back()[trio_tmp.back().length()-1])))
        trio_tmp.back().append(tmp);
        else trio_tmp.push_back(tmp);
        hand.replace(hand.find(tmp),3,"");
    }
    for(std::vector<std::string>::iterator it = trio_tmp.begin(); it != trio_tmp.end(); ++it)
    {
        if(it->length()==3) combine_card[TRIO].push_back(*it);
        else combine_card[TRIO_CHAIN].push_back(*it);
    }
    //4.pick pair chain ans solo chain
    robot::pick_chain(&combine_card[PAIR_CHAIN],hand,2,3);
    robot::pick_chain(&combine_card[SOLO_CHAIN],hand,1,5);
    int tmp_i = 0;
    while(tmp_i < hand.length())
    {
        if(tmp_i==hand.length()-1) combine_card[SOLO].push_back(std::string(1,hand[tmp_i])),tmp_i+=1;
        else if(hand[tmp_i] == hand[tmp_i+1]) combine_card[PAIR].push_back(std::string(2,hand[tmp_i])),tmp_i+=2;
        else combine_card[SOLO].push_back(std::string(1,hand[tmp_i])),tmp_i+=1;
    } hand = "";
    for(int i = 0; i < 8; ++i)
    {
        std::cout<<"TYPE: "<<std::endl;std::flush(std::cout);
        for(std::vector<std::string>::iterator it = combine_card[i].begin(); it != combine_card[i].end(); ++it)
        {std::cout<<*it<<" ";std::flush(std::cout);}
        puts("");
    }
    for(int i = 0; i < 8; ++i)
    {
        for(std::vector<std::string>::iterator it = combine_card[i].begin(); it != combine_card[i].end(); ++it)
        if((*it).find(_MINCHAR)!=std::string::npos)
        {
            return *it;
        }
    }
    return "";
}

std::string robot::BitsetTOString(std::bitset<54> _card)
{
    std::string tmp = "";
    for(int i = 0; i < 52; ++i) if(_card[i])
    tmp.append(1,robot::ANTI_index[i/4]);
    if(_card[52]) tmp.append(1,robot::ANTI_index[13]);
    if(_card[53]) tmp.append(1,robot::ANTI_index[14]);
    return tmp;
}

void robot::pick_chain(std::vector<std::string> *v,std::string &hand,int count,int lim)
{
    int hand_list[15] = {};
    for(int i = 0; i < hand.length(); ++i) ++hand_list[index(hand[i])];
    int MAXN = 0,POSN = 0;
    do
    {
        if(MAXN > 0)
        {
            std::string tmp = "";
            for(int i = POSN; i < 12 && hand_list[i] >= count; ++i)
            {
                hand_list[i] -= count;
                tmp.append(count,ANTI_index[i]);
            }
            v->push_back(tmp);
        }
        MAXN = 0;
        for(int i = 0; i < 12; ++i)
        if(hand_list[i] >= count)
        {
            int len = 1;
            for(int j = i+1; j < 12 && hand_list[j] >= count; ++j)
                ++len;
            if(len>=lim&&len>MAXN)  {MAXN = len,POSN = i;}
        }
    } while (MAXN > 0);
    hand = "";
    for(int i = 0; i < 15; ++i) if(hand_list[i]>0)
    hand.append(hand_list[i],ANTI_index[i]);
}

int robot::index(char c)
{
    switch (c)
    {
    case '3':
        return 0;
        break;
    case '4':
        return 1;
        break;
    case '5':
        return 2;
        break;
    case '6':
        return 3;
        break;
    case '7':
        return 4;
        break;
    case '8':
        return 5;
        break;
    case '9':
        return 6;
        break;
    case 'T':
        return 7;
        break;
    case 'J':
        return 8;
        break;
    case 'Q':
        return 9;
        break;
    case 'K':
        return 10;
        break;
    case 'A':
        return 11;
        break;
    case '2':
        return 12;
        break;
    case 'B':
        return 13;
        break;
    case 'R':
        return 14;
        break;
    
    
    default:
        break;
    }
    return -1;
}
