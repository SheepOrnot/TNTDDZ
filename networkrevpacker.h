#ifndef NETWORKREVPACKER_H
#define NETWORKREVPACKER_H

#include <boost/beast.hpp>
#include <boost/json.hpp>
//#include <boost/json/src.hpp>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include "messagepackage.h"

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
        //发送包到消息中心
        try {
            switch ((NETWORK)pt.get<int>("type"))
            {
            case NETWORK::LOGIN:
            {
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
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::CREATE_ROOM, pt.get<int>("status"));
                break;
            }
            case NETWORK::JOIN_ROOM:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::JOIN_ROOM, pt.get<int>("status"));
                break;
            }
            case NETWORK::LEAVE_ROOM:
            {
                message->packMessage<MessageVerifyStatus>(VERIFY_TYPE::LEAVE_ROOM, pt.get<int>("status"));
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
