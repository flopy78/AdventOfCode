import itertools
from time import time

def compute(terms,ops,result):
    compute = terms[0]
    for term,op in zip(terms[1:],ops):
        if op == "*":
            compute *= term
        elif op == "+":
            compute += term
        elif op == "s":
            compute = int(str(compute)+str(term))
        if compute > result:
            return compute
    return compute


def is_solvable(result,terms):
    combinations = itertools.product("+*s",repeat=len(terms)-1)
    for ops in combinations:
        if compute(terms,ops,result) == result:
            return True
    return False

start = time()
calib_score = 0

with open("input.txt") as file:
    for line in file.read().split("\n"):
        result,terms = line.split(": ")
        result = int(result)
        terms = list(map(int,terms.split(" ")))
        if is_solvable(result,terms):
            calib_score += result


print(calib_score)
print(time()-start,"s")
