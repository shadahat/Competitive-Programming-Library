int dis[MAX];
struct data{
    int u,v,c;
} edge[MAX];

bool bellmanFord(int n,int e,int s){
    int i,j;
    for(i=1;i<=n;i++) dis[i] = INF;
    dis[s] = 0;
    for(j=1; j<=n-1; j++){
        for(i=1; i<=e; i++){
            if(dis[edge[i].u]!=INF && dis[edge[i].u]+edge[i].c<dis[edge[i].v])
                dis[edge[i].v] = dis[edge[i].u]+edge[i].c;
        }
    }
    bool negativeCycle = false;
    for(i=1; i<=e; i++){
        if(dis[edge[i].u]!=INF && dis[edge[i].u]+edge[i].c<dis[edge[i].v]){
            negativeCycle = true;
        }
    }
    return negativeCycle;
}
