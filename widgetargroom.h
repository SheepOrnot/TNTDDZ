#ifndef WIDGETARGROOM_H
#define WIDGETARGROOM_H

#include<vector>

class WidgetArgRoom
{
public:
    WidgetArgRoom();
    int opcode;
    std::vector<int> addition_data;
    /*
1. 房间倍数改变 {倍数变化量}
2. 结算：{上家倍数，下家倍数，玩家倍数，上家豆子变化量，下家豆子变化量，玩家豆子变化量}
*/
};

#endif // WIDGETARGROOM_H
