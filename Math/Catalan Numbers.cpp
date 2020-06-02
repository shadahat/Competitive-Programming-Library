/***
    C_n =   C(2*n,n) - C(2*n,n+1)
        =   (1/(n+1)) * C(2*n,n)

    Here, C(n,r) denotes n Combination r

    7 * * * * * * * *
    6 * * * * * * * *
    5 * * * * * * * *
    4 * * * * * * * *
    3 * * * * * * * *
    2 * * * * * * * *
    1 * * * * * * * *
    0 * * * * * * * *
      0 1 2 3 4 5 6 7 (x-->)

    C_n =   number of paths from point (0,0) to point (n,n) in a n*n
            grid using only U and R moves where the path doesn't contain any
            point (x,y) where x<y

    Proof Using Reflection Technique

    Path Type 1 : Ways to go from (0,0) to (n,n)      = C(2*n,n)
    Path Type 2 : Ways to go from (0,0) to (n-1,n+1)  = C(2*n,n+1)

    There is a one-one mapping between the Type 2 paths and the invalid Type 1 paths
    Invalid means that path violates the condition at least once

    So, Number of valid paths   =   C(2*n,n) - C(2*n,n+1)
                                =   C_n
***/

