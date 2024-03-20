#ifndef WIDGETARGCARD_H
#define WIDGETARGCARD_H

#include <bitset>
#include <vector>
class WidgetArgCard
{
public:
    WidgetArgCard();

    int opcode;
    int addition_data;
    std::bitset<54> OutCards;
    std::bitset<54> HandCards;


};

#endif // WIDGETARGCARD_H

/*
opcpde
1: 发牌
2: 获得地主牌
3: 出牌
4: 不出
6: 上家出牌 addition_data 剩余手牌
7: 下家出牌 addition_data 剩余手牌
*/
