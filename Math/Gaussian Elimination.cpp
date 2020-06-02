/***
    *** In every test case, clear mat first and then do the changes
***/

const int SZ = 105;
const double EPS = 1e-9;

double mat[SZ][SZ]; /// Augmented Matrix
int where[SZ]; /// where[i] denotes the row index of the pivot element of column i
double ans[SZ];

/// n for row, m for column
int Gauss(int n,int m) {
    SET(where); /// sets to -1
    for(int row=0,col=0;col<m && row<n;col++){
        int max_row = row;
        for(int i=row;i<n;i++)
            if( abs(mat[i][col]) > abs(mat[max_row][col]) ) max_row = i;

        if( abs(mat[max_row][col]) < EPS ) continue;

        for(int i=col;i<=m;i++) swap(mat[row][i],mat[max_row][i]);

        where[col] = row;

        double mul;
        for(int i=row+1;i<n;i++){
            if(abs(mat[i][col])>EPS){
                mul = mat[i][col]/mat[row][col];
                for(int j=col;j<=m;j++) mat[i][j] -= mul*mat[row][j];
            }
        }
        row++;
    }

    /// checking 0 row
    bool zero;
    for(int i=0;i<n;i++){
        zero = true;
        for(int j=0;j<m;j++) {
            if(abs(mat[i][j])>EPS) {
                zero = false; break;
            }
        }
        if( zero && abs(mat[i][m]) > EPS ) return 0; ///no solution
    }

    /// back substitution
    double sltn;
    int cur;
    for(int j=m-1;j>=0;j--){
        if(where[j] == -1)  {
            ans[i] = 0; /// Infinitely many solutions, determining one
            continue;
        }
        sltn = mat[where[j]][m];
        cur = where[j];
        for(int k = j+1; k<m; k++)
            sltn -= mat[cur][k]*ans[k];
        ans[j] = sltn/mat[cur][j];
    }

    for(int j=0;j<m;j++)
        if( where[j] == -1 ) return INF; /// Infinitely many solutions

    return 1; /// unique solution
}
