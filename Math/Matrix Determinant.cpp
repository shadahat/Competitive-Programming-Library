/***
    * mat is 0 based
    * n x n matrix
    * If the entries are integer, the final result will also be integer
      But the returned value is of double type.
      To print it as an integer, do the following.
      cout << (int)round(determinant(n)) << endl;

    * In every test case, clear mat first and then do the changes
    * Complexity --> O(min(n,m) * nm)

    * Determinant -> Product of the diagonal entries of the matrix after
                     applying gaussian elimination * ((-1) ^ row swaps)
    * If determinant modulo P is needed, use the code in gaussian elimination in GF(P)
***/

const int SZ = 105;
const double EPS = 1e-9;
double mat[SZ][SZ];

double determinant(int n) {
    int sign = 1;
    for(int r = 0, c = 0; c < n and r < n; c++) {
        int mx = r;
        for(int i = r; i < n; i++) if(abs(mat[i][c]) > abs(mat[mx][c])) mx = i;
        if(abs(mat[mx][c]) < EPS) continue;
        if(r != mx) {
            for(int i=c; i<n; i++) swap(mat[r][i],mat[mx][i]);
            sign *= -1;
        }
        for(int i = 0; i < n; i++)
            if(i != r){
                double mul = mat[i][c] / mat[r][c];
                for(int j = c; j < n; j++) mat[i][j] -= mul * mat[r][j];
            }
        r++;
    }
    double ret = 1;
    for(int i = 0; i < n; i++) ret *= mat[i][i];
    return sign * ret;
}
