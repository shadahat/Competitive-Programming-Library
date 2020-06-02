/***
    If (a,n) = 1 :
        ord(a wrt n) = x such that,
        a^x = 1 (mod n) and x is the smallest number

        x will always divide phi(n)

    *** Primitive Root
    If n is a prime and x = (p - 1),
    then a is a primitive root of n.

    There, phi(phi(n)) primitive roots modulo n
    If a is primitive root and

    e1,e2,... are all the numbers less than and coprime to phi(phi(n)),

    then, all the primitive roots are
    a^e1 (mod n)
    a^e2 (mod n)
    a^e3 (mod n)
    ..........


    *** Discrete Log
    If n is a prime and a is a primitive root and 1 <= b <= n-1 :

    b = a ^ x (mod n)

    Then x is the discrete log of b for base (a,n)


***/
