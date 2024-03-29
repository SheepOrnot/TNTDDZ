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
        case 1:

            //login
            MessageLogin *login_package = static_cast<MessageLogin*>(current_message->package);
            std::string login_json = "{\"mail\":\""     + login_package->mail + "\","
                                     + " \"account\":\""  + login_package->accout + "\","
                                     + " \"password\":\"" + login_package->password + "\"}";
            MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/login", login_json));
            std::cout << rev_from_svr << std::endl;
            MessageStatus *status = static_cast<MessageStatus*>(rev_from_svr->package);
            std::cout << "loginStatus: " << status->success << std::endl;
            if(status->success)
            {
                WidgetArgPackage *arg = new WidgetArgPackage();
                arg->packMessage<WidgetArgStatus>(1, status->success);
                current_center->WidgetInterface["interfaceLoginSuccess"](arg);
            }
            else
            {
                WidgetArgPackage *arg = new WidgetArgPackage();
                arg->packMessage<WidgetArgStatus>(1, status->success);
                current_center->WidgetInterface["interfaceLoginFail"](arg);
            }
            break;
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
