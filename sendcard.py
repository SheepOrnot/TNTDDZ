import random  
  
# 生成1到54的所有数字  
all_numbers = list(range(1, 55))  
  
# 打乱数字顺序  
random.shuffle(all_numbers)  
  
# 分三次取出十七个数字  
group1 = all_numbers[:17]  
all_numbers = all_numbers[17:]  # 移除已经取出的数字  
  
group2 = all_numbers[:17]  
all_numbers = all_numbers[17:]  # 移除已经取出的数字  
  
group3 = all_numbers[:17]  
all_numbers = all_numbers[17:]  # 移除已经取出的数字  
  
# 剩余的三个数字作为第四组  
group4 = all_numbers  

def sendcard(group):
    Group = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    i = 0
    for i in  range(len(group)):
        #print(group[i])
        Group[group[i]] = 1
    return Group
def changetostring(Group):
    num2 = ""
    for i in range(len(Group)):
        num2 = num2+str(Group[i])
    return num2

# 打印四组数字  
print("Group 1:", group1)  
print("Group 2:", group2)  
print("Group 3:", group3)  
print("Group 4:", group4)  # 这将是剩余的三个数字


print("第一组牌",sendcard(group1))
print("第二组牌",sendcard(group2))
print("第三组牌",sendcard(group3))
print("地主牌",sendcard(group4))

print("----------------------")
print("第一组牌",changetostring(sendcard(group1)))
print("第二组牌",changetostring(sendcard(group2)))
print("第三组牌",changetostring(sendcard(group3)))
print("地主牌",changetostring(sendcard(group4)))
print("----------------------")
print("第一组牌",int(changetostring(sendcard(group1)),2))
print("第二组牌",int(changetostring(sendcard(group2)),2))
print("第三组牌",int(changetostring(sendcard(group3)),2))
print("地主牌",int(changetostring(sendcard(group4)),2))
