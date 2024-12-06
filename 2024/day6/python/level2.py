
class Guard:
    def __init__(self,x,y,grid):
        self.grid = grid.copy()
        self.h = len(grid)
        self.w = len(grid[0])
        self.x = x
        self.y = y
        self.direction = (0,-1)
        self.x0 = self.x
        self.y0 = self.y
        self.direction0 = self.direction
    def reset_pos(self):
        self.x = self.x0
        self.y = self.y0
        self.direction = self.direction0
    def move(self):
        dx,dy = self.direction
        nx,ny = self.x + dx, self.y + dy

        if nx in range(self.w) and ny in range(self.h):
            while self.grid[ny][nx] == "#":
                self.direction = (-dy,dx)
                dx,dy = self.direction
                nx,ny = self.x+dx,self.y+dy
            self.x = nx
            self.y = ny
            return True
        else:
            return False
            

with open("input.txt") as file:
    grid = file.read().split("\n")
    grid = [list(line) for line in grid]
w,h = len(grid[0]),len(grid)

guard = None

for y in range(h):
    for x in range(w):
        if grid[y][x] == "^":
            guard = Guard(x,y,grid)
            break

explored_cases = set()

while guard.move():
    explored_cases.add((guard.x,guard.y))

n_looping_pos = 0
i = 0

for ox,oy in explored_cases:
    guard.grid[oy][ox] = "#"
    guard.reset_pos()
    #print(guard.x,guard.y,guard.direction)
    records = set()
    can_loop = False
    while guard.move():
        if (guard.x,guard.y,guard.direction) in records:
            can_loop = True
            break
        records.add((guard.x,guard.y,guard.direction))
    guard.grid[oy][ox] = "."
    if can_loop:
        #print(ox,oy)
        n_looping_pos += 1
    i += 1
    
    print(i)
print(n_looping_pos)




