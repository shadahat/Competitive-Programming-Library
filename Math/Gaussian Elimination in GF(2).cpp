/***
    Complexity --> O( min(n,m) * nm )
    *** In every test case, clear ( mat[i].reset() ) mat first and then do the changes
**/

const int SZ = 105;
const int MOD = 1e9 + 7;

bitset <SZ> mat[SZ]; /// Augmented Matrix
int where[SZ]; /// where[i] denotes the row index of the pivot element of column i
bitset <SZ> ans;

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

/// n for row, m for column, modulo 2
int GaussJordan(int n,int m) {
    SET(where); /// sets to -1
    for(int row=0,col=0; col<m && row<n; col++) {
        for(int i=row; i<n; i++)
            if( mat[i][col] ){
                swap(mat[i],mat[row]);
                break;
            }

        if( !mat[row][col] ) continue;

        where[col] = row;

        for (int i=row+1; i<n; ++i)
            if (mat[i][col])
                mat[i] ^= mat[row];
        row++;
    }

    /// checking 0 row
    bool zero;
    for(int i=0;i<n;i++){
        zero = true;
        for(int j=0;j<m;j++) {
            if(mat[i][j]) {
                zero = false; break;
            }
        }
        if( zero and mat[i][m] ) return 0; ///no solution
    }

    /// back substitution
    int sltn;
    int cur;
    for(int j=m-1;j>=0;j--){
        if( where[j] == -1 ) {
            ans[j] = 0; /// Infinitely many solutions, determining one
            continue;
        }
        sltn = mat[where[j]][m];
        cur = where[j];
        for(int k = j+1; k<m; k++) {
            sltn ^= ( mat[cur][k] & ans[k] );
        }
        ans[j] =  sltn;
    }

    int cnt = 0;
    for(int i=0; i<m; i++)
        if(where[i]==-1) cnt++;

    if(cnt) return bigMod(2,cnt,MOD);
}
