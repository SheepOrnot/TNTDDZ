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
            case MESSAGE_TYPE::ACCOUNT:
            {
                MessageAccount *package = static_cast<MessageAccount*>(current_message->package);
                switch(package->opcode)
                {
                    case ACCOUNT_OPCODE::LOGIN:
                    {
                        //login
                        std::string login_json = "{\"mail\":\""      + package->mail + "\","
                                                + " \"account\":\""  + package->accout + "\","
                                                + " \"password\":\"" + package->password + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/login", login_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case ACCOUNT_OPCODE::REGISTER_MAIL:
                    {
                        //register_mail
                        std::string register_mail_json = "{\"mail\":\""     + package->mail + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/signupmail", register_mail_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case ACCOUNT_OPCODE::REGISTER:
                    {
                        //register
                        std::string register_json = "{\"mail\":\""   + package->mail     + "\","
                                                + " \"account\":\""  + package->accout   + "\","
                                                + " \"password\":\"" + package->password + "\","
                                                + " \"username\":\"" + package->username + "\","
                                                + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/signup", register_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case ACCOUNT_OPCODE::REGISTER_MAIL_CODE_VERIFY:
                    {
                        //forgetr_mail_verify
                        std::string register_mail_verify_json = "{\"mail\":\""   + package->mail     + "\","
                                                                + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/signup_code_verify", register_mail_verify_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case ACCOUNT_OPCODE::FORGET_PASSWORD_MAIL:
                    {
                        //forget_mail
                        std::string forget_password_mail_json = "{\"mail\":\""     + package->mail + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforgetmail", forget_password_mail_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case ACCOUNT_OPCODE::FORGET_PASSWORD:
                    {
                        //forget
                        std::string forget_password_json = "{\"mail\":\""   + package->mail     + "\","
                                                + " \"password\":\"" + package->password + "\","
                                                + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforget", forget_password_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                    case ACCOUNT_OPCODE::FORGET_PASSWORD_MAIL_CODE_VERIFY:
                    {
                        //register_mail_verify
                        std::string forget_mail_verify_json = "{\"mail\":\""   + package->mail     + "\","
                                                          + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforget_code_verify", forget_mail_verify_json));
                        current_center->threadpool_ptr->submit(MessageProcessing, rev_from_svr, current_center);
                        break;
                    }
                }
                break;
            }
            case MESSAGE_TYPE::VERIFY:
            {
                MessageVerifyStatus *status = static_cast<MessageVerifyStatus*>(current_message->package);
                std::cout << "Do Verify: " << status->code << std::endl;
                switch(status->type)
                {
                    case VERIFY_TYPE::LOGIN:
                    {
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ACCOUNT, status->code);
                        
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
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ACCOUNT, status->code);

                        std::cout << "registerStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceRegisterSuccess"](arg);
                        else
                            current_center->WidgetInterface["interfaceRegisterFail"](arg);
                        break;
                    }
                    case VERIFY_TYPE::FORGET_PASSWORD:
                    {
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ACCOUNT, status->code);

                        std::cout << "findPasswordStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceForgetPasswordSuccess"](arg);
                        else
                            current_center->WidgetInterface["interfaceForgetPasswordFail"](arg);
                        break;
                    }
                    case VERIFY_TYPE::REGISTER_MAIL:
                    {
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ACCOUNT, status->code);

                        std::cout << "registerMailStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceRegisterMailSuccess"](arg);
                        else
                            current_center->WidgetInterface["interfaceRegisterMailFail"](arg);
                        break;
                    }
                    case VERIFY_TYPE::FORGET_PASSWORD_MAIL:
                    {
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ACCOUNT, status->code);

                        std::cout << "findPasswordMailStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceForgetPasswordMailSuccess"](arg);
                        else
                            current_center->WidgetInterface["interfaceForgetPasswordMailFail"](arg);
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
