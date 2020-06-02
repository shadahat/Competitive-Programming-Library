/***
    * In every test case, clear mat first and then do the changes
    * Complexity --> O( min(n,m) * nm )
    * Augmented Matrix -->    [ ORIGINAL_MAT | IDENTITY_MAT ]
    * After elimination -->   [ IDENTITY_MAT | INVERSE_MAT  ]
***/

const int SZ = 105;
const double EPS = 1e-9;
double mat[SZ][SZ+SZ];

void Inverse(int n) {
    for(int mx,r=0,c=0; c<n && r<n; c++) {
        mx = r;
        for(int i=r; i<n; i++) if( abs(mat[i][c]) > abs(mat[mx][c]) ) mx = i;

        if( abs(mat[mx][c]) < EPS ) continue;

        for(int j=c; j<n+n; j++) swap(mat[r][j],mat[mx][j]);

        double mul;
        for(int i=0; i<n; i++)
            if( i!=r ){
                mul = mat[i][c]/mat[r][c];
                for(int j=c; j<n+n; j++) mat[i][j] -= mul*mat[r][j];
            }
        r++;
    }
    for(int i=0;i<n;i++) {
        for(int j=n;j<n+n;j++) {
            mat[i][j] /= mat[i][i];
        }
    }
}

int main() {
    int n;
    si(n);
    for(int i=0;i<n;i++) {
        mat[i][n+i] = 1;
        for(int j=0;j<n;j++) scanf("%lf",&mat[i][j]);
    }
    Inverse(n);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(j!=0) printf(" ");
            printf("%0.9f",mat[i][n+j]);
        }
        puts("");
    }
    CLR(mat);
    return 0;
}
