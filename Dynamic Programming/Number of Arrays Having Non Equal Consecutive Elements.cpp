/***
    * Number of arrays of size n having the first element as 1,
      the last element x and all the other elements between
      [1,k] and no two consecutive elements are equal

    * If k changes, preprocess has to be called

    * Preprocess Complexity -> O(n)
    * Query Complexity -> O(1)

    * If no bound on the first and last element,
      then there are k * (k-1)^(n-1) arrays
***/

int dp[MAX];
void preprocess(int n, int k) {
    dp[0] = 0; dp[1] = 1;
    for (int i=2;i<n;i++) {
        dp[i] = ( (k - 2) * 1LL * dp[i - 1] ) % MOD;
        dp[i] += ( (k - 1) * 1LL * dp[i - 2] ) % MOD;
        if(dp[i] >= MOD) dp[i] -= MOD;
    }
}

int howMany(int n,int k,int x) {
    if(x == 1) return ( (k - 1) * 1LL * dp[n - 2] ) % MOD;
    else return dp[n-1];
}
