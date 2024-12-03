import re

mul_regex = "mul\(\d+,\d+\)"
nums_regex = "mul\((\d+),(\d+)\)"

with open("input.txt") as file:
    memory = file.read()
    result = re.findall(mul_regex,memory)
    output = 0
    for mul in result:
        n1,n2 = map(int,re.search(nums_regex,mul).groups())
        output += n1*n2
    print(output)