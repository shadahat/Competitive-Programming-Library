/***
    **  Stirling Number of The First Kind :
    Number of ways you can decompose a set of size n
    into k disjoint cycles.

    S(n,k)  =   Number of ways you can decompose a set of size n
                into k disjoint cycles.
            =   (n-1) * S(n-1,k) + S(n-1,k-1)

    S(n,1)  =   (n-1)!
    S(n,2)  =   C(n,2)
    S(n,n)  =   1

    k>= 1       2       3       4       5       6       7
    1   1
    2   1       1
    3   2	    3	    1
    4   6	    11	    6	    1
    5   24	    50	    35	    10	    1
   (n)

    P(x,n) = x(x-1)(x-2) ... (x-(n-1))
    S(n,k) is the absolute value of the coefficient of x^k in P(x,n)

    P(x,1)  =   +x
    P(x,2)  =   -x      +x^2
    P(x,3)  =   +2x     -3x^2       +x^3
    P(x,4)  =   -6x     +11x^2      -6x^3   +x^4

    So, to know s(n,k) we just need to know a coefficient in a polynomial
    This can be done in O(n * logn * logn) using divide and conquer technique

    F(x) = x(x - 1)(x - 2)   ... (x - (n-1))
    Q(x) = x(x - 1)(x - 2)   ... (x - n/2)
    R(x) = (x - ((n/2) + 1)) ... (x - (n-1))

    F(x) = Q(x) * R(x)


    **  Stirling Number of The Second Kind :
        
    S(n,k)  =   Number of ways to partition a set of n objects
                into k non-empty subsets
            =   k * S(n-1,k) + S(n-1,k-1)

    Example :

    Number of ways to color a 1*n grid using k colors such
    That each color is used at least once
    =   k! * S(n,k)


    (k * logn) way :
    S(n,k) = (1 / k!) * sum
    sum = 0
    for(j from 0 to k)
        sum += ((-1)^(k-j)) * C(k,j) * j^n

    Generating A row in (n * logn):
    A(i) = ((-1)^(i))/(i!)
    B(i) = (i^n)/(i!)
    C = A * B
    S(n, k) is the coefficient of x^k of polynomial C.
***/
