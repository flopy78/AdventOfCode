with open("input.txt") as file:
    grid = file.read().split("\n")

h = len(grid)
w = len(grid[0])
n_xmas = 0

DIRS = [(0,1),
        (0,-1),
        (1,0),
        (-1,0),
        (1,1),
        (-1,1),
        (1,-1),
        (-1,-1)]

word = "XMAS"

for y in range(h):
    for x in range(w):
        if grid[y][x] == "X":
            directions = DIRS.copy()

            for step in range(1,4):
                directions_left = []
                for dx,dy in directions:
                    nx = x + step*dx
                    ny = y + step*dy
                    if nx in range(w) and ny in range(h):
                        if grid[ny][nx] == word[step]:
                            directions_left.append((dx,dy))
                directions = directions_left
            n_xmas += len(directions)
print(n_xmas)

