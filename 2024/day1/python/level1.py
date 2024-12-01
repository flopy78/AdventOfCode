list1,list2 = [],[]


with open("input.txt","r") as f:
    for line in f.readlines():
        id1,id2 = map(int,line.split("   "))
        list1.append(id1)
        list2.append(id2)
total = 0
list1.sort()
list2.sort()

for id1,id2 in zip(list1,list2):
    total += abs(id1-id2)

print(total)