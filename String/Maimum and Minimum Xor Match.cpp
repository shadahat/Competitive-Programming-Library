/// Find an integer x in the trie such than n^x is minimized
int FindMinMatch(int n,int nob){
    int ret = 0;
    int cur = root , to;
    for(int i=nob ; i>=0 ; i--){
        ret <<= 1;
        to = checkBit(n,i);
        if(nxt[cur][to]){
            ret += to;
            cur = nxt[cur][to];
        }
        else{
            ret += (!to);
            cur = nxt[cur][!to];
        }
    }
    return ret;
}

/// Find an integer x in the trie such than n^x is maximized
int FindMaxMatch(int n,int nob){
    int ret = 0;
    int cur = root , to;
    for(int i=nob ; i>=0 ; i--){
        ret <<= 1;
        to = checkBit(n,i);
        if(nxt[cur][!to]){
            ret += (!to);
            cur = nxt[cur][!to];
        }
        else{
            ret += (to);
            cur = nxt[cur][to];
        }
    }
    return ret;
}
