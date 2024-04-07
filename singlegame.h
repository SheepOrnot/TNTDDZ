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
        state = 0;
        thefirst = 0;
        landlordRound_final = 0;
        landlord = 0;
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
    }
    int SelectStart()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1,3);
        
        state = 1;
        thefirst = distribution(gen);
        
        return thefirst;
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
                        //预备叫地主
                        if(thefirst == 1)
                        {
                            int iscall = bot1.GetlandlordAction();
                            landlord = iscall ? 1 : landlord;
                            msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 1, 0, 999, "机器人1", package->roomid, iscall);
                        }
                        else if(thefirst == 2)
                        {
                            int iscall = bot2.GetlandlordAction();
                            landlord = iscall ? 2 : landlord;
                            msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 2, 0, 999, "机器人2", package->roomid, iscall);
                        }
                        state ++;
                        break;
                    }
                    case PLAYER_OPCODE::LANDLORD:
                    {
                        landlord = package->iscall ? package->pos : landlord;
                        if(state == 5)
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

                            msg->packMessage<MessageGameStart>();
                            break;
                        }

                        //抢地主
                        if(package->pos == 2)
                        {
                            int iscall = bot1.GetlandlordAction();
                            msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 1, 0, 999, "机器人1", package->roomid, iscall);
                        }
                        else if(package->pos == 3)
                        {
                            int iscall = bot2.GetlandlordAction();
                            msg->packMessage<MessagePlayer>(PLAYER_OPCODE::LANDLORD, 2, 0, 999, "机器人2", package->roomid, iscall);
                        }
                        state ++;
                        break;
                    }
                }
                break;
            }
            case MESSAGE_TYPE::GAME_START:
            {
                if(landlord == 1)
                {
                    std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot1.OutCardAction(std::make_pair(CardType::None, 0));
                    bot1_leftcards -= robotOutCard.first.count();
                    msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 1, bot1_leftcards, (int)robotOutCard.second.first, robotOutCard.second.second, robotOutCard.first, 0, 1);
                }
                else if(landlord == 2)
                {
                    std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot2.OutCardAction(std::make_pair(CardType::None, 0));
                    bot2_leftcards -= robotOutCard.first.count();
                    msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 2, bot2_leftcards, (int)robotOutCard.second.first, robotOutCard.second.second, robotOutCard.first, 0, 1);
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
                        if(package->leftcards == 0)
                        {
                            std::cout << "对局结束" << std::endl;
                            std::flush(std::cout);
                            msg->packMessage<MessageGameEnd>();
                            break;
                        }

                        if(package->pos == 1)
                        {
                            //pass
                        }
                        else if(package->pos == 2)
                        {
                            std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot1.OutCardAction(std::make_pair((CardType)package->cardtype, package->point));
                            bot1_leftcards -= robotOutCard.first.count();
                            msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 1, bot1_leftcards, (int)robotOutCard.second.first, robotOutCard.second.second, robotOutCard.first, 0, 1);
                        }
                        else if(package->pos == 3)
                        {
                            player_leftcards -= package->OutCard.count();
                            std::pair<std::bitset<54>, CardTypeStruct> robotOutCard = bot2.OutCardAction(std::make_pair((CardType)package->cardtype, package->point));
                            bot2_leftcards -= robotOutCard.first.count();
                            msg->packMessage<MessageCard>(CARD_OPCODE::OUTCARD, 2, bot2_leftcards, (int)robotOutCard.second.first, robotOutCard.second.second, robotOutCard.first, 0, 1);
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

    int EnterBidForLandlordRound()
    {
        return state == 2;
    }
    int isCallForLandlordRound()
    {
        return state == 2;
    }
    int isBidLandlordRound()
    {
        return state < 5;
    }
    int isGameEnd()
    {
        return bot1_leftcards == 0 || bot2_leftcards == 0 || player_leftcards == 0;
    }

    int state;
    int landlordRound_final;
    int thefirst;
    int landlord;

    std::string identity1;
    std::string identity2;
    std::string identity3;

    robot bot1;
    robot bot2;

    int bot1_leftcards;
    int bot2_leftcards;
    int player_leftcards;

    std::bitset<54> robot1_handcard;
    std::bitset<54> robot2_handcard;
    std::bitset<54> player_handcard;
    std::bitset<54> final_card;
};

#endif // SINGLEGAME_H
