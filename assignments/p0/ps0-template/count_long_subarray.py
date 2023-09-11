def count_long_subarray(A):
    '''
    Input:  A     | Python Tuple of positive integers
    Output: count | number of longest increasing subarrays of A
    '''
    max_length_count = 1
    length = len(A)
    if length == 0:
        return
    ##################
    # YOUR CODE HERE #
    ##################
    local_max_length = 1
    global_max_length = 1
    for i in range(1, length):
        if A[i] > A[i - 1]:
            local_max_length += 1
        else:
            local_max_length = 1
        if local_max_length == global_max_length:
            max_length_count += 1
        elif local_max_length > global_max_length:
            global_max_length = local_max_length
            max_length_count = 1
    return max_length_count
