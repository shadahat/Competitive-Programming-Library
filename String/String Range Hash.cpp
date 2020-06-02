#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 100005; // maximum possible string size

int len;
string str;
const ll base[2] = {982451653, 984516781};
const int mod[2] = {1067737007, 1069815139};

ll pwr[2][N], inv[2][N], fh[2][N], rh[2][N];

ll bigMod(ll a, ll b, ll m){
    ll ret = 1;
    if(a > m) a %= m;
    while(b) {
        if (b & 1LL) ret = ret * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return ret;
}

void init() {
    for(int it=0;it<2;it++) {
        pwr[it][0] = inv[it][0] = 1;
        ll minv = bigMod(base[it], mod[it] - 2, mod[it]);
        for(int i=1;i<N;i++) {
            pwr[it][i] = pwr[it][i - 1] * base[it] % mod[it];
            inv[it][i] = inv[it][i - 1] * minv % mod[it];
        }
    }
}

void build(int _len) {
    len = _len;
    for(int it=0;it<2;it++) {
        for(int i=1;i<=len;i++) {
            fh[it][i] = (fh[it][i - 1] + str[i - 1] * pwr[it][i]) % mod[it];
            rh[it][i] = (rh[it][i - 1] + str[i - 1] * pwr[it][len - i + 1]) % mod[it];
        }
    }
}

// a, b -> 0 based
ll fw_hash(int a, int b) {
    assert(a <= b);
    ll one = (fh[0][b + 1] - fh[0][a]) * inv[0][a + 1] % mod[0];
    ll two = (fh[1][b + 1] - fh[1][a]) * inv[1][a + 1] % mod[1];

    if(one < 0) one += mod[0]; if(two < 0) two += mod[1];
    return (one << 32LL) | two;
}

ll rv_hash(int a, int b) {
    assert(a <= b);
    ll one = (rh[0][b + 1] - rh[0][a]) * inv[0][len - b] % mod[0];
    ll two = (rh[1][b + 1] - rh[1][a]) * inv[1][len - b] % mod[1];

    if(one < 0) one += mod[0]; if(two < 0) two += mod[1];
    return (one << 32LL) | two;
}

int main() {
    init();
    int T; cin >> T;
    for(int t=1;t<=T;t++) {
        int n; cin >> n >> str;
        build(n);
        //call fw_hash() or rv_hash() to get hash and reverse hash
    }
    return 0;
}

