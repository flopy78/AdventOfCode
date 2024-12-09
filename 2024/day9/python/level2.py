import time

start = time.time()

files = {}

with open("input.txt") as file:
    memory = file.read()
    disk = []
    _id = 0
    for i in range(len(memory)):
        if i%2==0:
            disk.append((_id,int(memory[i])))
            files[_id] = int(memory[i]) 
            _id += 1
        else:
            if int(memory[i]) > 0:
                disk.append((".",int(memory[i])))

#print(display(disk))
l = None
for i in reversed(range(_id)):
    blank_idx = 0
    is_movable = False
    file_idx = disk.index((i,files[i]))
    while blank_idx < len(disk):
        if disk[blank_idx][0] == "." and disk[blank_idx][1] >= files[i] and blank_idx < file_idx:
            is_movable = True
            break
        blank_idx += 1

    if is_movable:
        disk[blank_idx] = (".",disk[blank_idx][1]-files[i])
        '''if disk[blank_idx][1] == 0:
            del disk[blank_idx]'''
        file_idx = disk.index((i,files[i]))
        if blank_idx < file_idx:
            disk[file_idx] = ('.',files[i])
            disk.insert(blank_idx,(i,files[i]))


idx = 0
checksum = 0

for element in disk:
    for i in range(element[1]):
        if element[0] != ".":
            checksum += element[0]*idx
        idx += 1
print(checksum)
print(time.time() - start)