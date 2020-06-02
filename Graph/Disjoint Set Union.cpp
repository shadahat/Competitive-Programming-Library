/// Time complexity = 5*number of operations
struct DisjointSet{
    int *root,*rnk,n;
    DisjointSet(){}
    DisjointSet(int sz){
        root = new int[sz+1];
        rnk = new int[sz+1];
        n = sz;
    }
    ~DisjointSet(){
        delete[] root;
        delete[] rnk;
    }
    void init(){
        for(int i=1;i<=n;i++){
            root[i] = i;
            rnk[i] = 0;
        }
    }
    int findRoot(int u){
        if(u!=root[u]) root[u] = findRoot(root[u]);
        return root[u];
    }
    void Merge(int u,int v){
        int ru = findRoot(u); int rv = findRoot(v);
        if(rnk[ru]>rnk[rv]) root[rv] = ru;
        else root[ru] = rv;
        if(rnk[ru]==rnk[rv]) rnk[rv]++;
    }
};

int main(){
    DisjointSet *S;
    S = new DisjointSet(n);
    S->init();
    int ru = S->findRoot(u);
    S->Merge(u,v);
    delete S;

    /// or

    DisjointSet S(n);
    S.init();
    int ru = S.findRoot(u);
    S.Merge(u,v);
    return 0;
}

