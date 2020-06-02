/***
    * str will contain the string
    * L = length of str
    * call generateSA(), the S[] will contain the suffix array

    * Think of suffix as a trie of suffixes.
    * lcp (x, y) = minimum { lcp(x, x + 1), lcp(x + 1, x + 2), ... lcp(y – 1, y) }.
***/

const int MAXL = ?;/// 1<< 20
const int MAXLG = ?;/// 20

char str[MAXL];
int L , stp;
int S[MAXL];
int P[MAXLG][MAXL];
/// P[i][j] = position of the suffix starting at character j after sorting
/// on the basis of 2^i characters

struct entry {
    int pr[2]; /// parameters for sorting
    int id; /// starting index of the suffix
} suf[MAXL] , out[MAXL];

int cnt[MAXL] , taken[MAXL] , cum[MAXL];
int special , specialTaken , it;

inline void countingSort(int type) {
    int i;
    CLR(cnt);
    CLR(taken);
    special = specialTaken = 0;
    for(i = 0; i<L ; i++) {
        if(suf[i].pr[type] == -1) special++;
        else cnt[ suf[i].pr[type] ]++;
    }
    cum[0] = special;
    for(i = 1; i <= it ; i++) cum[i] = cum[i-1] + cnt[i-1];
    for(i = 0; i<L ; i++) {
        if(suf[i].pr[type] == -1) out[ specialTaken++ ] = suf[i];
        else out[ cum[ suf[i].pr[type] ] + taken[ suf[i].pr[type] ]++ ] = suf[i];
    }
    for(i = 0; i<L ; i++) suf[i] = out[i];
}

/// n * lg n
void generateSA(int n){
    L = n;
    int now,i;
    it = 0;
    for(i=0; i<L; i++){
        P[0][i] = (int)str[i];
        it = max(it, P[0][i]);
    }
    for(now=1,stp=1 ; now <=L ; stp++,now *= 2){
        for(i=0; i<L; i++){
            suf[i].pr[0] = P[stp-1][i];
            if(i+now<L) suf[i].pr[1] = P[stp-1][i+now];
            else suf[i].pr[1] = -1;
            suf[i].id = i;
        }
        countingSort(1);
        countingSort(0);
        it = -1;
        for(i=0; i<L; i++){
            if(i>0 && suf[i].pr[0]==suf[i-1].pr[0] && suf[i].pr[1]==suf[i-1].pr[1])
                P[stp][suf[i].id] = it;
            else
                P[stp][suf[i].id] = ++it;

            it = max(it, P[stp][ suf[i].id ]);
        }
    }
    for(i=0;i<L;i++) S[P[stp-1][i]] = i;
}

/// n * lg n
inline int getLCP(int x,int y){
    int ret = 0,add,i;
    if(x==y) return L-x;
    for(i = stp-1 ; i >= 0 && x<L && y<L; i--){
        if(P[i][x]==P[i][y]){
            ret += (1<<i), x += (1<<i), y += (1<<i);
        }
    }
    return ret;
}
