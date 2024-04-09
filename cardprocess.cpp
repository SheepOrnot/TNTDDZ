#include "cardprocess.h"
//#define debug

void CardProcess::PringBukket(std::vector<std::pair<int, int>>& bukket)
{
    for(int i = 0; i < bukket.size(); i ++)
    {
        std::cout << "(" << bukket[i].first << " " << bukket[i].second << ") ";
    }
    std::cout << std::endl;
}

CardTypeVector CardProcess::CardTypeCheck(std::bitset<54> Card) {
    #define CARD_STRUCT(type, point, succ) CardTypeStruct(type, point, succ)
    #define INSERT_RESULT(type) CardTypeResult.push_back(CARD_STRUCT(CardType::type, bukket[0].second, 1))
    #define INSERT_RESULT_SUCC(type, succ) CardTypeResult.push_back(CARD_STRUCT(CardType::type, bukket[0].second, succ))
    #define LEN(v) v.size()    
    
    CardTypeVector CardTypeResult;
    if(Card.to_ullong() == 0)
    {
        CardTypeResult.push_back(CARD_STRUCT(CardType::None, 0, 1));
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

#ifdef debug
    std::cout << "4 bukket: ";
    PringBukket(bukket);
#endif

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

#ifdef debug
    std::cout << "3 bukket: ";
    PringBukket(bukket);
#endif

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

            #ifdef debug
            printf("succThreeCount:%d, ThreePairCount:%d, PairCount:%d, SingleCount:%d\n", succThreeCount, ThreePairCount, PairCount, SingleCount);
            #endif

            if(succThreeCount != 1)
            {
                if(succThreeCount == ThreePairCount)
                {
                    if(ThreePairCount == PairCount && SingleCount == 0)
                        INSERT_RESULT_SUCC(ThreePair_Straight_with_Pair, succThreeCount);
                    else if(ThreePairCount == PairCount*2 + SingleCount)
                        INSERT_RESULT_SUCC(ThreePair_Straight_with_Single, succThreeCount);
                    else if(PairCount == 0 && SingleCount == 0)
                        INSERT_RESULT_SUCC(ThreePair_Straight, succThreeCount);
                }
                else if(succThreeCount == (ThreePairCount - succThreeCount)*3 + PairCount*2 + SingleCount)
                    INSERT_RESULT_SUCC(ThreePair_Straight_with_Single, succThreeCount);
            }
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

#ifdef debug
    std::cout << "2 bukket: ";
    PringBukket(bukket);
#endif

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

            if(succPairCount >= 3 && succPairCount == PairCount && SingleCount == 0)
                INSERT_RESULT_SUCC(Pair_Straight, succPairCount);
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

#ifdef debug
    std::cout << "1 bukket: ";
    PringBukket(bukket);
#endif

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

            if(succSingleCount >= 5 && succSingleCount == SingleCount)
                INSERT_RESULT_SUCC(Straight, succSingleCount);
        }
    }

    if(LEN(CardTypeResult) == 0)
        CardTypeResult.push_back(CARD_STRUCT(CardType::None, 0, 1));
    return CardTypeResult;
}

CompareResult CardProcess::CardCheck(long long OutCard, long long PreOutCard) {
    CardTypeVector OutCardType = CardTypeCheck(std::bitset<54>(OutCard));
    CardTypeVector PreOutCardType = CardTypeCheck(std::bitset<54>(PreOutCard));

    if(OutCardType[0].cardtype == CardType::None)
        return std::make_pair(OutCardType, 0);
    
    if(PreOutCardType[0].cardtype == CardType::None)
        return std::make_pair(OutCardType, 1);
    
    if(OutCardType[0].cardtype == CardType::KingBomb)
        return std::make_pair(OutCardType, 1);

    if(OutCardType[0].cardtype == CardType::Bomb)
        return std::make_pair(OutCardType, !(PreOutCardType[0].cardtype == CardType::Bomb && PreOutCardType[0].point > OutCardType[0].point));
    
    if(OutCardType[0].cardtype == PreOutCardType[0].cardtype &&
       OutCardType[0].succ  == PreOutCardType[0].succ  && 
       OutCardType[0].point > PreOutCardType[0].point)
        return std::make_pair(OutCardType, 1);
    
    return std::make_pair(OutCardType, 0);

}

