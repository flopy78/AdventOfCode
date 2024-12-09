import time
import re

start = time.time()

mul_regex = "(mul\(\d+,\d+\)|do\(\)|don't\(\))"
nums_regex = "mul\((\d+),(\d+)\)"

with open("input.txt") as file:
    memory = file.read()
    result = re.findall(mul_regex,memory)
    output = 0
    enabled = True
    for command in result:
        if command == "do()":
            enabled = True
        elif command == "don't()":
            enabled = False
        elif enabled:
            n1,n2 = map(int,re.search(nums_regex,command).groups())
            output += n1*n2
    
    print(output)
    print(time.time()-start,"s")