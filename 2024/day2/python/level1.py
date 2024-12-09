import time

start = time.time()

with open("input.txt") as file:
    n_safe = 0

    for report in file.readlines():
        levels = list(map(int,report.split(" ")))
        sign = 0

        for i in range(len(levels)-1):
            step = levels[i+1]-levels[i]
            if not abs(step) in (1,2,3):
                break
            current_sign = step/abs(step)
            if sign == 0:
                sign = current_sign
            elif sign != current_sign:
                break


        else:
            n_safe += 1
print(n_safe)

print(time.time()-start,"s")