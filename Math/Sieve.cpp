bool isComp[MAX];  /// ara[i] is true if i is composite
vector <int> primes;

void Sieve(int N) {
    isComp[0] = isComp[1] = 1;
    int  i,j,sq = sqrt(N);
    for(i=4;i<=N;i+=2) isComp[i] = true;
    for(i=3;i<=sq;i+=2){
        if(!isComp[i]){
            for(j=i*i;j<=N;j+=i+i) isComp[j] = 1;
        }
    }
    for(i=2;i<=N;i++) if(!isComp[i]) primes.pb(i);
}
