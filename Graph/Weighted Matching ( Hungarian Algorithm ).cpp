/***
    * Given a n by m matrix, a call to hungarian() returns
      minimum/maximum cost of matching
    * Complexity O(n^3), takes around 1s when n =  1000
***/

#define MAXIMIZE -1
#define MINIMIZE +1

namespace wm{
    using T = int;
    const T INF = ?;/// 0x3f3f3f3f or 0x3f3f3f3f3f3f3f3fLL
    const int MAX = ?;

    bool vis[MAX];
    int P[MAX], way[MAX], match[MAX];
    T U[MAX], V[MAX], minv[MAX], ara[MAX][MAX];

    /// n = number of row and m = number of columns in 1 based, flag = MAXIMIZE or MINIMIZE
    /// match[i] contains the column to which row i is matched
    T hungarian(int n, int m, T mat[MAX][MAX], int flag){
        CLR(U), CLR(V), CLR(P), CLR(ara), CLR(way);

        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                ara[i][j] = flag * mat[i][j];
            }
        }
        if (n > m) m = n;

        int a, b, d;
        T r, w;
        for (int i = 1; i <= n; i++){
            P[0] = i, b = 0;
            for (int j = 0; j <= m; j++) minv[j] = INF, vis[j] = false;

            do{
                vis[b] = true;
                a = P[b], d = 0, w = INF;

                for (int j = 1; j <= m; j++){
                    if (!vis[j]){
                        r = ara[a][j] - U[a] - V[j];
                        if (r < minv[j]) minv[j] = r, way[j] = b;
                        if (minv[j] < w) w = minv[j], d = j;
                    }
                }

                for (int j = 0; j <= m; j++){
                    if (vis[j]) U[P[j]] += w, V[j] -= w;
                    else minv[j] -= w;
                }
                b = d;
            } while (P[b] != 0);

            do{
                d = way[b];
                P[b] = P[d], b = d;
            } while (b != 0);
        }
        for (int j = 1; j <= m; j++) match[P[j]] = j;

        return (flag == MINIMIZE) ? -V[0] : V[0];
    }
}
