/***
    F(n, k) = number of ways to color n objects using exactly k colors

    Let G(n, k) be the number of ways to color n objects using no more than k colors.

    Then,
    F(n, k) = G(n, k) - C(k, 1) * G(n, k-1) + C(k, 2) * G(n, k-2) - C(k, 3) * G(n, k-3) .....


    Determining G(n, k) :

    Suppose, we are given a 1 * n grid. Any two adjacent cells can not have same color.
    Then, G(n, k) = k * ((k-1)^(n-1))

    If no such condition on adjacent cells.
    Then, G(n, k) = k ^ n
***/
