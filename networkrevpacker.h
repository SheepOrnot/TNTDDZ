#ifndef NETWORKREVPACKER_H
#define NETWORKREVPACKER_H


#include "messagepackage.h"
#include "networkState.h"

namespace http = boost::beast::http;

//using namespace boost::property_tree

class NetworkRevPacker
{
public:
    NetworkRevPacker()
    {

    };

    ~NetworkRevPacker();


    /*消息打包，压入消息中心*/
    static MessagePackage* NetworksendMessage(std::string current_json_package)
    {
        std::stringstream ss(current_json_package);
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        std::cout << "从网络读取:" << pt.size() << std::endl;
        std::cout << "------------------------------------------------------------------" << std::endl;
        for(auto i = pt.begin(); i != pt.end(); i ++)
        {
            std::cout << i->first << " : " << pt.get<std::string>(i->first) << std::endl;
        }
        std::cout << "------------------------------------------------------------------" << std::endl;

        MessagePackage* message = new MessagePackage();
        std::shared_ptr<NetworkState> networkState = NetworkState::getInstance();

        //发送包到消息中心
        try {
            switch ((NETWORK)pt.get<int>("type"))
            {
            case NETWORK::LOGIN:
            {
                networkState->account   = pt.get<std::string>("account");
                networkState->username  = pt.get<std::string>("username");
                networkState->diamond   = std::stoi(pt.get<std::string>("diamond"));
                networkState->peas      = std::stoi(pt.get<std::string>("peas"));
                networkState->profile   = std::stoi(pt.get<std::string>("profilepicture"));
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::LOGIN, pt.get<int>("loginStatus"));
                break;
            }
            case NETWORK::REGISTER:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::REGISTER, pt.get<int>("signupresult"));
                break;
            }
            case NETWORK::FORGET_PASSWORD:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::FORGET_PASSWORD, pt.get<int>("result"));
                break;
            }
            case NETWORK::REGISTER_MAIL_CODE_VERIFY:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::REGISTER_MAIL, pt.get<int>("result"));
                break;
            }
            case NETWORK::FORGET_PASSWORD_MAIL_CODE_VERIFY:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::FORGET_PASSWORD_MAIL, pt.get<int>("result"));
                break;
            }
            case NETWORK::CREATE_ROOM:
            {
                networkState->roomid = pt.get<std::string>("roomid");
                networkState->seat   = std::stoi(pt.get<std::string>("seat"));
                networkState->setpos(networkState->seat);
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::CREATE_ROOM, pt.get<int>("status"));
                break;
            }
            case NETWORK::JOIN_ROOM:
            {
                if(pt.get<std::string>("account") == networkState->account)
                {
                    networkState->seat = std::stoi(pt.get<std::string>("seat"));
                    networkState->setpos(networkState->seat);
                }
                int result = pt.get<int>("status") != 1 ? -1 : pt.get<int>("seat");
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::JOIN_ROOM, result);
                break;
            }
            case NETWORK::LEAVE_ROOM:
            {
                int result;
                if(pt.get<std::string>("account") == networkState->account)
                {
                    int result = pt.get<int>("status") != 1 ? -1 : pt.get<int>("seat");
                    message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::LEAVE_ROOM, result);
                }
                else
                {
                    int result = pt.get<int>("status") != 1 ? -2 : pt.get<int>("seat");
                    message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::LEAVE_ROOM, result);
                }
                break;
            }
            case NETWORK::READY:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::READY, pt.get<int>("seat"));
                break;
            }
            case NETWORK::SENDCARD:
            {
                networkState->thefirst = pt.get<int>("first_lord_seat");
                networkState->handcards = std::bitset<54>(pt.get<long long>("handcards"));
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::SENDCARD, 0);
                break;
            }
            case NETWORK::PLAYER_INFO:
            {
                std::stringstream ss2(pt.get<std::string>("player_status"));
                boost::property_tree::ptree pt2;
                boost::property_tree::read_json(ss2, pt2);
                std::cout << "player_status:" << pt2.size() << std::endl;
                std::cout << "------------------------------------------------------------------" << std::endl;
                for(auto i = pt2.begin(); i != pt2.end(); i ++)
                {
                    std::cout << i->first << " : " << pt2.get<std::string>(i->first) << std::endl;
                }
                std::cout << "------------------------------------------------------------------" << std::endl;
                int seat = networkState->seat;
                networkState->account_up    = seat == 1 ? pt2.get<std::string>("player_3_account") : (seat == 2 ? pt2.get<std::string>("player_1_account") : pt2.get<std::string>("player_2_account"));
                networkState->username_up   = seat == 1 ? pt2.get<std::string>("player_3_username") : (seat == 2 ? pt2.get<std::string>("player_1_username") : pt2.get<std::string>("player_2_username"));
                networkState->peas_up       = seat == 1 ? pt2.get<int>("player_3_peas") : (seat == 2 ? pt2.get<int>("player_1_peas") : pt2.get<int>("player_2_peas"));
                networkState->profile_up    = seat == 1 ?  pt.get<int>("player3_profilepicture") : (seat == 2 ? pt.get<int>("player1_profilepicture") : pt.get<int>("player2_profilepicture"));
                networkState->account_down  = seat == 1 ? pt2.get<std::string>("player_2_account") : (seat == 2 ? pt2.get<std::string>("player_3_account") : pt2.get<std::string>("player_1_account"));
                networkState->username_down = seat == 1 ? pt2.get<std::string>("player_2_username") : (seat == 2 ? pt2.get<std::string>("player_3_username") : pt2.get<std::string>("player_1_username"));
                networkState->peas_down     = seat == 1 ? pt2.get<int>("player_2_peas") : (seat == 2 ? pt2.get<int>("player_3_peas") : pt2.get<int>("player_1_peas"));
                networkState->profile_down  = seat == 1 ?  pt.get<int>("player2_profilepicture") : (seat == 2 ? pt.get<int>("player3_profilepicture") : pt.get<int>("player1_profilepicture"));

                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::PLAYER_INFO, 0);
                break;
            }
            case NETWORK::ASK_OR_ROB:
            {
                networkState->curr_is_rob_stage = pt.get<int>("ask_or_rob_type");
                networkState->next_is_rob_stage = pt.get<int>("ask_or_rob_type_next");
                networkState->curr_seat = pt.get<int>("now_seat");
                networkState->next_seat = pt.get<int>("next_seat");
                networkState->curr_decision = networkState->curr_is_rob_stage == 0 ? pt.get<int>("ask") : pt.get<int>("rob");
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::ASK_OR_ROB, 0);
                break;
            }
            case NETWORK::LORD_DOUBLE:
            {
                networkState->double_score = pt.get<int>("now_double");
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::LORD_DOUBLE, pt.get<int>("now_double"));
                break;
            }
            case NETWORK::MUST_ROB:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::MUST_ROB, 0);
                break;
            }
            case NETWORK::LORD_CARD_BROADCAST:
            {
                networkState->identity1 = networkState->net2wid[pt.get<int>("seat")] == 1 ? "landlord" : "farmer";
                networkState->identity2 = networkState->net2wid[pt.get<int>("seat")] == 2 ? "landlord" : "farmer";
                networkState->identity3 = networkState->net2wid[pt.get<int>("seat")] == 3 ? "landlord" : "farmer";
                networkState->lordcards = std::bitset<54>(pt.get<long long>("lord_cards"));
                if(networkState->seat == pt.get<int>("seat"))
                {
                    networkState->handcards |= networkState->lordcards;
                }
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::LORD_CARD_BROADCAST, 0);
                break;
            }
            case NETWORK::LORD_CARD_UPDATE:
            {
                networkState->handcards = pt.get<std::bitset<54>>("handcards");
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::LORD_CARD_UPDATE, 0);
                break;
            }
            case NETWORK::CALL_DOUBLE:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::CALL_DOUBLE, 0);
                break;
            }
            case NETWORK::PLAYER_DOUBLE:
            {
                if(pt.get<int>("double"))
                {
                    message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::PLAYER_IS_DOUBLE, pt.get<int>("seat"));
                }
                else
                {
                    message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::PLAYER_NOT_DOUBLE, pt.get<int>("seat"));
                }
                break;
            }
            case NETWORK::CALL_OUTCARD:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::CALL_OUTCARD, pt.get<int>("now_output_player"));
                break;
            }
            case NETWORK::OUTCARD_UPDATE:
            {
                if(pt.get<long long>("tablecards") != networkState->outcards.to_ullong())
                {
                    networkState->outcards = std::bitset<54>(pt.get<long long>("tablecards"));
                    networkState->curr_decision = 1;
                }
                else
                {
                    networkState->curr_decision = 0;
                }
                std::cout << "networkState->curr_decision: " << std::endl; std::flush(std::cout);

                networkState->hide = pt.get<int>("hide");
                networkState->double_score = pt.get<int>("now_double");
                networkState->leftcard = pt.get<int>("handcards_num");
                networkState->curr_seat = pt.get<int>("seat");
                networkState->next_seat = pt.get<int>("now_output_player");
                networkState->cards_type = pt.get<int>("cards_type");
                if(networkState->curr_seat == networkState->seat)
                    networkState->handcards ^= networkState->outcards;
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::OUTCARD_UPDATE, 0);
                break;
            }
            case NETWORK::GAMEEND:
            {
                networkState->change_peas = pt.get<int>("change_peas");
                networkState->new_peas = pt.get<int>("new_peas");
                networkState->win_result = pt.get<int>("win_result");
                networkState->Score1 = networkState->change_peas;
                //networkState->Score2 = pt.get<int>("win_result");
                //networkState->Score3 = pt.get<int>("win_result");
                //networkState->times = pt.get<int>("win_result");
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::GAMEEND, 0);
                break;
            }
            default:
            {
                std::cout << "unknown network package" << std::endl;
                std::flush(std::cout);
                break;
            }
            }
        } catch (...) {
            std::cout << "Json No type" << std::endl;
            std::flush(std::cout);
            return nullptr;
        }

        return message;
    }

    void test()
    {
        std::cout << "Json 测试完毕" << std::endl;
    }
};


#endif // NETWORKREVPACKER_H
