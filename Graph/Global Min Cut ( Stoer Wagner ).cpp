#include <bits/stdc++.h>
using namespace std;

// given an undirected weighted graph, returns the global min cut
// O(V^3)
// 0 based node indexing
// weights is a 2D vector
// weights[u][v] or weights[v][u] is the weight of the edge between node u and node v
// weights[u][v] = weights[v][u] = 0 if there is node edge between u and v

const int N = 1405;

pair <int, vector <int>> GetMinCut(vector <vector <int>> &weights) {
    int n = weights.size();
    vector <int> used(n), cut, best_cut;
    int best_weight = -1;

    for (int phase = n-1; phase >= 0; phase--) {
        vector <int> w = weights[0], added = used;

        int prev, k = 0;
        for(int i=0;i<phase;i++) {
            prev = k;
            k = -1;

            for(int j=1;j<n;j++)
                if (!added[j] and (k == -1 or w[j] > w[k])) k = j;

            if (i == phase-1) {
                for(int j=0;j<n;j++) weights[prev][j] += weights[k][j];
                for(int j=0;j<n;j++) weights[j][prev] = weights[prev][j];
                used[k] = true;
                cut.push_back(k);
                if (best_weight == -1 or w[k] < best_weight) {
                    best_cut = cut;
                    best_weight = w[k];
                }
            }
            else {
                for(int j=0;j<n;j++) w[j] += weights[k][j];
                added[k] = true;
            }
        }
    }
    // best_weight -> min cut value
    // best_cut -> list of nodes in one side
    return{best_weight, best_cut};
}

int main() {
    int n, w;
    cin >> n;
    vector <vector <int>> mat(n, vector <int>(n));
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cin >> w;
            mat[i][j] = w;
        }
    }
    auto r = GetMinCut(mat);
    cout << r.first << endl;
    return 0;
}
