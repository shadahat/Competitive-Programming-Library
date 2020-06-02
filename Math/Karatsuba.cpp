/***
    multiply (7x^2 + 8x^1 + 9x^0) with (6x^1 + 5x^0)
    ans = (42x^3 + 83x^2 + 94x^1 + 45x^0)
    A = [7,8,9], B = [6,5], n = 3, m = 2
    multiply(A,B,res)
    res will be (42 83 94 45)
***/
#define MAX 200000*4 /// Must be a power of 2 (Not really actually, 4*MAX suffices)
#define MOD ?
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

long long ptr = 0;
long long temp[128];
long long buffer[MAX * 6];
const long long INF = 8000000000000000000LL;

void karatsuba(int n, long long *a, long long *b, long long *res){ /// n is a power of 2
    int i, j, s;
    if (n < 33){ /// Reduce recursive calls by setting a threshold
        for (i = 0; i < (n + n); i++) temp[i] = 0;
        for (i = 0; i < n; i++){
            if (a[i]){
                for (j = 0; j < n; j++){
                    temp[i + j] += (a[i] * b[j]);
                    if (temp[i + j] > INF) temp[i + j] %= MOD;
                }
            }
        }
        for (i = 0; i < (n + n); i++) res[i] = temp[i] % MOD;
        return;
    }

    s = n >> 1;
    karatsuba(s, a, b, res);
    karatsuba(s, a + s, b + s, res + n);
    long long *x = buffer + ptr, *y = buffer + ptr + s, *z = buffer + ptr + s + s;

    ptr += (s + s + n);
    for (i = 0; i < s; i++){
        x[i] = a[i] + a[i + s], y[i] = b[i] + b[i + s];
        if (x[i] >= MOD) x[i] -= MOD;
        if (y[i] >= MOD) y[i] -= MOD;
    }

    karatsuba(s, x, y, z);
    for (i = 0; i < n; i++) z[i] -= (res[i] + res[i + n] - MOD);
    for (i = 0; i < n; i++) res[i + s] = (res[i + s] + z[i] + MOD) % MOD;
    ptr -= (s + s + n);
}

/// multiplies two polynomial a( degree n-1 ) and b( degree m-1 ) and returns the result modulo MOD in a
/// returns (the degree of the multiplied polynomial + 1)
/// note that a and b are changed in the process
int mul(int n, long long *a, int m, long long *b){
    int i, r, c = (n < m ? n : m), d = (n > m ? n : m);
    long long *res = buffer + ptr;
    r = 1 << (32 - __builtin_clz(d) - (__builtin_popcount(d) == 1));
    for (i = d; i < r; i++) a[i] = b[i] = 0;
    for (i = c; i < d && n < m; i++) a[i] = 0;
    for (i = c; i < d && m < n; i++) b[i] = 0;

    ptr += (r << 1), karatsuba(r, a, b, res), ptr -= (r << 1);
    for (i = 0; i < (r << 1); i++) a[i] = res[i];
    return (n + m - 1);
}


/// For a polynomial of degree D ,
/// coeff[0] will contain the coefficient of x^D
/// coeff[D] will contain the coefficient of x^0
/// coeff[D-i] will contain the coefficient of x^i
