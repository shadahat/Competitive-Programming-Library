/// What SOS DP actually finds out
    for(int mask = 0;mask < (1<<N); ++mask)
        for(int i = 0;i < (1<<N); ++i)
            if( (mask & i) == i ) { /// i is a submask of mask
                F[mask] += A[i];
            }
/// O(4^n)


/// Suboptimal approach
/// iterating over all the masks
    for (int mask = 0; mask < (1<<n); mask++){
        F[mask] = A[0];
        /// iterating over all the submasks of the mask
        for(int submask = mask; submask > 0; submask = (submask-1) & mask) {
            F[mask] += A[submask];
        }
    }
/// O(3^n)

/***
    S(mask,i) denotes those submasks of mask which differ
    from mask only in the least significant i+1 bits ( 0, 1, 2, ...., i --> 0 based indexing)
    Example : S(1011010,3) = {1011010,1010010,1011000,1010000}


    if(bit i is on)
        S(mask, i) = S(mask, i - 1) U S(mask ^ (1<<i), i - 1)
    else
        S(mask, i) = S(mask, i - 1)


    Let Sum(mask,i) denote the sum of the all A[x] where x element of S(mask,i)
    So, Sum(mask,N-1) will contain SOS DP result for a particular mask

    Recurrence :
    if(i'th bit is on)
        Sum(mask, i) = Sum(mask, i-1) + Sum(mask ^ (1<<i), i-1)
    else
        Sum(mask, i) = Sum(mask, i-1)
***/

///iterative version
    for(int mask = 0; mask < (1<<N); ++mask){
        dp[mask][-1] = A[mask];	///handle base case separately (leaf states)
        for(int i = 0;i < N; ++i){
            if(mask & (1<<i)) dp[mask][i] = dp[mask][i-1] + dp[mask ^ (1<<i)][i-1];
            else dp[mask][i] = dp[mask][i-1];
        }
        F[mask] = dp[mask][N-1];
    }

///memory optimized version
    for(int i = 0; i<(1<<N); ++i) F[i] = A[i];
    for(int i = 0;i < N; ++i)
        for(int mask = 0; mask < (1<<N); ++mask){
            if(mask & (1<<i))
                F[mask] += F[mask^(1<<i)];
        }
/// O( N * 2^N )

/// How many pairs in ara[] such that (ara[i] & ara[j]) = 0
/// N --> Max number of bits of any array element
const int N = 20;
int inv = (1<<N) - 1;
int F[(1<<N) + 10];
int ara[MAX];

/// ara is 0 based
long long howManyZeroPairs(int n,int ara[]) {
    CLR(F);
    for(int i=0;i<n;i++) F[ara[i]]++;
    for(int i = 0;i < N; ++i)
        for(int mask = 0; mask < (1<<N); ++mask){
            if(mask & (1<<i))
                F[mask] += F[mask^(1<<i)];
        }

    long long ans = 0;
    for(int i=0;i<n;i++) ans += F[ara[i] ^ inv];
    return ans;
}


/// To get
    for(int mask = 0;mask < (1<<N); ++mask)
        for(int i = 0;i < (1<<N); ++i)
            if( (mask & i) == mask ) { /// i is a supermask of mask
                F[mask] += A[i];
            }
/// The code is the following
    for(int i = 0; i<(1<<N); ++i) F[i] = A[i];
    for(int i = 0;i < N; ++i)
        for(int mask = (1<<N)-1; mask >= 0; --mask){
            if (!(mask & (1<<i)))
                F[mask] += F[mask | (1<<i)];
        }


/// Number of subsequences of ara[0:n-1] such that
/// sub[0] & sub[2] & ... & sub[k-1] = 0
const int N = 20;
int inv = (1<<N) - 1;
int F[(1<<N) + 10];
int ara[MAX];
int p2[MAX]; /// p2[i] = 2^i
///0 based array
int howManyZeroSubSequences(int n,int ara[]) {
    CLR(F);
    for(int i=0;i<n;i++) F[ara[i]]++;
    for(int i = 0;i < N; ++i)
        for(int mask = (1<<N)-1; mask >= 0; --mask){
            if (!(mask & (1<<i)))
                F[mask] += F[mask | (1<<i)];
        }
    int ans = 0;
    for(int mask=0;mask<(1<<N);mask++) {
        if(__builtin_popcount(mask) & 1) ans = sub(ans, p2[F[mask]]);
        else ans = add(ans, p2[F[mask]]);
    }
    return ans;
}

/// Number of subsequences of ara[0:n-1] such that
/// sub[0] | sub[2] | ... | sub[k-1] = Q

int F[(1<<20) + 10], ara[MAX];
int p2[MAX]; /// p2[i] = 2^i

/// ara is 0 based
int howManySubsequences(int n, int ara[], int m, int Q) {
    CLR(F);
    for(int i=0;i<n;i++) F[ara[i]]++;
    if(Q == 0) return sub(p2[F[0]], 1);
    for(int i = 0;i < m; ++i)
        for(int mask = 0; mask < (1<<m); ++mask){
            if (mask & (1<<i))
                F[mask] += F[mask ^ (1<<i)];
        }
    int ans = 0;
    for(int mask=0;mask<(1<<m);mask++) {
        if(mask & Q != mask) continue;
        if(__builtin_popcount(mask ^ Q) & 1) ans = sub(ans, p2[F[mask]]);
        else ans = add(ans, p2[F[mask]]);
    }
    return ans;
}

