#ifndef WIDGETREVPACKER_H
#define WIDGETREVPACKER_H


#include "common.h"
#include "messagepackage.h"
#include "messagecenter.h"
#include "widgetargpackage.h"

class WidgetRevPacker
{
public:
    static std::shared_ptr<WidgetRevPacker> getInstance() {return instance;}
    static void destoryInstance(WidgetRevPacker* x) {delete x;}

    /*消息中心指针*//*message_center->submit(MessagePackage)*/
    std::shared_ptr<MessageCenter> message_center;

    /*消息打包，压入消息中心*/
    void WidgetsendMessage(WidgetArgPackage* current_widget_arg)
    {
        MessagePackage *msg_ptr = new MessagePackage;
        WidgetArgAccount *account_package;
        //发送包到消息中心
        std::cout << "recv package: " << (int)msg_ptr->message_type << std::endl;
        std::flush(std::cout);
        switch (current_widget_arg->widget_arg_type)
        {
        case WIDGET_ARG_TYPE::ACCOUNT:
        {
            //account
            account_package = static_cast<WidgetArgAccount*>(current_widget_arg->package);
            msg_ptr->packMessage<MessageAccount>(account_package->opcode, account_package->mail, account_package->accout, account_package->password, account_package->username, account_package->code);
            break;
        }
        case WIDGET_ARG_TYPE::PLAYER:
        {
            WidgetArgPlayer *player_package = static_cast<WidgetArgPlayer*>(current_widget_arg->package);
            msg_ptr->packMessage<MessagePlayer>(player_package->opcode, player_package->pos,
                                                player_package->profileindex, player_package->beannum,
                                                player_package->account, player_package->roomid,
                                                player_package->iscall, player_package->singlemode);
            break;
        }
        }

        message_center->MessageSubmit(msg_ptr);
        delete current_widget_arg;
    }

private:
    WidgetRevPacker()
    {
        message_center = MessageCenter::getInstance();
    };
    ~WidgetRevPacker()
    {

    };

    static std::shared_ptr<WidgetRevPacker> instance;
    std::mutex _mutex;
};


#endif // WIDGETREVPACKER_H
