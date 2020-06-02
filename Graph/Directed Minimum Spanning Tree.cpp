/***
    Jaan Vai's code
    Finds cost of forming DMST
    Runs under (V^2)*log(V) where V is the number of nodes
    0 based indexing
    MM is the maximum number of nodes
    Put all the outgoing edges from u in E[u]
    Just call Find_DMST(root, number of nodes) and it will return the total cost of forming DMST
    if it returns inf, then initial graph was disconnected
***/
const int MM = ?
const int inf = ?

struct edge {
    int v, w;
    edge() {}
    edge( int vv, int ww ) { v = vv, w = ww; }
    bool operator < ( const edge &b ) const { return w < b.w; }
};

vector <edge> E[MM], inc[MM];
int DirectedMST( int n, int root, vector <edge> inc[MM] ) {
    int pr[MM];
    inc[root].clear();

    /// if any node is not reachable from root, then no mst can be found
    for( int i = 0; i < n; i++ ) {
        sort( inc[i].begin(), inc[i].end() );
        pr[i] = i;
    }
    bool cycle = true;
    while( cycle ) {
        cycle = false;
        int vis[MM] = {0}, W[MM];
        vis[root] = -1;
        for( int i = 0, t = 1; i < n; i++, t++ ) {
            int u = pr[i], v;
            if( vis[u] ) continue;
            for( v = u; !vis[v]; v = pr[inc[v][0].v] ) vis[v] = t;
            if( vis[v] != t ) continue;
            cycle = true;
            int sum = 0, super = v;
            for( ; vis[v] == t; v = pr[inc[v][0].v] ) {
                vis[v]++;
                sum += inc[v][0].w;
            }
            for( int j = 0; j < n; j++ ) W[j] = INT_MAX;
            for( ; vis[v] == t + 1; v = pr[inc[v][0].v] ) {
                vis[v]--;
                for( int j = 1; j < inc[v].size(); j++ ) {
                    int w = inc[v][j].w + sum - inc[v][0].w;
                    W[ inc[v][j].v ] = min( W[ inc[v][j].v ], w );
                }
                pr[v] = super;
            }
            inc[super].clear();
            for( int j = 0; j < n; j++ ) if( pr[j] != pr[ pr[j] ] ) pr[j] = pr[ pr[j] ];
            for( int j = 0; j < n; j++ ) if( W[j] < INT_MAX && pr[j] != super ) inc[super].push_back( edge( j, W[j] ) );
            sort( inc[super].begin(), inc[super].end() );
        }
    }
    int sum = 0;
    for( int i = 0; i < n; i++ ) if( i != root && pr[i] == i ) sum += inc[i][0].w;
    return sum;
}

int Find_DMST(int root, int n) {
    bool visited[MM] = {0};
    queue <int> Q;
    for( int i = 0; i < n; i++ ) inc[i].clear();
    for( int i = 0; i < n; i++ ) for( int j = 0; j < E[i].size(); j++ ) {
        int v = E[i][j].v, w = E[i][j].w;
        inc[v].push_back( edge( i, w ) );
    }
    visited[root] = true;
    Q.push(root);
    while( !Q.empty() ) {
        int u = Q.front(); Q.pop();
        for( int i = 0; i < E[u].size(); i++ ) {
            int v = E[u][i].v;
            if( !visited[v] ) {
                visited[v] = true;
                Q.push(v);
            }
        }
    }
    /// The given graph is disconnected. So forming any MST is not possible.
    for( int i = 0; i < n; i++ ) if( !visited[i] ) return inf;
    return DirectedMST( n, root, inc );
}