int CardProcess::CardCheck_tiny(CardTypeStruct Card, CardTypeStruct CardPre)
{
    if(Card.cardtype == CardType::None)
        return 0;
    
    if(CardPre.cardtype == CardType::None)
        return 1;
    
    if(Card.cardtype == CardType::KingBomb)
        return 1;
    
    if(Card.cardtype == CardType::Bomb)
        return !(CardPre.cardtype == CardType::Bomb && CardPre.point > Card.point);

    if(Card.cardtype == CardPre.cardtype &&
       Card.succ  == CardPre.succ  && 
       Card.point > CardPre.point)
        return 1;
    
    return 0;
}

ActionVector CardProcess::EnumerateCardOutAction(std::bitset<54> Card)
{
    ActionVector Action;
    unsigned long long Count = Card.count();
    
    //build mapping: 
    std::vector<int> mapping;
    for(int i = 0; i < 54; i ++)
    {
        if(Card[i] == 1) mapping.push_back(i);
    }

    for(unsigned long long i = 0; i < (1<<mapping.size()); i ++)
    {
        std::bitset<54> selected;
        unsigned long long x = i;
        int j = 0;
        while(x)
        {
            if(x&1) selected[mapping[j]] = 1;
            j ++;
            x >>= 1;
        }

        CardTypeVector results = CardTypeCheck(selected);
        for(auto& result : results)
        {
            //if(result.first == 0) continue;
            CardAction action(result.cardtype, result.point, result.succ, selected);
            Action.push_back(action);
        }
    }

    if(Action.size() == 0)
    {
        CardAction action = {CardType::None, 0, 1, 0};
        Action.push_back(action);
    }

    return Action;
}

SendCardPackage CardProcess::SendCard()
{
    int card[54];
    for(int i = 0; i < 54; i ++ ) card[i] = i;

    std::random_device rd;
    std::default_random_engine rng(rd());

    // 使用 std::shuffle 打乱数组
    std::shuffle(card, card + 54, rng);

    SendCardPackage package;
    std::bitset<54> someone_card;
    for(int i = 0; i < 17; i ++) someone_card[card[17*0 + i]] = 1;
    package.p1 = someone_card;

    someone_card = 0;
    for(int i = 0; i < 17; i ++) someone_card[card[17*1 + i]] = 1;
    package.p2 = someone_card;

    someone_card = 0;
    for(int i = 0; i < 17; i ++) someone_card[card[17*2 + i]] = 1;
    package.p3 = someone_card;
    
    someone_card = 0;
    for(int i = 0; i < 3; i ++) someone_card[card[17*3 + i]] = 1;
    package.finalcard = someone_card;

    return package;
}

/*
int main() {
    std::vector<long long> testOutCard;
    testOutCard.push_back(0b110000000000000000000000000000000000000000000000000000);    //2w
    testOutCard.push_back(0b000000000011111111000000000000000000000000000000000000);    //4.k 4.q
    testOutCard.push_back(0b110000111001111110100000000000000000000000000000000000);    //2w 3a 3k 3q 1j
    testOutCard.push_back(0b000000011101110111000000000000000000000000000000000000);    //3a 3k 3q
    testOutCard.push_back(0b110111111000000000110000000000000000000000000000000000);    //2w 32 3a 2j
    testOutCard.push_back(0b000111011100111100000000000000000000000000000000000000);    //32 3a 2k 2q
    testOutCard.push_back(0b000001111111100000000000000000000000000000000000000000);    //12 4a 3k
    testOutCard.push_back(0b000000001101111110000000000000000000000000000000000000);    //2a 3k 3q
    testOutCard.push_back(0b111111001100101000100000000000000000000000000000000000);
    testOutCard.push_back(0b111100001110111101100000000000000000000000000000000000);
    long long testPreCard    = 0b000000000000000000000000000000000000000000000000000000;

    std::vector<CompareResult> result;
    for (long long test : testOutCard) {
        result.push_back(CardProcess::CardCheck(test, testPreCard));
    }

    for (auto& result_i : result) {
        for (auto& card_type : result_i.first) {
            std::cout << "(" << card_type.first << ", " << card_type.second << ") ";
        }
        std::cout << (result_i.second ? "true" : "false") << std::endl;
    }

#ifndef debug
    ActionVector Action = CardProcess::EnumerateCardOutAction(0b111111111111111111110000000000000000000000000000000000);
    for(auto k : Action)
    {
        std::cout << "(" << k.cardtype << "," << k.point << ") " << k.action.to_string() << std::endl;
    }
#endif

    return 0;
}
*/
