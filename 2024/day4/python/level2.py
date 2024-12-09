import time

start = time.time()

with open("input.txt") as file:
    grid = file.read().split("\n")

h = len(grid)
w = len(grid[0])

n_xmas = 0

diag = {"M","S"}

for y in range(h):
    for x in range(w):
        if grid[y][x] == "A":
            if x in range(1,w-1) and y in range(1,h-1):
                diag1 = {grid[y-1][x-1],grid[y+1][x+1]}
                diag2 = {grid[y-1][x+1],grid[y+1][x-1]}
                if diag1 == diag and diag2 == diag:
                    n_xmas += 1
     
print(n_xmas)

print(time.time()-start,"s")