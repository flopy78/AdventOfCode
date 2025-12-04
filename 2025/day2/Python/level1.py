import re

def parse_input(line):
    ranges_list = line.split(",")
    return [(l.split("-")[0],l.split("-")[1]) for l in ranges_list]

def is_invalid_id(id):
    regexp = ""
    if len(id)%2 == 1:
        return False
    return (id[:len(id)//2]==id[len(id)//2:])



with open("input.txt","r") as file:
    line = file.readline() 
    data = parse_input(line)
    answer = 0
    for lower,higher in data:
        for i in range(int(lower),int(higher)+1):
            if is_invalid_id(str(i)):
                answer += i
    print(answer)




