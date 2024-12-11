import time

start = time.time()


with open("example.txt") as file:
    stones = list(map(int,file.read().split()))
    
for i in range(6):
    new_stones = []
    for k in range(len(stones)):
        if stones[k] == 0:
            new_stones.append(1)
        elif len(str(stones[k]))%2==0:
            digits = str(stones[k])
            new_stones.append(int(digits[0:len(digits)//2]))
            new_stones.append(int(digits[len(digits)//2:len(digits)]))
        else:
            new_stones.append(stones[k]*2024)
    #print(i)
    stones = new_stones
    print(stones)
print(len(stones))

    


print(time.time()-start,"s")