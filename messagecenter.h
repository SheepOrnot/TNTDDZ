#ifndef MESSAGECENTER_H
#define MESSAGECENTER_H

#include "HTTPJSONSender.h"
#include "common.h"
#include "threadpool.h"
#include "messagepackage.h"
#include "networkrevpacker.h"
#include "widgetargpackage.h"
#include "socketioclient.h"
#include "singlegame.h"
#include <QThread>

typedef std::function<void(WidgetArgPackage*)> WidgetInterfacePtr;

class Runner : public QThread
{
    Q_OBJECT
public:
    Runner(WidgetInterfacePtr _func, WidgetArgPackage* _package, QObject *parent = nullptr) :
        QThread(parent),
        func(_func),
        package(_package){};
    WidgetArgPackage* package;
    WidgetInterfacePtr func;

    void run() override {
        func(package);
    }
};

class MessageCenter
{
public:
    static std::shared_ptr<MessageCenter> getInstance() {return instance;}
    static void destoryInstance(MessageCenter* x) {delete x;}
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
                        current_center->MessageSubmit(rev_from_svr);
                        break;
                    }
                    case ACCOUNT_OPCODE::REGISTER_MAIL:
                    {
                        //register_mail
                        std::string register_mail_json = "{\"mail\":\""     + package->mail + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/signupmail", register_mail_json));
                        current_center->MessageSubmit(rev_from_svr);
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
                        current_center->MessageSubmit(rev_from_svr);
                        break;
                    }
                    case ACCOUNT_OPCODE::REGISTER_MAIL_CODE_VERIFY:
                    {
                        //forgetr_mail_verify
                        std::string register_mail_verify_json = "{\"mail\":\""   + package->mail     + "\","
                                                                + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/signup_code_verify", register_mail_verify_json));
                        current_center->MessageSubmit(rev_from_svr);
                        break;
                    }
                    case ACCOUNT_OPCODE::FORGET_PASSWORD_MAIL:
                    {
                        //forget_mail
                        std::string forget_password_mail_json = "{\"mail\":\""     + package->mail + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforgetmail", forget_password_mail_json));
                        current_center->MessageSubmit(rev_from_svr);
                        break;
                    }
                    case ACCOUNT_OPCODE::FORGET_PASSWORD:
                    {
                        //forget
                        std::string forget_password_json = "{\"mail\":\""   + package->mail     + "\","
                                                + " \"password\":\"" + package->password + "\","
                                                + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforget", forget_password_json));
                        current_center->MessageSubmit(rev_from_svr);
                        break;
                    }
                    case ACCOUNT_OPCODE::FORGET_PASSWORD_MAIL_CODE_VERIFY:
                    {
                        //register_mail_verify
                        std::string forget_mail_verify_json = "{\"mail\":\""   + package->mail     + "\","
                                                          + " \"code\":\""     + package->code     + "\"}";
                        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(HTTPJSONSender::HTTPJSONSend("/passwordforget_code_verify", forget_mail_verify_json));
                        current_center->MessageSubmit(rev_from_svr);
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
                            current_center->doInterfaceWidget("interfaceLoginSuccess", arg);
                            //current_center->WidgetInterface["interfaceLoginSuccess"](arg);
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
                    case VERIFY_TYPE::CREATE_ROOM:
                    {
                        std::cout << "create room" << std::endl;
                        std::flush(std::cout);
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ROOM, status->code);
                        
                        std::cout << "createRoomStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceEnterRoomSuccess"](arg);
                        else
                            current_center->WidgetInterface["interfaceEnterRoomFail"](arg);
                        break;
                    }
                    case VERIFY_TYPE::JOIN_ROOM:
                    {
                        std::cout << "join room" << std::endl;
                        std::flush(std::cout);
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ROOM, status->code);
                        
                        std::cout << "joinRoomStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceEnterRoomSuccess"](arg);
                        else
                            current_center->WidgetInterface["interfaceEnterRoomFail"](arg);
                        break;
                    }
                    case VERIFY_TYPE::LEAVE_ROOM:
                    {
                        std::cout << "leave room" << std::endl;
                        std::flush(std::cout);
                        WidgetArgPackage *arg = new WidgetArgPackage();
                        arg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ROOM, status->code);
                        
                        std::cout << "leaveRoomStatus: " << status->code << std::endl;
                        if(status->code == 1)
                            current_center->WidgetInterface["interfaceExitRoom"](arg);
                        break;
                    }
                
                }
                break;
            }
            case MESSAGE_TYPE::PLAYER:
            {
                MessagePlayer *package = static_cast<MessagePlayer*>(current_message->package);
                std::cout << "singlemode:" << package->singlemode << std::endl;
                std::flush(std::cout);
                if(package->singlemode)
                {
                    switch(package->opcode)
                    {
                        case PLAYER_OPCODE::CREATE_ROOM:
                        {
                            std::cout << "single Mode Create Room" << std::endl;
                            std::flush(std::cout);
                            WidgetArgPackage *Robot1Arg = new WidgetArgPackage();
                            Robot1Arg->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::ENTER, 1, 0, 999, "机器人1", "111", package->roomid, 0, 1);
                            WidgetArgPackage *Robot2Arg = new WidgetArgPackage();
                            Robot2Arg->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::ENTER, 2, 0, 999, "机器人2", "222", package->roomid, 0, 1);

                            WidgetArgPackage *CreateRoomArg = new WidgetArgPackage();
                            CreateRoomArg->packMessage<WidgetArgStatus>(WIDGET_ARG_TYPE::ROOM, -1);
                            current_center->WidgetInterface["interfaceEnterRoomSuccess"](CreateRoomArg);
                            sleepcp(1000);

                            current_center->WidgetInterface["interfaceSomebodyEnterRoom"](Robot1Arg);
                            current_center->WidgetInterface["interfaceSomebodyEnterRoom"](Robot2Arg);
                            WidgetArgPackage *Robot1Ready= new WidgetArgPackage();
                            Robot1Ready->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::READY, 1, 0, 999, "机器人1", "111", package->roomid, 0, 1);
                            WidgetArgPackage *Robot2Ready = new WidgetArgPackage();
                            Robot2Ready->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::READY, 2, 0, 999, "机器人2", "222", package->roomid, 0, 1);
                            current_center->WidgetInterface["interfaceSomebodyReady"](Robot1Ready);
                            current_center->WidgetInterface["interfaceSomebodyReady"](Robot2Ready);

                            //singleCtrl -> newgame
                            current_center->singleCtrl = new SingleGame();
                            break;
                        }
                        case PLAYER_OPCODE::READY:
                        {
                            std::cout << "玩家准备" << std::endl;
                            std::flush(std::cout);
                            WidgetArgPackage *PlayerArg = new WidgetArgPackage();
                            PlayerArg->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::READY, 3, package->profileindex, package->beannum, package->username, package->account, package->roomid);
                            current_center->WidgetInterface["interfaceSomebodyReady"](PlayerArg);
                            
                            std::cout << "Ready" << std::endl;
                            std::flush(std::cout);
                            //singleCtrl -> SendCard
                            current_center->singleCtrl->SendCard();
                            WidgetArgPackage *PlayerCardArg = new WidgetArgPackage();
                            PlayerCardArg->packMessage<WidgetArgCard>(CARD_OPCODE::OUTCARD, 3, 0, 0, 0, 0, 0, current_center->singleCtrl->player_handcard, 1);
                            current_center->WidgetInterface["interfaceDealingCards"](PlayerCardArg);

                            //singleCtrl -> Ramdom start
                            int thefirst = current_center->singleCtrl->SelectStart();
                            WidgetArgPackage *CallLandlordArg = new WidgetArgPackage();
                            CallLandlordArg->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::LANDLORD, thefirst, package->profileindex, package->beannum, package->username, package->account, package->roomid);
                            current_center->WidgetInterface["interfaceCallLandlordRound"](CallLandlordArg);

                            current_center->MessageSubmit(current_center->singleCtrl->getnext(current_message));
                            break;
                        }
                        case PLAYER_OPCODE::LANDLORD:
                        {
                            if(current_center->singleCtrl->isCallLandlordRound())
                            {
                                WidgetArgPackage *CallLandlordArg = new WidgetArgPackage();
                                CallLandlordArg->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::LANDLORD, package->pos, package->profileindex, package->beannum, package->username, package->account, package->roomid, package->iscall);
                                current_center->WidgetInterface["interfaceCallLandlord"](CallLandlordArg);
                            }
                            else
                            {
                                WidgetArgPackage *BidLandlordArg = new WidgetArgPackage();
                                BidLandlordArg->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::LANDLORD, package->pos, package->profileindex, package->beannum, package->username, package->account, package->roomid, package->iscall);
                                current_center->WidgetInterface["interfaceBidForLandlord"](BidLandlordArg);
                            }

                            current_center->singleCtrl->getnext_prepare(current_message);
                            //next one
                            std::cout << "state: " << current_center->singleCtrl->state << std::endl; std::flush(std::cout);
                            if(current_center->singleCtrl->isBidLandlordRound())
                            {
                                WidgetArgPackage *nextRound = new WidgetArgPackage();
                                //int nextone = package->pos == 1 ? 3 : (package->pos == 2 ? 1 : 2);
                                int nextone = current_center->singleCtrl->nextone();
                                nextRound->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::LANDLORD, nextone, 0, 0, "", "", "", 0);
                                if(current_center->singleCtrl->isCallLandlordRound())
                                    current_center->WidgetInterface["interfaceCallLandlordRound"](nextRound);
                                else
                                    current_center->WidgetInterface["interfaceBidForLandlordRound"](nextRound);
                            }
                            sleepcp(1000);
                            MessagePackage* newmsg = current_center->singleCtrl->getnext(current_message);
                            current_center->MessageSubmit(newmsg);
                            break;
                        }
                        break;
                    }
                }
                else
                {
                    if(!current_center->socketio_client->checkConnection())
                    {
                        current_center->socketio_client->connect();
                        current_center->socketio_client->bindAction("server_response", std::bind(&MessageCenter::OnServerResponse,current_center,std::placeholders::_1));
                    }

                    switch(package->opcode)
                    {
                        case PLAYER_OPCODE::CREATE_ROOM:
                        {
                            current_center->socketio_client->create_room(package->account);
                            break;
                        }
                        case PLAYER_OPCODE::JOIN_ROOM:
                        {
                            current_center->socketio_client->join_room(package->account, package->roomid);
                            break;
                        }
                        case PLAYER_OPCODE::LEAVE_ROOM:
                        {
                            current_center->socketio_client->leave_room(package->account, package->roomid);
                            break;
                        }
                        case PLAYER_OPCODE::READY:
                        {
                            current_center->socketio_client->ready(package->account, package->roomid);
                            break;
                        }
                    }
                }
                break;
            }
            case MESSAGE_TYPE::CARD:
            {
                MessageCard *package = static_cast<MessageCard*>(current_message->package);
                if(package->singlemode)
                {
                    switch(package->opcode)
                    {
                        case CARD_OPCODE::OUTCARD:
                        {
                            std::cout << "***********************CARD CHECK**********************************" << std::endl;
                            std::cout << "bot1:   " << current_center->singleCtrl->bot1.showhandcard().to_string() << "  left:" << current_center->singleCtrl->bot1_leftcards << std::endl;
                            std::cout << "bot2:   " << current_center->singleCtrl->bot2.showhandcard().to_string() << "  left:" << current_center->singleCtrl->bot2_leftcards << std::endl;
                            std::cout << "player: " << current_center->singleCtrl->player_handcard.to_string() << "  left:" << current_center->singleCtrl->player_leftcards <<  std::endl;
                            std::cout << "*******************************************************************" << std::endl;
                            if(package->pos == 3 && !current_center->singleCtrl->PlayerCardOutCheck(package->OutCard))
                            {
                                if(package->OutCard.count())
                                    std::cout << "你出的牌管不上" << std::endl;
                                else
                                    std::cout << "此轮不能不出" << std::endl;
                                std::flush(std::cout);
                                break;
                            }
                            current_center->singleCtrl->getnext_prepare(current_message);
                            WidgetArgPackage *OutCardArg = new WidgetArgPackage();
                            OutCardArg->packMessage<WidgetArgCard>(package->opcode, package->pos, package->leftcards, package->cardtype, package->point, package->succ, package->OutCard, package->HandCard, 1);
                            current_center->WidgetInterface["interfaceOutCard"](OutCardArg);

                            //next one
                            std::cout << "isGameEnd: " << current_center->singleCtrl->isGameEnd() << std::endl;
                            std::flush(std::cout);
                            if(!current_center->singleCtrl->isGameEnd())
                            {
                                WidgetArgPackage *nextRound = new WidgetArgPackage();
                                int nextone = package->pos == 1 ? 3 : (package->pos == 2 ? 1 : 2);
                                nextRound->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::PLAY, nextone, 0, 0, "", "", "", 0);
                                current_center->WidgetInterface["interfacePlayCardRound"](nextRound);
                            }
                            sleepcp(1000);
                            MessagePackage* newmsg = current_center->singleCtrl->getnext(current_message);
                            current_center->MessageSubmit(newmsg);
                            break;
                        }
                    }
                    break;
                }
            }
            case MESSAGE_TYPE::GAME_START:
            {
                std::cout << "Game Start" << std::endl; std::flush(std::cout);
                WidgetArgPackage *GameArg = new WidgetArgPackage();
                GameArg->packMessage<WidgetArgStartGame>(
                    current_center->singleCtrl->identity1,
                    current_center->singleCtrl->identity2,
                    current_center->singleCtrl->identity3,
                    current_center->singleCtrl->player_handcard,
                    current_center->singleCtrl->final_card
                );
                current_center->WidgetInterface["interfaceStartGame"](GameArg);
                sleepcp(500);

                WidgetArgPackage *PlayCardRound = new WidgetArgPackage();
                PlayCardRound->packMessage<WidgetArgPlayer>(PLAYER_OPCODE::PLAY, current_center->singleCtrl->landlord, 0, 0, "", "", "", 0);
                current_center->WidgetInterface["interfacePlayCardRound"](PlayCardRound);
                
                current_center->MessageSubmit(current_center->singleCtrl->getnext(current_message));
                break;
            }
            case MESSAGE_TYPE::GAME_END:
            {
                WidgetArgPackage *GameEndArg = new WidgetArgPackage();
                current_center->WidgetInterface["interfaceGameEnd"](GameEndArg);
                break;
            }
            default:
            {
                std::cout << "unknown message package" << std::endl;
                std::flush(std::cout);
                break;
            }
        }

        delete current_message;
    }

    void MessageSubmit(MessagePackage* current_message)
    {
        if(current_message)
            threadpool_ptr->submit(MessageProcessing, current_message, this);
        else
        {
            std::cout << "ERROR: try to submit null message" << std::endl;
            std::flush(std::cout);
        }
    }

    void loadInterface(std::string key, WidgetInterfacePtr func_ptr)
    {
        WidgetInterface[key] = func_ptr;
    }

    void OnServerResponse(sio::event& ev){
        std::cout << "OnServerResponse \n";

        //接收消息
        const sio::message::list message_received = ev.get_message();
        std::cout << "消息大小：" << message_received.size() << std::endl;

        //必须转成特定类型的消息
        std::cout << message_received[0]->get_string() << std::endl;

        MessagePackage* rev_from_svr = NetworkRevPacker::NetworksendMessage(message_received[0]->get_string());
        MessageSubmit(rev_from_svr);
    }

    static void sleepcp(int milliseconds) // 跨平台 sleep 函数
    {
#ifdef _WIN32
        Sleep(milliseconds);
#else
        usleep(milliseconds * 1000);
#endif // _WIN32
    }

    void doInterfaceWidget(std::string func, WidgetArgPackage* package)
    {
        Runner *runner = new Runner(WidgetInterface[func], package);
        runner->start();
    }

private:
    MessageCenter()
    {
        PluginFuncVector = nullptr;
        socketio_client = new socketIOClient();
        threadpool_ptr = new ThreadPool(1);
    }
    ~MessageCenter() {};

private:
    /*插件函数注册表*/
    const std::vector<PluginFuncPtr>* PluginFuncVector;
    /*线程池*/
    ThreadPool *threadpool_ptr;
    /*状态组指针*/

    /*界面接口*/
    std::map<std::string, WidgetInterfacePtr> WidgetInterface;
    /*SocketIO客户端指针*/
    socketIOClient* socketio_client;

    static std::shared_ptr<MessageCenter> instance;
    //std::mutex _mutex;

    /*单机模式*/
    SingleGame* singleCtrl;
};

#endif // MESSAGECENTER_H
