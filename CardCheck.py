
CardType = {
    "None":0,
    "Single":1,
    "Pair":2,
    "ThreePair":3,
    "ThreePair_with_Single":4,
    "ThreePair_with_Pair":5,
    "Straight":6,
    "Pair_Straight":7,
    "Bomb":8,
    "Bomb_with_Single":9,
    "Bomb_with_Pair":10,
    "ThreePair_Straight":11,
    "ThreePair_Straight_with_Single":12,
    "ThreePair_Straight_with_Pair":13,
    "KingBomb":14
}

def CardTypeCheck(Card):
    if(int(Card, 2) == 0):
        return [[CardType['None'], None]]
    print(Card)
    #bukket calc
    bukket = [0] * 16                       #1-10 jqk small_king big_king
    for i in range(len(Card)):
        if(Card[i] == '0'):
            continue
        print(f"Card: {i}")
        if(i >= 48 and i <= 51):      #51504948 -> 2 -> 13
            bukket[13] += 1
        elif(i == 52):
            bukket[14] += 1         #14 -> small_king
        elif(i == 53):
            bukket[15] += 1         #15 -> big_king
        else:
            bukket[i//4] += 1       #0 -> 3;  1 -> 4; ...8 -> J 9 -> Q 10 -> K 11 -> A             

    bukket = [[count, i] for i, count in enumerate(bukket) if count != 0]
    bukket.sort(reverse=True)

    print(f"4 bukket: {bukket}")

    CardTypeResult = []

    #王炸判断
    if(bukket == [[1,15], [1,14]]):
        CardTypeResult.append([CardType['KingBomb'], bukket[0][1]])

    #关键4判断
    if(bukket[0][0] >= 4):
        if(len(bukket) == 1):
            CardTypeResult.append([CardType['Bomb'], bukket[0][1]])
        elif(len(bukket) == 2):
            if(bukket[1][0] == 4):
                CardTypeResult.append([CardType['Bomb_with_Pair'], bukket[0][1]])
            elif(bukket[1][0] == 2):
                CardTypeResult.append([CardType['Bomb_with_Single'], bukket[0][1]])
        elif(len(bukket) == 3):
            if(bukket[1][0] == 1 and bukket[2][0] == 1):
                CardTypeResult.append([CardType['Bomb_with_Single'], bukket[0][1]])
            elif(bukket[1][0] == 2 and bukket[2][0] == 2):
                CardTypeResult.append([CardType['Bomb_with_Pair'], bukket[0][1]])

    #消除4
    for i in range(len(bukket)):
        if(bukket[i][0] < 4):
            break
        bukket[i][0] -= 1
        bukket.append([1, bukket[i][1]])
    bukket.sort(reverse=True)
    print(f"3 bukket: {bukket}")

    #关键3判断
    if(bukket[0][0] >= 3):
        if(len(bukket) == 1):
            CardTypeResult.append([CardType['ThreePair'],bukket[0][1]])
        elif(len(bukket) == 2):
            if(bukket[1][0] == 1):
                CardTypeResult.append([CardType['ThreePair_with_Single'],bukket[0][1]])
            elif(bukket[1][0] == 2):
                CardTypeResult.append([CardType['ThreePair_with_Pair'],bukket[0][1]])
        else:
            CountList = [count for count,_ in bukket]
            ThreePairCount = CountList.count(3)
            PairCount = CountList.count(2)
            SingleCount = CountList.count(1)
            
            #连号检查
            succThreeCount = 1
            for i in range(len(bukket)-1):
                if(bukket[i+1][0] == 3 and bukket[i][1] == bukket[i+1][1] + 1):
                    succThreeCount += 1

            #print(f"succThreeCount:{succThreeCount}, ThreePairCount:{ThreePairCount}, PairCount:{PairCount}, SingleCount:{SingleCount}")
            if(succThreeCount >= 2):
                if(succThreeCount == ThreePairCount):
                    if(ThreePairCount == PairCount and SingleCount == 0):
                        CardTypeResult.append([CardType['ThreePair_Straight_with_Pair'],bukket[0][1]])
                    elif(ThreePairCount == SingleCount or ThreePairCount == PairCount*2 + SingleCount):
                        CardTypeResult.append([CardType['ThreePair_Straight_with_Single'],bukket[0][1]])
                    elif(PairCount == 0 and SingleCount == 0):
                        CardTypeResult.append([CardType['ThreePair_Straight'],bukket[0][1]])
                elif(succThreeCount == (ThreePairCount - succThreeCount)*3 + PairCount*2 + SingleCount):
                    CardTypeResult.append([CardType['ThreePair_Straight_with_Single'],bukket[0][1]])

    #消除3
    for i in range(len(bukket)):
        if(bukket[i][0] < 3):
            break
        bukket[i][0] -= 1
        bukket.append([1, bukket[i][1]])
    bukket.sort(reverse=True)
    #重整散牌
    for i in range(len(bukket)-1, 0, -1):
        if(bukket[i][0] > 1):
            continue
        if(bukket[i][1] == bukket[i-1][1] and bukket[i-1][0] == 1):
            bukket.pop(i)
            bukket[i-1][0] += 1
    bukket.sort(reverse=True)
    print(f"2 bukket: {bukket}")

    #关键2判断
    if(bukket[0][0] >= 2):
        if(len(bukket) == 1):
            CardTypeResult.append([CardType['Pair'],bukket[0][1]])
        elif(len(bukket) >= 3):
            CountList = [count for count,_ in bukket]
            PairCount = CountList.count(2)
            SingleCount = CountList.count(1)

            #连号检查
            succPairCount = 1
            for i in range(len(bukket)-1):
                if(bukket[i+1][0] == 2 and bukket[i][1] == bukket[i+1][1] + 1):
                    succPairCount += 1

            if(succPairCount >= 3 and succPairCount == PairCount and SingleCount == 0):
                CardTypeResult.append([CardType['Pair_Straight'],bukket[0][1]])
    
    #消除2
    for i in range(len(bukket)):
        if(bukket[i][0] < 2):
            break
        bukket[i][0] -= 1
        bukket.append([1, bukket[i][1]])
    bukket.sort(reverse=True)
    print(f"1 bukket: {bukket}")

    #关键1判断
    if(bukket[0][0] >= 1):
        if(len(bukket) == 1):
            CardTypeResult.append([CardType['Single'],bukket[0][1]])
        elif(len(bukket) >= 5):
            CountList = [count for count,_ in bukket]
            SingleCount = CountList.count(1)

            #连号检查
            succSingleCount = 1
            for i in range(len(bukket)-1):
                if(bukket[i+1][0] == 1 and bukket[i][1] == bukket[i+1][1] + 1):
                    succSingleCount += 1

            if(succSingleCount >= 5 and succSingleCount == SingleCount):
                CardTypeResult.append([CardType['Straight'],bukket[0][1]])

    if(len(CardTypeResult) == 0):
        CardTypeResult.append([CardType['None'], None])
    return CardTypeResult

def CardCheck(OutCard, PreOutCard):
    OutCard = bin(OutCard)[2:].zfill(54)[::-1]
    PreOutCard = bin(PreOutCard)[2:].zfill(54)[::-1]

    OutCardType = CardTypeCheck(OutCard)
    PreOutCardType = CardTypeCheck(PreOutCard)

    
    if(OutCardType[0][0] == CardType['None']):
        return (OutCardType, False)
    
    if(PreOutCardType[0][0] == CardType['None']):
        return (OutCardType, True)
    
    if(OutCardType[0][0] == CardType['KingBomb']):
        return (OutCardType, True)
    
    if(OutCardType[0][0] == PreOutCardType[0][0] and OutCardType[0][1] > PreOutCardType[0][1]):
        return (OutCardType, True)
    
    return (OutCardType, False)


if __name__ == "__main__":
    testOutCard = []
    testOutCard.append(int('110000000000000000000000000000000000000000000000000000', 2))    #2w
    testOutCard.append(int('000000000011111111000000000000000000000000000000000000', 2))    #4.k 4.q
    testOutCard.append(int('110000111001111110100000000000000000000000000000000000', 2))    #2w 3a 3k 3q 1j
    testOutCard.append(int('000000011101110111000000000000000000000000000000000000', 2))    #3a 3k 3q
    testOutCard.append(int('110111111000000000110000000000000000000000000000000000', 2))    #2w 32 3a 2j
    testOutCard.append(int('000111011100111100000000000000000000000000000000000000', 2))    #32 3a 2k 2q
    testOutCard.append(int('000001111111100000000000000000000000000000000000000000', 2))    #12 4a 3k
    testOutCard.append(int('000000001101111110000000000000000000000000000000000000', 2))    #2a 3k 3q
    testOutCard.append(int('111111001100101000100000000000000000000000000000000000', 2))
    testOutCard.append(int('111100001110111101100000000000000000000000000000000000', 2))
    

    testPreCard = int('000000000000000000000000000000000000000000000000000000', 2)

    result = []
    for test in testOutCard:
        result.append(CardCheck(test, testPreCard))

    for result_i in result:
        print(result_i)
        print(result_i[1])
