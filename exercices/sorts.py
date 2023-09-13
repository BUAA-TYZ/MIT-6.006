def selection_sort(A):
    for i in range(len(A) - 1, 0, -1):
        m = i
        for j in range(i):
            if A[m] < A[j]:
                m = j
        A[m], A[i] = A[i], A[m]

def find_max_index(A):
    l = len(A)
    if l <= 1:
        return 0
    m = find_max_index(A[:l - 1])
    return m if A[m] > A[l - 1] else l - 1

def selection_sort_recursive(A, i):
    if i == 0:
        return
    m = find_max_index(A[:i])
    if A[m] > A[i]:
        A[m], A[i] = A[i], A[m]
    selection_sort_recursive(A, i - 1)

def merge_sort(A, a = 0, b = None):
    if b is None:
        b = len(A)
    if 1 < b - a:
        c = (a + b + 1) // 2
        merge_sort(A, a, c)
        merge_sort(A, c, b)
        L, R = A[a:c], A[c:b]
        i, j = 0, 0
        while a < b:
            if (j >= len(R)) or (i < len(L) and L[i] < R[j]):
                A[a] = L[i]
                i = i + 1
            else:
                A[a] = R[j]
                j = j + 1
            a = a + 1

def main():
    A = [i for i in range(10, 0, -1)]
    merge_sort(A)
    print(A)

if __name__ == "__main__":
    main()