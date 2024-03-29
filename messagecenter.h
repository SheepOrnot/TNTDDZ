#ifndef MESSAGECENTER_H
#define MESSAGECENTER_H

#include "common.h"
#include "threadpool.h"
#include "messagepackage.h"
#include "HTTPJSONSender.h"
#include "networkrevpacker.h"
#include "widgetargpackage.h"

typedef std::function<void(WidgetArgPackage*)> WidgetInterfacePtr;

class MessageCenter
{
public:
    MessageCenter()
    {
        PluginFuncVector = nullptr;
        threadpool_ptr = new ThreadPool(10);
    }
    void loadLib();
    void static MessageProcessing(MessagePackage* current_message, MessageCenter* current_center)
    {
        switch (current_message->message_type)
        {
            case MESSAGE_TYPE::LOGIN:
            {
                MessageLogin *package = static_cast<MessageLogin*>(current_message->package);
                switch(package->opcode)
                {
                    case LOGIN_OPCODE::LOGIN:
                    {
                        //login
                        std::string login_json = "{\"mail\":\""      + package->mail + "\","
                                                + " \"account\":\""  + package->accout + "\","
                                                + " \"password\":\"" + package->password + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/login", login_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case LOGIN_OPCODE::REGISTER_MAIL:
                    {
                        //register_mail
                        std::string register_mail_json = "{\"mail\":\""     + package->mail + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/signupmail", register_mail_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case LOGIN_OPCODE::REGISTER:
                    {
                        //register
                        std::string register_json = "{\"mail\":\""   + package->mail     + "\","
                                                + " \"account\":\""  + package->accout   + "\","
                                                + " \"password\":\"" + package->password + "\","
                                                + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/signup", register_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case LOGIN_OPCODE::FORGET_PASSWORD_MAIL:
                    {
                        //register_mail
                        std::string register_mail_json = "{\"mail\":\""     + package->mail + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforgetmail", register_mail_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case LOGIN_OPCODE::FORGET_PASSWORD:
                    {
                        //register
                        std::string register_json = "{\"mail\":\""   + package->mail     + "\","
                                                + " \"password\":\"" + package->password + "\","
                                                + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforget", register_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                }
            }
            case MESSAGE_TYPE::VERIFY:
            {
                MessageVerifyStatus *status = static_cast<MessageVerifyStatus*>(current_message->package);
                switch(status->type)
                {
                    case VERIFY_TYPE::LOGIN:
                    {
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::LOGIN, status->code);
                        
                        std::cout << "loginStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceLoginSuccess"](arg);
                        else
                            current_center->WidgetInterface["interfaceLoginFail"](arg);
                        break;
                    }
                    case VERIFY_TYPE::REGISTER:
                    {
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::REGISTER, status->code);

                        std::cout << "registerStatus: " << status->code << std::endl;
                        //TODO
                        break;
                    }
                    case VERIFY_TYPE::FORGET_PASSWORD:
                    {
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::FORGET_PASSWORD, status->code);

                        std::cout << "findPasswordStatus: " << status->code << std::endl;
                        //TODO
                        break;
                    }
                }
                break;
            }
        }


        delete current_message;
    }

    void MessageSubmit(MessagePackage* current_message)
    {
        threadpool_ptr->submit(MessageProcessing, current_message, this);
    }

    void loadInterface(std::string key, WidgetInterfacePtr func_ptr)
    {
        WidgetInterface[key] = func_ptr;
    }

private:
    /*插件函数注册表*/
    const std::vector<PluginFuncPtr>* PluginFuncVector;
    /*线程池*/
    ThreadPool *threadpool_ptr;
    /*状态组指针*/

    /*界面接口*/
    std::map<std::string, WidgetInterfacePtr> WidgetInterface;

};

#endif // MESSAGECENTER_H
