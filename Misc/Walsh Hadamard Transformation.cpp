const int MAX = (1<<N) + 10; /// maximum value of n
//const int INF = 2000000000;
//const int MOD = 1000000007;

/***
    * A call to fwht::convolution(n, A, B, operator) returns a vector V of size n
    * A and B are arrays of size n
    * n must be a power of 2
    * For i = 0 to n - 1, j = 0 to n - 1
      V[i operator j] += A[i] * B[j]
***/

/// Fast Walsh-Hadamard Transformation in n log n
namespace fwht{
    const int OR = 0;
    const int AND = 1;
    const int XOR = 2;

    long long P1[MAX], P2[MAX]; /// Adjust the MAX accordingly

    void walsh_transform(long long* ar, int n, int flag = XOR){
        if (n == 0) return;
        int i, m = n / 2;
        walsh_transform(ar, m, flag);
        walsh_transform(ar + m, m, flag);

        for (i = 0; i < m; i++){ /// Don't forget modulo if required
            long long x = ar[i], y = ar[i + m];
            if (flag == OR) ar[i] = x, ar[i + m] = x + y;
            if (flag == AND) ar[i] = x + y, ar[i + m] = y;
            if (flag == XOR) ar[i] = x + y, ar[i + m] = x - y;
        }
    }

    void inverse_walsh_transform(long long* ar, int n, int flag = XOR){
        if (n == 0) return;

        int i, m = n / 2;
        inverse_walsh_transform(ar, m, flag);
        inverse_walsh_transform(ar + m, m, flag);

        for (i = 0; i < m; i++){ /// Don't forget modulo if required
            long long x = ar[i], y = ar[i + m];
            if (flag == OR) ar[i] = x, ar[i + m] = y - x;
            if (flag == AND) ar[i] = x - y, ar[i + m] = y;
            if (flag == XOR) ar[i] = (x + y) >> 1, ar[i + m] = (x - y) >> 1; /// Modular inverse if required here
        }
    }

    vector <long long> convolution(int n, long long* A, long long* B, int flag = XOR){
        assert(__builtin_popcount(n) == 1); /// n must be a power of 2
        for (int i = 0; i < n; i++) P1[i] = A[i];
        for (int i = 0; i < n; i++) P2[i] = B[i];

        walsh_transform(P1, n, flag);
        walsh_transform(P2, n, flag);
        for (int i = 0; i < n; i++) P1[i] = P1[i] * P2[i]; /// Don't forget modulo if required
        inverse_walsh_transform(P1, n, flag);
        return vector<long long> (P1, P1 + n);
    }
}
