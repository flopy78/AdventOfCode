import time

start = time.time()

sum_scores = 0

def get_score(hike_map,w,h,x,y):
    directions = {(0,1),(0,-1),(1,0),(-1,0)}
    opened_set = [(x,y)]
    n_paths = 0
    while opened_set:
        new_set = []

        for step_x,step_y in opened_set:
            for dx,dy in directions:
                new_x,new_y = step_x + dx, step_y + dy
                if new_x in range(w) and new_y in range(h):
                    if int(hike_map[new_y][new_x]) - int(hike_map[step_y][step_x]) == 1:
                        new_set.append((new_x,new_y))
                        if hike_map[new_y][new_x] == "9":
                            n_paths += 1
        opened_set = new_set
    return n_paths



with open("input.txt") as file:
    hike_map = file.read().split("\n")

w,h = len(hike_map[0]),len(hike_map)

for y in range(h):
    for x in range(w):
        if hike_map[y][x] == "0":
            sum_scores += get_score(hike_map,w,h,x,y)
print(sum_scores)
print(time.time()-start,"s")
