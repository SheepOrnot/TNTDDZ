#ifndef WIDGETREVPACKER_H
#define WIDGETREVPACKER_H


#include "common.h"
#include "messagepackage.h"
#include "messagecenter.h"
#include "widgetargpackage.h"

class WidgetRevPacker
{
public:
    WidgetRevPacker(MessageCenter* _message_center)
    {
        message_center = _message_center;
    };
    ~WidgetRevPacker();

    /*消息中心指针*//*message_center->submit(MessagePackage)*/
    MessageCenter *message_center;

    /*消息打包，压入消息中心*/
    void WidgetsendMessage(WidgetArgPackage* current_widget_arg)
    {
        MessagePackage *msg_ptr = new MessagePackage;

        //发送包到消息中心
        switch (current_widget_arg->widget_arg_type)
        {
        case 1:
            //login
            WidgetArgLogin *login_package = static_cast<WidgetArgLogin*>(current_widget_arg->package);
            msg_ptr->packMessage<MessageLogin>(login_package->mail, login_package->accout, login_package->password);
            break;
        }

        message_center->MessageSubmit(msg_ptr);
        delete current_widget_arg;
    }

    void test()
    {
        std::cout << "界面消息发送 测试完毕" << std::endl;
    }
};


#endif // WIDGETREVPACKER_H
