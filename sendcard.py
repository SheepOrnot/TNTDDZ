import random  
  


def transfercard(group):
    
    string = ""
    for i in range(1, 55):
        if i in group:
            string += "1"
        else:
            string += "0"
    return string



