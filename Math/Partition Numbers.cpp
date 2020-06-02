/***
    5   =   5
        =   4 + 1
        =   3 + 2
        =   3 + 1 + 1
        =   2 + 2 + 1
        =   2 + 1 + 1 + 1
        =   1 + 1 + 1 + 1 + 1

    So , P(5) = 7
    Recurrence, O(n*n)
    P(n,m)  =   Number of ways to partition n where the maximum size of a
                part can be m ( a+b and b+a is considered as same patition)


    Another way( O(n*sqrt(n)) ) :

    k = 1,-1,2,-2,3,-3,4,-4,.....
    if(n<0) P(n) = 0
    if(n==0) P(n) = 1
    P(n) = 0
    for(all k)
        g_k = (k*(3k-1))/2;
        mul = -1^(k-1)
        P(n) += mul * P(n-g_k)

    g_k here is the k'th generalized pentagonal number
***/
