/// returns (a^b) % m
ll bigMod(ll a,ll b,ll m){
    ll ret = 1LL;
    a %= m;
    while (b){
        if (b & 1LL) ret = (ret * a) % m;
        a = (a * a) % m;
        b >>= 1LL;
    }
    return ret;
}

PLL extEuclid(ll a,ll b) {
    if(b==0LL) return make_pair(1LL,0LL);
    PLL ret,got;
    got = extEuclid(b,a%b);
    ret = make_pair(got.yy,got.xx-(a/b)*got.yy);
    return ret;
}


/// returns modular invers of a with respect to m
/// inverse exists if and only if a and m are co-prime
ll modularInverse(ll a, ll m){
    ll x, y, inv;
    PLL sol = extEuclid(a,m);
    inv = (sol.xx + m) % m;
    return inv;
}

/***
    * returns smallest x such that (g^x) % p = h, -1 if none exists
    * p must be a PRIME ( gcd(g,p)=1 should be enough :/ )
    * function returns x, the discrete log of h with respect to g modulo p


    * g^x = h (mod p)
    * g^(mq+r) = h (mod p)
    * g^mq * g^r = h mod(p)
    * g^r = h * ((g^-1)^m)^q (mod p)

    * we will precompute all possible (g^r % p) and store the values in a map (value-->r)
    * for every q from 0 to m, we will find corresponding r in a map

***/
ll discrete_log(ll g, ll h, ll p){
    if (h >= p) return -1LL;
    if ( ( g % p) == 0LL ){
        /// return -1 if strictly positive integer solution is required
        if ( h == 1LL ) return 0;
        else return -1;
    }

    unordered_map <ll, ll> mp;
    ll i, q, r, m = ceil(sqrt(p));
    ll d = 1LL, inv = bigMod(modularInverse(g, p), m, p);

    for (r = 0; r <= m; r++){
        if (mp.find(d)!=mp.end()) mp[d] = r ;
        d *= g;
        if (d >= p) d %= p;
    }

    d = h;
    for (q = 0; q <= m; q++){
        if(mp.find(d)!=mp.end()) {
            r = mp[d];
            return (m * q) + r;
        }
        d *= inv;
        if (d >= p) d %= p;
    }
    return -1LL;
}
