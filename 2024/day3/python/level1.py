import re

get_mul = "^(mul\(\d+,\d+\))"
get_nums = "^mul\((\d+),(\d+)\)"

with open("input.txt") as file:
    memory = file.read()
    compute = 0

    for i in range(len(memory)):
        result = re.search(get_mul,memory[i:])
        if result is not None:
            mul = result.groups()[0]
            nums = re.search(get_nums,mul).groups()
            compute += int(nums[0])*int(nums[1])
    print(compute)

