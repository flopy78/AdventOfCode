
class Guard:
    def __init__(self,x,y,grid):
        self.grid = grid
        self.h = len(grid)
        self.w = len(grid[0])
        self.x = x
        self.y = y
        self.direction = (0,-1)
    def move(self):
        dx,dy = self.direction
        nx,ny = self.x + dx, self.y + dy

        if nx in range(self.w) and ny in range(self.h):
            if self.grid[ny][nx] == "#":
                self.direction = (-dy,dx)
                dx,dy = self.direction
                nx,ny = self.x+dx,self.y+dy
            self.x = nx
            self.y = ny
            return True
        else:
            return False
            

with open("example.txt") as file:
    grid = file.read().split("\n")
w,h = len(grid[0]),len(grid)

guard = None

for y in range(h):
    for x in range(w):
        if grid[y][x] == "^":
            guard = Guard(x,y,grid)
            break

explored_cases = {(guard.x,guard.y)}

while guard.move():
    explored_cases.add((guard.x,guard.y))

print(len(explored_cases))

'''
for y in range(h):
    for x in range(w):
        if (x,y) in explored_cases:
            print("X",end="")
        else:
            print(grid[y][x],end="")
    print()
'''