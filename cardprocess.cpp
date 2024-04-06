#include "cardprocess.h"

void CardProcess::PringBukket(std::vector<std::pair<int, int>>& bukket)
{
    for(int i = 0; i < bukket.size(); i ++)
    {
        std::cout << "(" << bukket[i].first << " " << bukket[i].second << ") ";
    }
    std::cout << std::endl;
}

CardTypeVector CardProcess::CardTypeCheck(std::bitset<54> Card) {
#define CARD_STRUCT(type, point) std::make_pair(type, point)
#define INSERT_RESULT(type) CardTypeResult.push_back(CARD_STRUCT(CardType::type, bukket[0].second))
#define LEN(v) v.size()

    CardTypeVector CardTypeResult;
    if(Card.to_ulong() == 0)
    {
        CardTypeResult.push_back(CARD_STRUCT(CardType::None, 0));
        return CardTypeResult;
    }

    std::vector<std::pair<int, int>> bukket;    //(count, point)
    std::vector<int> count(16, 0);

    for (int i = 0; i < Card.size(); ++i)
    {
        if (Card[i] == 0) continue;
        if (i >= 48 && i <= 51) count[13] += 1;
        else if (i == 52) count[14] += 1;
        else if (i == 53) count[15] += 1;
        else count[i / 4] += 1;
    }

    for (int i = 0; i < count.size(); ++i)
    {
        if (count[i] != 0)
            bukket.push_back({count[i], i});
    }

    std::sort(bukket.rbegin(), bukket.rend());
    std::cout << "4 bukket: ";
    PringBukket(bukket);

    //王炸判断
    if(LEN(bukket) == 2 && bukket[0] == std::make_pair(1, 15) && bukket[1] == std::make_pair(1, 14))
        INSERT_RESULT(KingBomb);

    //关键4判断
    if(bukket[0].first >= 4)
    {
        if(LEN(bukket) == 1)
            INSERT_RESULT(Bomb);
        else if(LEN(bukket) == 2)
        {
            if(bukket[1].first == 4)
                INSERT_RESULT(Bomb_with_Pair);
            else if(bukket[1].first == 2)
                INSERT_RESULT(Bomb_with_Single);
        }
        else if(LEN(bukket) == 3)
        {
            if(bukket[1].first == 1 and bukket[2].first == 1)
                INSERT_RESULT(Bomb_with_Single);
            else if(bukket[1].first == 2 and bukket[2].first == 2)
                INSERT_RESULT(Bomb_with_Pair);
        }
    }

    //消除4
    for(int i = 0; i < LEN(bukket); i ++)
    {
        if(bukket[i].first < 4) break;
        bukket[i].first -= 1;
        bukket.push_back({1, bukket[i].second});
    }
    std::sort(bukket.rbegin(), bukket.rend());

    std::cout << "3 bukket: ";
    PringBukket(bukket);

    //关键3判断
    if(bukket[0].first >= 3)
    {
        if(LEN(bukket) == 1)
            INSERT_RESULT(ThreePair);
        else if(LEN(bukket) == 2)
        {
            if(bukket[1].first == 1)
                INSERT_RESULT(ThreePair_with_Single);
            else if(bukket[1].first == 2)
                INSERT_RESULT(ThreePair_with_Pair);
        }
        else
        {
            std::vector<int> CountList;
            for(int i = 0; i < LEN(bukket); i ++) CountList.push_back(bukket[i].first);

            int ThreePairCount = std::count(CountList.begin(), CountList.end(), 3);
            int PairCount = std::count(CountList.begin(), CountList.end(), 2);
            int SingleCount = std::count(CountList.begin(), CountList.end(), 1);

            //连号检查
            int succThreeCount = 1;
            for(int i = 0; i < LEN(bukket)-1; i ++ )
                if(bukket[i+1].first == 3 and bukket[i].second == bukket[i+1].second + 1)
                    succThreeCount += 1;

            //print(f"succThreeCount:{succThreeCount}, ThreePairCount:{ThreePairCount}, PairCount:{PairCount}, SingleCount:{SingleCount}")
            if(succThreeCount == ThreePairCount)
            {
                if(ThreePairCount == PairCount)
                    INSERT_RESULT(ThreePair_Straight_with_Pair);
                else if(ThreePairCount == SingleCount || ThreePairCount == PairCount*2 + SingleCount)
                    INSERT_RESULT(ThreePair_Straight_with_Single);
                else if(PairCount == 0 && SingleCount == 0)
                    INSERT_RESULT(ThreePair_Straight);
            }
            else if(succThreeCount == (ThreePairCount - succThreeCount)*3 + PairCount*2 + SingleCount)
                INSERT_RESULT(ThreePair_Straight_with_Single);
        }
    }

    //消除3
    for(int i = 0; i < LEN(bukket); i ++)
    {
        if(bukket[i].first < 3) break;
        bukket[i].first -= 1;
        bukket.push_back({1, bukket[i].second});
    }
    std::sort(bukket.rbegin(), bukket.rend());
    //重整散牌
    for(int i = LEN(bukket)-1; i > 0; i --)
    {
        if(bukket[i].first > 1) continue;
        if(bukket[i].second == bukket[i-1].second and bukket[i-1].first == 1)
        {
            bukket.erase(bukket.begin() + i);
            bukket[i-1].first += 1;
        }
    }
    std::sort(bukket.rbegin(), bukket.rend());
    std::cout << "2 bukket: ";
    PringBukket(bukket);

    //关键2判断
    if(bukket[0].first >= 2)
    {
        if(LEN(bukket) == 1)
            INSERT_RESULT(Pair);
        else if(LEN(bukket) >= 3)
        {
            std::vector<int> CountList;
            for(int i = 0; i < LEN(bukket); i ++) CountList.push_back(bukket[i].first);

            int PairCount = std::count(CountList.begin(), CountList.end(), 2);
            int SingleCount = std::count(CountList.begin(), CountList.end(), 1);

            //连号检查
            int succPairCount = 1;
            for(int i = 0; i < LEN(bukket)-1; i ++ )
                if(bukket[i+1].first == 2 and bukket[i].second == bukket[i+1].second + 1)
                    succPairCount += 1;

            if(succPairCount == PairCount && SingleCount == 0)
                INSERT_RESULT(Pair_Straight);
        }
    }

    //消除2
    for(int i = 0; i < LEN(bukket); i ++)
    {
        if(bukket[i].first < 2) break;
        bukket[i].first -= 1;
        bukket.push_back({1, bukket[i].second});
    }
    std::sort(bukket.rbegin(), bukket.rend());
    std::cout << "1 bukket: ";
    PringBukket(bukket);

    //关键1判断
    if(bukket[0].first >= 1)
    {
        if(LEN(bukket) == 1)
            INSERT_RESULT(Single);
        else if(LEN(bukket) >= 5)
        {
            std::vector<int> CountList;
            for(int i = 0; i < LEN(bukket); i ++) CountList.push_back(bukket[i].first);

            int SingleCount = std::count(CountList.begin(), CountList.end(), 1);

            //连号检查
            int succSingleCount = 1;
            for(int i = 0; i < LEN(bukket)-1; i ++ )
                if(bukket[i+1].first == 1 and bukket[i].second == bukket[i+1].second + 1)
                    succSingleCount += 1;

            if(succSingleCount == SingleCount)
                INSERT_RESULT(Straight);
        }
    }

    if(LEN(CardTypeResult) == 0)
        CardTypeResult.push_back(CARD_STRUCT(CardType::None, 0));
    return CardTypeResult;
}

