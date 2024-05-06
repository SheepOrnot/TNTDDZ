#ifndef SOCKETIOCLIENT_H
#define SOCKETIOCLIENT_H

#include "common.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32

using namespace sio;

class socketIOClient
{
private:
    socket::ptr current_socket;
    client h;

public:
    socketIOClient(){
        current_socket = nullptr;
    }

    void sleepcp(int milliseconds) // 跨平台 sleep 函数
    {
#ifdef _WIN32
        Sleep(milliseconds);
#else
        usleep(milliseconds * 1000);
#endif // _WIN32
    }

    void create_room(std::string account)
    {
        std::string data_json = "{\"account\":\"" + account + "\"}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("create_room", data);
    }

    void join_room(std::string account, std::string roomid)
    {
        std::string data_json = "{\"account\":\"" + account + "\","
                                + "\"roomid\":\""  + roomid  + "\"}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("join_room", data);
    }

    void leave_room(std::string account, std::string roomid)
    {
        std::string data_json = "{\"account\":\"" + account + "\","
                                + "\"roomid\":\""  + roomid  + "\"}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("leave_room", data);
    }

    void ready(std::string account, std::string roomid, int seat)
    {
        std::string data_json = "{\"account\":\"" + account + "\","
                                + "\"seat\":"     + std::to_string(seat) + ","
                                + "\"roomid\":\"" + roomid  + "\"}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("ready", data);
    }

    void ask_or_rob(std::string account, std::string roomid, int seat, int lord, int rob)
    {
        std::string data_json = "{\"account\":\"" + account + "\","
                                + "\"roomid\":\"" + roomid  + "\","
                                + "\"seat\":"     + std::to_string(seat) + ","
                                + "\"lord\":"     + std::to_string(lord) + ","
                                + "\"rob\":"      + std::to_string(rob)  + "}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("ask_or_rob", data);
    }

    void Double(std::string roomid, int seat, int Double)
    {
        std::string data_json = "{\"roomid\":\"" + roomid  + "\","
                                + "\"seat\":"    + std::to_string(seat) + ","
                                + "\"double\":"  + std::to_string(Double)  + "}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("double", data);
    }

    void output_handcards(std::string roomid, int seat, long long outputcards)
    {
        std::string data_json = "{\"roomid\":\"" + roomid  + "\","
                                + "\"seat\":"    + std::to_string(seat) + ","
                                + "\"outputcards\":"  + std::to_string(outputcards)  + "}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("output_handcards", data);
    }

    void bigger_cards(std::string account, std::string roomid, int seat, long long outcards, long long tablecards, int canorcannot)
    {
        std::string data_json = "{\"account\":\"" + account + "\","
                                + "\"roomid\":\"" + roomid  + "\","
                                + "\"seat\":"     + std::to_string(seat) + ","
                                + "\"outputcards\":" + std::to_string(outcards) + ","
                                + "\"tablecards\":"  + std::to_string(tablecards) + ","
                                + "\"canorcannot\":" + std::to_string(canorcannot)  + "}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("bigger_cards", data);
    }

    void timeout(std::string account, std::string roomid, int seat)
    {
        std::string data_json = "{\"account\":\"" + account + "\","
                                + "\"roomid\":\"" + roomid  + "\","
                                + "\"seat\":"     + std::to_string(seat)  + "}";
        std::cout << "Sending: " << data_json << std::endl;
        message::list data(data_json);
        current_socket->emit("timeout", data);
    }

    void connect()
    {
        h.connect("http://" + SERVER_IP + ":" + SERVER_PORT);

        current_socket = h.socket();

        std::cout << "Connecting..." << std::endl;
        sleepcp(1000);

        std::cout << "Hello World!" << std::endl;
    }

    void close()
    {
        h.sync_close();
        h.clear_con_listeners();
    }

    bool checkConnection()
    {
        return h.opened();
    }

    void bindAction(std::string name, std::function<void(event& event)> func)
    {
        current_socket->on(name, func);
    }

};


#endif // SOCKETIOCLIENT_H
