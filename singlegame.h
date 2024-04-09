#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "common.h"
#include "robot.h"
#include "cardprocess.h"
#include "messagepackage.h"

class SingleGame
{
public:
    SingleGame()
    {
        robot::init();
        bot1.setname("bot1");
        bot2.setname("bot2");
        init();
    }
    void init()
    {
        state = 0;
        thefirst = 0;
        landlordRound_final = 0;
        landlord = 0;
        cardtype = 0;
        point = 0;
        succ = 0;
        preout = 0;
        someonecall = 0;
        callCount = 0;
        preout_cards = 0;
    }
    void SendCard()
    {
        SendCardPackage result = CardProcess::SendCard();
        robot1_handcard = result.p1;
        robot2_handcard = result.p2;
        player_handcard = result.p3;
        final_card = result.finalcard;

        bot1.sethandcard(robot1_handcard);
        bot2.sethandcard(robot2_handcard);

        std::cout << "发牌完毕" << std::endl;
        std::flush(std::cout);
    }
    int SelectStart()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1,3);
        
        state = 1;
        thefirst = distribution(gen);
        
        std::cout << "先手叫地主: " << thefirst << std::endl;
        std::flush(std::cout);

        return thefirst;
    }
    void getnext_prepare(MessagePackage* current_message)
    {
        MessagePackage *msg = new MessagePackage();
        switch(current_message->message_type)
        {
            case MESSAGE_TYPE::PLAYER:
            {
                MessagePlayer *package = static_cast<MessagePlayer*>(current_message->package);
                switch(package->opcode)
                {
                    case PLAYER_OPCODE::LANDLORD:
                    {
                        callCount ++;
                        if(isCallLandlordRound()) 
                        {
                            if(package->iscall)
                                state ++;
                        }
                        else state ++;

                        std::cout << "someone want landlord prepare: " << package->pos << " call:" << package->iscall << std::endl; std::flush(std::cout);
                        landlord = package->iscall ? package->pos : landlord;
                        someonecall = !someonecall && package->iscall ? package->pos : someonecall;
                        break;
                    }
                }
                break;
            }
            case MESSAGE_TYPE::CARD:
            {
                MessageCard *package = static_cast<MessageCard*>(current_message->package);
                switch(package->opcode)
                {
                    case CARD_OPCODE::OUTCARD:
                    {
                        if(package->OutCard.count())
                        {
                            cardtype = package->cardtype;
                            point = package->point;
                            succ = package->succ;
                            preout = package->pos;
                            preout_cards = package->OutCard;
                            std::cout << "set1: " << cardtype << " " << point << " " << succ << " " << preout << std::endl; std::flush(std::cout);
                        }
                        if(package->pos == 3)
                        {
                            player_leftcards -= package->OutCard.count();
                            player_handcard ^= package->OutCard;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    MessagePackage* getnext(MessagePackage* current_message)
    {
        //1(叫地主) -> 2(抢地主1) -> 3(抢地主2) -> 4(抢地主3) -> 5(出牌)
        MessagePackage *msg = new MessagePackage();
        switch(current_message->message_type)
        {
            case MESSAGE_TYPE::PLAYER:
            {
                MessagePlayer *package = static_cast<MessagePlayer*>(current_message->package);
                switch(package->opcode)
                {
                    case PLAYER_OPCODE::READY:
                    {
                        int iscall = 0;
                        //预备叫地主
                        if(thefirst == 1)
                        {
                            //landlordQueue.push(1);
                            landlordQueue.push(3);
                            landlordQueue.push(2);
                            iscall = bot1.GetlandlordAction();
                            landlord = iscall ? 1 : landlord;
                            std::cout << "robot1: calllandlord: " << iscall << std::endl; std::flush(std::cout);
                            msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 1, 0, 999, "机器人1", "111", package->roomid, iscall, 1);
                        }
                        else if(thefirst == 2)
                        {
                            //landlordQueue.push(2);
                            landlordQueue.push(1);
                            landlordQueue.push(3);
                            iscall = bot2.GetlandlordAction();
                            landlord = iscall ? 2 : landlord;
                            std::cout << "robot2: calllandlord: " << iscall << std::endl; std::flush(std::cout);
                            msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 2, 0, 999, "机器人2", "222", package->roomid, iscall, 1);
                        }
                        else if(thefirst == 3)
                        {
                            landlordQueue.push(2);
                            landlordQueue.push(1);
                        }
                        printLandlordQueue();
                        break;
                    }
                    case PLAYER_OPCODE::LANDLORD:
                    {
                        std::cout << "someone want landlord: " << package->pos << " call:" << package->iscall << std::endl; std::flush(std::cout);
                        landlord = package->iscall ? package->pos : landlord;
                        someonecall = !someonecall && package->iscall ? package->pos : someonecall;

                        if(!isBidLandlordRound())
                        {
                            landlordRound_final = 1;
                            identity1 = landlord == 1 ? "landlord" : "farmer";
                            identity2 = landlord == 2 ? "landlord" : "farmer";
                            identity3 = landlord == 3 ? "landlord" : "farmer";
                            bot1_leftcards = 17;
                            bot2_leftcards = 17;
                            player_leftcards = 17;

                            if(landlord == 1)
                            {
                                robot1_handcard |= final_card;
                                bot1_leftcards += 3;
                                bot1.sethandcard(robot1_handcard);
                            }
                            else if(landlord == 2)
                            {
                                robot2_handcard |= final_card;
                                bot2_leftcards += 3;
                                bot2.sethandcard(robot2_handcard);
                            }
                            else if(landlord == 3)
                            {
                                player_leftcards += 3;
                                player_handcard |= final_card;
                            }
                            std::cout << "the landlord: " << landlord << std::endl; std::flush(std::cout);

                            msg->packMessage<MessageGameStart>();
                            break;
                        }
                        
                        if(isCallLandlordRound())
                        {
                            //叫地主
                            //if no one call landlord
                            if(callCount == 3)
                            {
                                std::cout << "no one call landlord" << std::endl; std::flush(std::cout);
                                init();
                                msg->packMessage<MessagePlayer>(PLAYER_OPCODE::READY, 3, 0, 0, "", "", package->roomid, 0, 1);
                                break;
                            }

                            int iscall = 0;
                            
                            if(package->pos == 2)
                            {
                                iscall = bot1.GetlandlordAction();
                                std::cout << "robot2: calllandlord: " << iscall << std::endl; std::flush(std::cout);
                                msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 1, 0, 999, "机器人1", "111", package->roomid, iscall, 1);
                            }
                            else if(package->pos == 3)
                            {
                                iscall = bot2.GetlandlordAction();
                                std::cout << "robot2: calllandlord: " << iscall << std::endl; std::flush(std::cout);
                                msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 2, 0, 999, "机器人2", "222", package->roomid, iscall, 1);
                            }
                            landlordQueue.pop();
                        }
                        else
                        {
                            if(state == 2)
                            {
                                landlordQueue.push(package->pos);
                            }
                            //抢地主
                            //if(package->pos == 2)
                            int iscall = 0;
                            if(landlordQueue.front() == 1)
                            {
                                iscall = bot1.GetlandlordAction();
                                std::cout << "robot1: bidlandlord: " << iscall << std::endl; std::flush(std::cout);
                                msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 1, 0, 999, "机器人1", "111", package->roomid, iscall, 1);
                            }
                            else if(landlordQueue.front() == 2)
                            {
                                iscall = bot2.GetlandlordAction();
                                std::cout << "robot2: bidlandlord: " << iscall << std::endl; std::flush(std::cout);
                                msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 2, 0, 999, "机器人2", "222", package->roomid, iscall, 1);
                            }

                            landlordQueue.pop();
                            if(!iscall && landlordQueue.front() == landlord)
                            {
                                state ++;
                                landlordQueue.pop();
                            }
                        }

                        printLandlordQueue();
                        break;
                    }
                }
                break;
            }
            case MESSAGE_TYPE::GAME_START:
            {
                if(landlord == 1)
                {
                    std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot1.OutCardAction(CardTypeStruct(CardType::None, 0, 1), isTheLandlordFirst(1));
                    bot1_leftcards -= robotOutCard.first.count();
                    robot1_handcard ^= robotOutCard.first;
                    bot1.sethandcard(robot1_handcard);
                    msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 1, bot1_leftcards, (int)robotOutCard.second.cardtype, robotOutCard.second.point, robotOutCard.second.succ, robotOutCard.first, 0, 1);
                }
                else if(landlord == 2)
                {
                    std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot2.OutCardAction(CardTypeStruct(CardType::None, 0, 1), isTheLandlordFirst(2));
                    bot2_leftcards -= robotOutCard.first.count();
                    robot2_handcard ^= robotOutCard.first;
                    bot2.sethandcard(robot2_handcard);
                    msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 2, bot2_leftcards, (int)robotOutCard.second.cardtype, robotOutCard.second.point, robotOutCard.second.succ, robotOutCard.first, 0, 1);
                }
                break;
            }
            case MESSAGE_TYPE::CARD:
            {
                MessageCard *package = static_cast<MessageCard*>(current_message->package);
                switch(package->opcode)
                {
                    case CARD_OPCODE::OUTCARD:
                    {
                        if(isGameEnd())
                        {
                            std::cout << "对局结束" << std::endl;
                            std::flush(std::cout);
                            msg->packMessage<MessageGameEnd>();
                            break;
                        }
                        if(package->pos == 1)
                        {
                            if(preout == 3 && !package->OutCard.count()) {preout_cards = cardtype = point = 0; succ = 1; std::cout << "player set2: " << cardtype << " " << point << " " << succ << " " << preout << std::endl; std::flush(std::cout);}
                        }
                        else if(package->pos == 2)
                        {
                            if(preout == 1 && !package->OutCard.count()) {preout_cards = cardtype = point = 0; succ = 1; std::cout << "bot1 set2: " << cardtype << " " << point << " " << succ << " " << preout << std::endl; std::flush(std::cout);}
                            std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot1.OutCardAction(CardTypeStruct((CardType)cardtype, point, succ), 0);
                            bot1_leftcards -= robotOutCard.first.count();
                            robot1_handcard ^= robotOutCard.first;
                            bot1.sethandcard(robot1_handcard);

                            std::cout << "bot1 out: " << robotOutCard.second.cardtype << " " << robotOutCard.second.point << " " << robotOutCard.second.succ << " " << robotOutCard.first.to_string() << std::endl; std::flush(std::cout);
                            msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 1, bot1_leftcards, (int)robotOutCard.second.cardtype, robotOutCard.second.point, robotOutCard.second.succ, robotOutCard.first, 0, 1);
                        }
                        else if(package->pos == 3)
                        {
                            //2
                            if(preout == 2 && !package->OutCard.count()) {preout_cards = cardtype = point = 0; succ = 1; std::cout << "bot2 set2: " << cardtype << " " << point << " " << succ << " " << preout << std::endl; std::flush(std::cout);}
                            std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot2.OutCardAction(CardTypeStruct((CardType)cardtype, point, succ), 0);
                            bot2_leftcards -= robotOutCard.first.count();
                            robot2_handcard ^= robotOutCard.first;
                            bot2.sethandcard(robot2_handcard);

                            std::cout << "bot2 out: " << robotOutCard.second.cardtype << " " << robotOutCard.second.point << " " << robotOutCard.second.succ << " " << " " << robotOutCard.first.to_string() << std::endl; std::flush(std::cout);
                            msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 2, bot2_leftcards, (int)robotOutCard.second.cardtype, robotOutCard.second.point, robotOutCard.second.succ, robotOutCard.first, 0, 1);
                        }

                        break;
                    }
                }
                break;
            }
        }

        if(msg->package == nullptr) 
        {
            delete msg;
            return nullptr;
        }
        return msg;
    }

    int isCallForLandlordRound()
    {
        return state == 2;
    }
    int isBidLandlordRound()
    {
        //return state <= 4;
        return landlordQueue.size();
    }
    int isCallLandlordRound()
    {
        return state <= 1;
    }
    int isGameEnd()
    {
        return bot1_leftcards == 0 || bot2_leftcards == 0 || player_leftcards == 0;
    }
    int isTheLandlordFirst(int pos)
    {
        int result = pos == landlord && state == 5;
        state ++;
        return result;
    }
    int PlayerCardOutCheck(std::bitset<54> outcards)
    {
        std::cout << "PlayerCardOutCheck: "     << std::endl;
        std::cout << outcards.to_string()       << std::endl;
        std::cout << preout_cards.to_string()   << std::endl;
        std::flush(std::cout);

        if(!outcards.count())
        {
            return !(isTheLandlordFirst(3) || !preout_cards.count());
        }

        std::pair<CardTypeVector, int> result = CardProcess::CardCheck(outcards.to_ulong(), preout_cards.to_ulong());
        return result.second;
    }
    int nextone()
    {
        return landlordQueue.front();
    }
    void printLandlordQueue()
    {
        std::queue<int> tmp(landlordQueue);
        int len = tmp.size();
        std::cout << "LandlordQueue: ";
        for(int i = 0; i < len; i ++ )
        {
            std::cout << tmp.front() << " ";
            tmp.pop();
        }
        std::cout << std::endl;
        std::flush(std::cout);
    }

    int state;
    int landlordRound_final;
    int thefirst;
    int landlord;
    int callCount;
    std::queue<int> landlordQueue;

    std::string identity1;
    std::string identity2;
    std::string identity3;

    robot bot1;
    robot bot2;

    int bot1_leftcards;
    int bot2_leftcards;
    int player_leftcards;

    int cardtype;
    int point;
    int preout;
    int succ;
    std::bitset<54> preout_cards;

    int someonecall;

    std::bitset<54> robot1_handcard;
    std::bitset<54> robot2_handcard;
    std::bitset<54> player_handcard;
    std::bitset<54> final_card;
};

#endif // SINGLEGAME_H
