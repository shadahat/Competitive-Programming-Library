/***
    insert function inserts a pair(x,y) into the structure

    query(v) returns the maximum value y such that x <= v and
    pair(x,y) is present in the current structure
***/

struct MonotonousSet{
    set < pii > S;
    void insert(pii p){
        S.insert(p);
        auto it = S.find(p);
        if(it != S.begin()){
            auto tmp = it;
            --tmp;
            if(tmp->yy >= it->yy){
                S.erase(it);
                return;
            }
        }
        ++it;
        while(it!=S.end() && it->yy<=p.yy){
            S.erase(it);
            it = S.find(p);
            ++it;
        }
    }
    int query(int v){
        if(S.empty()) return 0;
        auto it = S.upper_bound({v,INF});
        if(it==S.begin()) return 0;
        return (--it)->second;
    }
    void clear() { S.clear(); }
};
