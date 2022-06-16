import random
import time

#Creating Random IVector
def create_random_ivector(n, m):
    return [[random.randint(-25000, 25000) for i in range(n)] for i in range(m)]

#Creating Sorted IVector
def create_sorted_ivector(n, m):
    iv_array = create_random_ivector(n, m)
    for i in range(m):
        for j in range(n):
            iv_array[i][j] = (i + j) / n
    return iv_array

#Creating Reverse Sorted Random Ivector
def create_reverse_sorted_ivector(n, m):
    iv_array = create_random_ivector(n, m)
    for i in range(m):
        for j in range(n):
            iv_array[i][j] = ((m - i) + j) / n
    return iv_array

def ivector_length(vector):
    length = 0
    for i in vector:
        length += abs(i)
    return length

# insertion sort
def insertion_sort(A, l=0):
    start_insertion = time.time()
    for j in range(1, len(A)):
        key = A[j]
        i = j-1

        while i >= l and ivector_length(key) < ivector_length(A[i]) :
                A[i + 1] = A[i]
                i -= 1
        A[i + 1] = key
    end_insertion = time.time()
    #print(A)
    return end_insertion - start_insertion

# Calculating length of each vector and storing it in an array
def length_of_all_vectors(A):
    length_array = []
    for i in A:
        length_array.append(ivector_length(i))
    return length_array

# Implementing a binary search for improved insertion sort that would reduce the search from O(n) in normal insertion sort to O(logn). This would give us improvement over naive insertion sort.
def binarySearch(arr, k, low, high):
    if high <= low:
        if k > arr[low]:
            return low + 1
        else:
            return low

    mid = (low + high) // 2

    if k == arr[mid]:
        return mid + 1
    
    if k > arr[mid]:
        return binarySearch(arr, k, mid+1, high)
    
    return binarySearch(arr, k, low, mid - 1)

# TO IMPLEMENT: Improved Insertion Sort for problem 1.
def insertion_sort_im(A):
    r = len(A) - 1
    start_insertion_im = time.time()
    array_of_lengths = length_of_all_vectors(A)
    for i in range(1, r+1):
        j = i - 1
        key1 = array_of_lengths[i]
        key2 = A[i]

        location = binarySearch(array_of_lengths, key1, 0, j)

        while j >= location:
            array_of_lengths[j + 1] = array_of_lengths[j]
            A[j + 1] = A[j]
            j -= 1
        
        array_of_lengths[j+1] = key1
        A[j + 1] = key2
    del array_of_lengths
    end_insertion_im = time.time()
    #print(A)
    return end_insertion_im - start_insertion_im

# Calling Merge Sort here rather than in merge_sort because we first need to determine the array consisting of lengths of each vector
def merge_sort_algo(array_of_lengths, A):
    if len(array_of_lengths) > 1:
  
        mid = len(array_of_lengths) // 2
  
        L = array_of_lengths[:mid]
        A_left = A[:mid]
  
        R = array_of_lengths[mid:]
        A_right = A[mid:]
  
        merge_sort_algo(L, A_left)
  
        merge_sort_algo(R, A_right)
  
        i = j = k = 0
  
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                array_of_lengths[k] = L[i]
                A[k] = A_left[i]
                i += 1
            else:
                array_of_lengths[k] = R[j]
                A[k] = A_right[j]
                j += 1
            k += 1
  
        while i < len(L):
            array_of_lengths[k] = L[i]
            A[k] = A_left[i]
            i += 1
            k += 1
  
        while j < len(R):
            array_of_lengths[k] = R[j]
            A[k] = A_right[j]
            j += 1
            k += 1
    return A

# TO IMPLEMENT: Improved Merge Sort for problem 2.
def merge_sort(A):
    start_merge = time.time()
    array_of_lengths = length_of_all_vectors(A)
    merge_sort_algo(array_of_lengths, A)
    #print(merge_sort_algo(array_of_lengths, A))
    end_merge = time.time()
    return end_merge - start_merge
    
#Below is used to calculate time
"""
#k = create_random_ivector(10, 5000)
#print(k)
#print(insertion_sort_im(k))
#print(merge_sort(k))

n_array1 = [1000, 2500, 5000, 10000, 25000, 50000, 100000, 250000]
m_array1 = [10, 25, 50]
n_array = [10, 20]
m_array = [5, 6]

#for m in m_array1:
for n in n_array1:
    average1 = 0
    average2 = 0
    average3 = 0
    #for i in range(10):
        #arr = create_random_ivector(m, n)
        #average1 += insertion_sort(arr)
        #average2 += insertion_sort_im(arr)
        #average3 += merge_sort(arr)    
    arr = create_reverse_sorted_ivector(50, n)
    #average1 += insertion_sort(arr)
    average2 += insertion_sort(arr)
    #average3 += merge_sort(arr)
    #print("For naive insertion, m " + str(m) + " and n " + str(n) + " time- " +str(average1))
    print("For naive insertion sort, m " + str(50) + " and n " + str(n) + " time- " +str(average2))
    #print("For merge, m " + str(m) + " and n " + str(n) + " time- " + str(average3))
"""