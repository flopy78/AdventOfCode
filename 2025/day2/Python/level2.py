import re
import time
def parse_input(line):
    ranges_list = line.split(",")
    return [(l.split("-")[0],l.split("-")[1]) for l in ranges_list]

def is_invalid_id(id):
    for d in range(1,len(id)//2+1):
        if len(id)%d!=0:
            continue
        if re.match("^("+id[:d]+"){2,}$",id) != None:
            return True
    return False




start = time.time()
with open("input.txt","r") as file:

    line = file.readline() 
    data = parse_input(line)
    answer = 0
    for lower,higher in data:
        for i in range(int(lower),int(higher)+1):
            if is_invalid_id(str(i)):
                #print(i)
                answer += i
    print(answer)
print(time.time()-start)


