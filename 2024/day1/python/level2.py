import time

start = time.time()

list1,list2 = [],[]

count = {}

with open("input.txt","r") as f:
    for line in f.readlines():
        id1,id2 = map(int,line.split("   "))
        list1.append(id1)
        list2.append(id2)
        if id2 in count.keys():
            count[id2] += 1
        else:
            count[id2] = 1

similarity_score = 0

for id1 in list1:
    n_occurences = count[id1] if id1 in count.keys() else 0 
    similarity_score += id1*n_occurences

print(similarity_score)

print(time.time()-start,"s")
