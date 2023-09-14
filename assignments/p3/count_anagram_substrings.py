def count_anagram_substrings(T, S):
    '''
    Input:  T | String
            S | Tuple of strings S_i of equal length k < |T|
    Output: A | Tuple of integers a_i:
              | the anagram substring count of S_i in T
    '''
    A = []
    ##################
    # YOUR CODE HERE #
    ##################
    k = len(S[0])
    record = {}
    for i in range(0, len(T) - k + 1):
        R = bucket_sort(T[i:i + k])
        if R not in record:
            record[R] = 1
        else:
            record[R] += 1
    for s in S:
        R = bucket_sort(s)
        if R in record:
            A.append(record[R])
        else:
            A.append(0)
    return tuple(A)

def bucket_sort(T):
    A = [0] * 26
    for t in T:
        A[ord(t) - 97] += 1
    S = ""
    for i in range(26):
        S += chr(i + 97) * A[i]
    return S
    