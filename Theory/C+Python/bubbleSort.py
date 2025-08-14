
def swap(n1,n2):
    return n2,n1

def bubbleSort(list, n):
    for i in range(n-1):
        for j in range(n-i-1):
            if list[j] > list[j+1]:
                list[j], list[j+1] = swap(list[j], list[j+1])
    return list

print(bubbleSort([4,7,3,2,7],5))
