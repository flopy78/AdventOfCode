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
while " " in disk:
    print(disk.count(" "))
    if disk[-1] != " ":
        disk[disk.index(" ")] = disk[-1]
    del disk[-1]
checksum = 0
for i in range(len(disk)):
    checksum += i*disk[i]
print(checksum)
    

        