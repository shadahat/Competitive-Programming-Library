/***
    Given an array consisting of all zeroes
    Update -> Add some value to all the elements of a range
                (no element ever gets negative value)
    Query -> How many non zero element in a range
***/

int tree[MAX];  /// how many non zero elements in this segment
int lazy[MAX];  /// how many times a node is fully updated

void lazyUpdate(int n,int st,int ed){
    if(st!=ed){
        if(lazy[n]) tree[n] = ed-st+1;
        else tree[n] = tree[2*n]+tree[2*n+1];
    }
    else{
        if(lazy[n]) tree[n] = ed-st+1;
        else tree[n] = 0;
    }
}

void build(int n,int st,int ed){
    lazy[n] = tree[n] = 0;
    if(st==ed) return;
    int mid = (st+ed)/2;
    build(2*n,st,mid);
    build(2*n+1,mid+1,ed);
}

void update(int n,int st,int ed,int i,int j,int v){
    if(st>j || ed<i) return;
    if(st>=i && ed<=j){
        lazy[n] += v;
        lazyUpdate(n,st,ed);
        return;
    }
    int mid = (st+ed)/2;
    update(2*n,st,mid,i,j,v);
    update(2*n+1,mid+1,ed,i,j,v);
    lazyUpdate(n,st,ed);
}

int query(int n,int st,int ed,int i,int j){
    if(st>=i && ed<=j) return tree[n];
    int mid = (st+ed)/2;
    if(mid<i) return query(2*n+1,mid+1,ed,i,j);
    else if(mid>=j) return query(2*n,st,mid,i,j);
    else return query(2*n,st,mid,i,j) + query(2*n+1,mid+1,ed,i,j);
}
