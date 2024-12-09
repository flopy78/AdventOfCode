import time

start = time.time()

list1,list2 = [],[]

def quicksort(array):
    if len(array) <= 1:
        return array

    pivot = array[0]
    upper = []
    lower = []
    equal = []

    for elt in array:
        if elt < pivot:
            lower.append(elt)
        elif elt > pivot:
            upper.append(elt)
        else:
            equal.append(elt)
    
    return quicksort(lower) + equal + quicksort(upper)

with open("input.txt","r") as f:
    for line in f.readlines():
        id1,id2 = map(int,line.split("   "))
        list1.append(id1)
        list2.append(id2)
total = 0
list1 = quicksort(list1)#list1.sort()
list2 = quicksort(list2) #list2.sort()

for id1,id2 in zip(list1,list2):
    total += abs(id1-id2)

print(total)

print(time.time()-start,"s")