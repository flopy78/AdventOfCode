import time

start = time.time()

with open("input.txt") as file:
    memory = file.read()
    disk = []
    _id = 0
    for i in range(len(memory)):
        if i%2==0:
            disk += [_id]*int(memory[i])
            _id += 1
        else:
            disk += [" "]*int(memory[i])
blank_idx = 0
#n_spaces = disk.count(" ")
#i = 0
while " " in disk:
    while disk[blank_idx] != " ":
        blank_idx += 1
    if disk[-1] != " ":
        disk[blank_idx] = disk[-1]
    del disk[-1]
    #i += 1
    #print(i,"/",n_spaces)
checksum = 0
for i in range(len(disk)):
    checksum += i*disk[i]
print(checksum)
print(time.time()-start,"s")
    

        