#ifndef NETWORKSTATE_H
#define NETWORKSTATE_H

#include "common.h"

class NetworkState
{
public:
    static std::shared_ptr<NetworkState> getInstance() {return instance;}
    static void destoryInstance(NetworkState* x) {delete x;}

    void setpos(int seat)
    {
        net2wid[1] = seat == 1 ? 3 : (seat == 2 ? 1 : 2);
        net2wid[2] = seat == 1 ? 2 : (seat == 2 ? 3 : 1);
        net2wid[3] = seat == 1 ? 1 : (seat == 2 ? 2 : 3);
    }
    int net2wid[4];


    //login
    std::string account;
    std::string username;
    int diamond;
    int peas;
    int profile;

    //room
    std::string roomid;
    int seat;
    int inroom = 0;
    int inroom_up = 0;
    int inroom_down = 0;

    //playinfo
    std::string username_up;
    std::string username_down;
    std::string account_up;
    std::string account_down;
    int peas_up;
    int peas_down;
    int profile_up;
    int profile_down;

    //gameinfo
    int lord;
    int double_score;
    std::bitset<54> handcards;
    std::bitset<54> lordcards;
    std::bitset<54> outcards;
    int leftcard;
    std::string identity1;
    std::string identity2;
    std::string identity3;
    int hide;
    int thefirst;

    int curr_is_rob_stage;
    int curr_decision;
    int curr_seat;
    int next_is_rob_stage;
    int next_seat;
    int cards_type;


    //end
    int win_result;
    int change_peas;
    int new_peas;
    int times = 1;
    int Score1 = 0;
    int Score2 = 0;
    int Score3 = 0;



private:
    NetworkState(){};
    static std::shared_ptr<NetworkState> instance;

};

#endif // NETWORKSTATE_H
