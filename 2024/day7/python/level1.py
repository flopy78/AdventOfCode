import itertools

def compute(terms,ops):
    compute = terms[0]
    for term,op in zip(terms[1:],ops):
        if op == "*":
            compute *= term
        elif op == "+":
            compute += term
        elif op == "s":
            compute = int(str(compute)+str(term))
    return compute


def is_solvable(result,terms):
    combinations = itertools.product("+*",repeat=len(terms)-1)
    for ops in combinations:
        if compute(terms,list(ops)) == result:
            return True
    return False


equations = {}
with open("input.txt") as file:
    for line in file.read().split("\n"):
        result,terms = line.split(": ")
        terms = list(map(int,terms.split(" ")))
        equations[int(result)] = terms

calib_score = 0


for result,terms in equations.items():
    if is_solvable(result,terms):
        calib_score += result
print(calib_score)
