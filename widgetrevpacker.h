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
        WidgetArgAccount *account_package;
        //发送包到消息中心
        switch (current_widget_arg->widget_arg_type)
        {
        case WIDGET_ARG_TYPE::ACCOUNT:
            //account
            account_package = static_cast<WidgetArgAccount*>(current_widget_arg->package);
            msg_ptr->packMessage<MessageAccount>(account_package->opcode, account_package->mail, account_package->accout, account_package->password, account_package->username, account_package->code);
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
