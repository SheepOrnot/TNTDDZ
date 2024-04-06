#ifndef CARDPROCESS_H
#define CARDPROCESS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <random>

enum CardType {
    None,
    Single,
    Pair,
    ThreePair,
    ThreePair_with_Single,
    ThreePair_with_Pair,
    Straight,
    Pair_Straight,
    Bomb,
    Bomb_with_Single,
    Bomb_with_Pair,
    ThreePair_Straight,
    ThreePair_Straight_with_Single,
    ThreePair_Straight_with_Pair,
    KingBomb
};

typedef struct CardAction
{
    CardType cardtype;
    int point;
    std::bitset<54> action;
}CardAction;

typedef struct SendCardPackage
{
    std::bitset<54> p1, p2, p3, finalcard;
}SendCardPackage;

typedef std::pair<CardType, int> CardTypeStruct;
typedef std::vector<CardTypeStruct> CardTypeVector;
typedef std::pair<CardTypeVector, int> CompareResult;

typedef std::vector<CardAction> ActionVector;

//牌处理工具类
class CardProcess
{
public:
    CardProcess() = delete;
    static CompareResult CardCheck(long OutCard, long PreOutCard);
    static ActionVector EnumerateCardOutAction(std::bitset<54> Card);
    static CardTypeVector CardTypeCheck(std::bitset<54> Card);
    static int CardCheck_tiny(CardTypeStruct Card, CardTypeStruct CardPre);
    static SendCardPackage SendCard();
private:
    static void PringBukket(std::vector<std::pair<int, int>>& bukket);
};

#endif // CARDPROCESS_H