CompareResult CardProcess::CardCheck(long OutCard, long PreOutCard) {
    CardTypeVector OutCardType = CardTypeCheck(std::bitset<54>(OutCard));
    CardTypeVector PreOutCardType = CardTypeCheck(std::bitset<54>(PreOutCard));

    if(OutCardType[0].first == CardType::None)
        return std::make_pair(OutCardType, 0);

    if(PreOutCardType[0].first == CardType::None)
        return std::make_pair(OutCardType, 1);

    if(OutCardType[0].first == CardType::KingBomb)
        return std::make_pair(OutCardType, 1);

    if(OutCardType[0].first == PreOutCardType[0].first and OutCardType[0].second > PreOutCardType[0].second)
        return std::make_pair(OutCardType, 1);

    return std::make_pair(OutCardType, 0);

}

/*
int main() {
    std::vector<long> testOutCard;
    testOutCard.push_back(0b110000000000000000000000000000000000000000000000000000);    //2w
    testOutCard.push_back(0b000000000011111111000000000000000000000000000000000000);    //4.k 4.q
    testOutCard.push_back(0b110000111001111110100000000000000000000000000000000000);    //2w 3a 3k 3q 1j
    testOutCard.push_back(0b000000011101110111000000000000000000000000000000000000);    //3a 3k 3q
    testOutCard.push_back(0b110111111000000000110000000000000000000000000000000000);    //2w 32 3a 2j
    testOutCard.push_back(0b000111011100111100000000000000000000000000000000000000);    //32 3a 2k 2q
    testOutCard.push_back(0b000001111111100000000000000000000000000000000000000000);    //12 4a 3k
    testOutCard.push_back(0b000000001101111110000000000000000000000000000000000000);    //2a 3k 3q

    long testPreCard = 0b000000000000000000000000000000000000000000000000000000;

    std::vector<CompareResult> result;
    for (long test : testOutCard) {
        result.push_back(CardProcess::CardCheck(test, testPreCard));
    }

    for (auto& result_i : result) {
        for (auto& card_type : result_i.first) {
            std::cout << "(" << card_type.first << ", " << card_type.second << ") ";
        }
        std::cout << (result_i.second ? "true" : "false") << std::endl;
    }

    return 0;
}
*/
