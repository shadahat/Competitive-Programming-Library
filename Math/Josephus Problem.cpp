/***
            1
        8       2
    7               3
        6       4
            5

    N person ar standing in a circular fashion above. Person 1
    moves first. Starting from person 1, everyone kills the alive
    person next to him.
    SO, they will be killed in the following order
    2, 4, 6, 8, 3, 7, 5 and person 1 will servive.

    For any N, N can be written as
    N = 2^a + L where (L>=0 and a is as large as possible)

    The the surviver J(N) = 2*L + 1
    Because if N is a power of two, surviver J(N) = 1.

    J(2*N) = 2*J(N) + 1  [ for N >= 1 ]

**/
