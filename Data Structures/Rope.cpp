/***
    Problem : Given a string of length n, you will be given q queries
              Each query will contain two indexes L and R (L>=R)
              You have to move the segment [L,R] to the beginning of the string
              *** All the indexes are zero based ***
***/

#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

rope <char> R; ///use as usual STL container

string initial_string;

int main() {
    int n,q;
    cin >> n >> q;
    cin >> initial_string;
    for(int i=0;i<n;i++) R.push_back(initial_string[i]);

    int l, r;
    for(int i = 0; i < q; ++i) {
        cin >> l >> r;
        rope <char> cur = R.substr(l, r - l + 1);
        R.erase(l, r - l + 1);
        R.insert(R.mutable_begin(), cur);
    }
    for(rope <char>::iterator it = R.mutable_begin(); it != R.mutable_end(); ++it)
        cout << *it;
    cout << "\n";
    return 0;
}

/***
    R.push_back(x) inserts character x at the end of rope R

    R.insert(pos,nr) inserts rope nr into R at position pos
    (the first character of nr will be in position pos)

    R.erase(pos,cnt) deletes segment [pos , pos+cnt-1] from R

    R.substr(pos,cnt) = segment [pos, pos+cnt-1]
***/

