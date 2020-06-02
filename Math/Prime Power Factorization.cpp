/***
    A call to generatePPF(int N) will generate the prime power
    factorization of numbers upto N
    TLE khele vector ke array diye replace korte hobe
    Overall complexity is almost n(log n)
***/

vector <pii> factor[MAX];
/// factor[x] contains (p,i) if prime p divides x i times
bool isComp[MAX]; /// true if a number is composite
int lp[MAX]; /// least prime factor

void Sieve(int N){
    int sq = sqrt(N);
    for(int i = 1; i <= N; i++) lp[i] = i;
    for(int i = 4; i <= N; i += 2) isComp[i] = true, lp[i] = 2;
    for(int i = 3; i <= sq; i += 2){
        if(isComp[i]) continue;
        for(int j = i * i; j <= N; j += i + i) isComp[j] = 1 , lp[j] = min(lp[j], i);
    }
}

void generatePPF(int N) {
    Sieve(N);
    int now;
    vector <int> temp;
    for(int num = 2; num <= N; num++) {
        now = num;
        temp.clear();
        while(lp[now]!=1){
            temp.pb(lp[now]);
            now = now/lp[now];
        }
        int cnt = 1;
        for(int i = 1; i < temp.size(); i++){
            if(temp[i] == temp[i-1]) cnt++;
            else{
                factor[num].push_back({temp[i-1], cnt});
                cnt = 1;
            }
        }
        factor[num].push_back({temp[temp.size()-1], cnt});
    }
}

/***
    Another Way
    Takes more time than the previous but soto code
***/

vector <pii> factor[MAX];
/// factor[x] contains (p,i) if prime p divides x i times
bool isComp[MAX]; /// true if a number is composite

void generatePPF(int N) {
    int cnt, tmp, x;
    for(int i = 2; i <= N; i++) {
        if(!isComp[i]) {
            for(int j = i; j <= N; j += i) {
                if(i != j) isComp[j] = true;
                tmp = j, cnt = 0;
                while(true) {
                    x = tmp/i;
                    if(x * i != tmp) break;
                    tmp = x;
                    cnt++;
                }
                factor[j].pb({i, cnt});
            }
        }
    }
}

