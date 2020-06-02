/// l, r are 0 based

struct simplehash{
    int len;
    ll base, mod;
    vector <int> P, H, R;

    simplehash(){}
    simplehash(const string &str, ll b, ll m){
        base = b, mod = m, len = str.size();
        P.resize(len + 3, 1), H.resize(len + 3, 0), R.resize(len + 3, 0);

        for (int i = 1; i <= len; i++) P[i] = (P[i - 1] * base) % mod;
        for (int i = 1; i <= len; i++) H[i] = (H[i - 1] * base + str[i - 1] + 1007) % mod;
        for (int i = len; i >= 1; i--) R[i] = (R[i + 1] * base + str[i - 1] + 1007) % mod;
    }

    inline int range_hash(int l, int r) {
        int hashval = H[r + 1] - ((ll)P[r - l + 1] * H[l] % mod);
        return (hashval < 0 ? hashval + mod : hashval);
    }

    inline int reverse_hash(int l, int r) {
        int hashval = R[l + 1] - ((ll)P[r - l + 1] * R[r + 2] % mod);
        return (hashval < 0 ? hashval + mod : hashval);
    }
};

struct stringhash{
    simplehash sh1, sh2;
    stringhash(){}
    // character array can be sent as parameter too
    stringhash(const string &str){
        sh1 = simplehash(str, 982451653, 1067737007);
        sh2 = simplehash(str, 984516781, 1069815139);
    }

    inline ll range_hash(int l, int r){
        return ((ll)sh1.range_hash(l, r) << 32) ^ sh2.range_hash(l, r);
    }

    inline ll reverse_hash(int l, int r){
        return ((ll)sh1.reverse_hash(l, r) << 32) ^ sh2.reverse_hash(l, r);
    }
};


