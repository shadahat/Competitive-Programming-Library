#define N       200000 /// total number of characters given as input
#define S       26

int root,now;
int nxt[N][S], cnt[N];

/// will be called from main
void init(){
    root = now = 1;
    CLR(nxt),CLR(cnt);
}

inline int scale(char ch) { return (ch - 'a'); }

inline void Insert(char s[],int sz){
    int cur = root, to;
    for(int i=0 ; i< sz ; i++){
        to = scale(s[i]) ;
        if( !nxt[cur][to] ) nxt[cur][to] = ++now;
        cur = nxt[cur][to];
    }
    cnt[cur]++;
}

inline bool Find(char s[],int sz){
    int cur = root, to;
    for(int i=0 ; i<sz ; i++){
        to = scale(s[i]) ;
        if( !nxt[cur][to] ) return false;
        cur = nxt[cur][to];
    }
    return (cnt[cur]!=0);
}

/// It's better to call the Delete() after checking if the
/// string we wanna delete actually exists in the trie
inline void Delete(char s[],int sz){
    int cur = root, to;
    for(int i=0 ; i<sz ; i++){
        to = scale(s[i]) ;
        cur = nxt[cur][to];
    }
    cnt[cur]--;
}
