import time

start = time.time()

def is_well_ordered(update,must_be_after):
    seen_before = []   
    well_ordered = True

    for n in update:
        if n in must_be_after.keys():
            for m in must_be_after[n]:
                if m in seen_before:
                    well_ordered = False
        seen_before.append(n)

    return well_ordered

with open("input.txt") as file:
    part = 1
    must_be_after = {}
    sum_mid_pages= 0

    for line in file.read().split("\n"):
        if line == '':
            part = 2
        elif part == 1:
            X,Y = map(int,line.split("|"))

            if X in must_be_after.keys():
                must_be_after[X].append(Y)
            else:
                must_be_after[X] = [Y]
        elif part == 2:
            update = list(map(int,line.split(",")))
            if is_well_ordered(update,must_be_after):
                sum_mid_pages += update[int(len(update)/2)]
    print(sum_mid_pages)
    print(time.time()-start,"s")