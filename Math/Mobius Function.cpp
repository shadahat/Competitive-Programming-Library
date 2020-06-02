/***
    mu[1] = 1,
    mu[n] = 0 if n has a squared prime factor,
    mu[n] = 1 if n is square-free with even number of prime factors
    mu[n] = -1 if n is square-free with odd number of prime factors

    *** sum of mu[d] where d | n is 0 ( For n=1, sum is 1 )***
***/

int mu[MAX] = {0};

void Mobius(int N){
    int i, j;
    mu[1] = 1;
    for (i = 1; i <= N; i++){
        if (mu[i]){
            for (j = i + i; j <= N; j += i){
                mu[j] -= mu[i];
            }
        }
    }
}
