#include <bits/stdc++.h>
using namespace std;
const int MAX = 100010;
int ara[MAX], b[MAX], f[MAX];
int main() {
    int n;
    cin >> n;
    int answer = 0;
    for (int i=1; i<=n; i++) {
        cin >> ara[i];
        f[i] = lower_bound(b+1, b+answer+1, ara[i]) - b;
        answer = max(answer, f[i]);
        b[f[i]] = ara[i];
    }
    printf("%d\n", answer);

    vector<int> S;

    int required = answer;
    for (int i=n; i>=1; i--)
        if (f[i]==required) {
            S.push_back(ara[i]);
            required--;
        }

    /// then print T with reversed order
    int i = S.size();
    while (i--) printf("%d ", S[i]);
    printf("\n");
}
