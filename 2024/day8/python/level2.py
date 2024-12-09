import time

start = time.time()

def get_antinodes(antennas,frequency,new_antenna,grid):
    new_antinodes = set()
    w,h = len(grid[0]),len(grid)
    for antenna in antennas[frequency]:
        dx = new_antenna[0] - antenna[0]
        dy = new_antenna[1] - antenna[1]
        step = 0
        while new_antenna[0]+step*dx in range(w) and new_antenna[1]+step*dy in range(h):
            new_antinodes.add((new_antenna[0]+step*dx,new_antenna[1]+step*dy))
            step += 1
        step = 0
        while antenna[0]-step*dx in range(w) and antenna[1]-step*dy in range(h):
            new_antinodes.add((antenna[0]-step*dx,antenna[1]-step*dy))
            step += 1
    return new_antinodes




antennas = {}
antinodes = set()
with open("input.txt") as file:
    grid = file.read().split("\n")
    for y in range(len(grid)):
        for x in range(len(grid[y])):
            if grid[y][x] != ".":
                if grid[y][x] in antennas.keys():
                    antinodes |= get_antinodes(antennas,grid[y][x],(x,y),grid)
                    antennas[grid[y][x]].append((x,y))
                else:
                    antennas[grid[y][x]] = [(x,y)]
    print(len(antinodes))                    
print(time.time()-start,'s')