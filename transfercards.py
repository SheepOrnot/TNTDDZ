import sendcard
def transfer_int_to_str(cards):
    print("--------------",cards)
    # 首先将整数转换为二进制字符串  
    binary_str = bin(cards)
    binary_str = binary_str.lstrip('0b')
    print("--------------",binary_str)
    # 计算二进制字符串的长度  
    length = len(binary_str)  
      
    # 如果长度小于54，左侧用零填充至54位  
    if length < 54:  
        binary_str = '0' * (54 - length) + binary_str  
      
    return binary_str  
def add_cards(str1,str2):
        # 确保两个字符串长度相同  
    if len(str1) != len(str2):  
        raise ValueError("The strings must be of the same length.")  
      
    # 初始化结果字符串  
    result = ""  
      
    # 遍历字符串的每一位  
    for char1, char2 in zip(str1, str2):  
        # 将字符转换为整数进行按位或运算，然后再转回字符  
        result += str(int(char1) | int(char2))  
      
    return result  
