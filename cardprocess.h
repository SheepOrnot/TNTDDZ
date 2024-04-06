#ifndef CARDPROCESS_H
#define CARDPROCESS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

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

typedef std::pair<CardType, int> CardTypeStruct;
typedef std::vector<CardTypeStruct> CardTypeVector;
typedef std::pair<CardTypeVector, int> CompareResult;

//牌处理工具类
class CardProcess
{
public:
    CardProcess() = delete;
    static CompareResult CardCheck(long OutCard, long PreOutCard);
    //static CardTypeVector EnumerateCardOutAction(std::bitset<54> Card);
private:
    static void PringBukket(std::vector<std::pair<int, int>>& bukket);
    static CardTypeVector CardTypeCheck(std::bitset<54> Card);
};
#endif // CARDPROCESS_H
