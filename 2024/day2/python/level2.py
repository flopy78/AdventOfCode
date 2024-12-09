import time

start = time.time()

def is_safe(steps):
    if not all(steps):
        return False
    if not (all([x>0 for x in steps]) or all([x<0 for x in steps])):
        return False
    abs_steps = [abs(x) for x in steps]
    if abs(max(abs_steps)) > 3 or abs(min(abs_steps)) < 1:
        return False
    return True

def remove_step(steps,i):
   
    new_steps = []

    for j in range(len(steps)):
        if j == i:
            if i!=0:
                new_steps[-1] += steps[i]
        else:
            new_steps.append(steps[j])
    return new_steps

def get_steps(levels):
    steps = []

    for i in range(len(levels)-1):
        steps.append(levels[i+1]-levels[i])
    
    return steps

with open("input.txt") as file:
    n_safe = 0
    n_direct_safe = 0

    for report in file.readlines():
        levels = list(map(int,report.split(" ")))
        steps = get_steps(levels)
        safe = False

        if is_safe(steps):
            n_direct_safe += 1
            safe = True
        else:
            safe = False
            for i in range(len(steps)):
                #print(steps,remove_step(steps,i))
                if is_safe(remove_step(steps,i)):
                    safe = True
                    break
            if is_safe(steps[:-1]):
                safe = True
        if safe:
            n_safe += 1

 
print(n_safe)

print(time.time()-start,"s")
