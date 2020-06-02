#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/***
    Treap as Interval Tree(1 based) With Insert and Remove Operation at any position
    The key(BST Value) is not explicitly stored and determined in the runtime.
    That's why called implicit treap
***/

typedef struct node{
    int prior, sz;
    ll val; ///value stored in the array
    ll sum; ///whatever info you want to maintain in segment tree for each node
    ll lazy; ///whatever lazy update you want to do
    struct node *l, *r, *p;
} node;

typedef node* pnode;
pnode Treap;

inline int getSize(pnode t) { return t ? t->sz : 0; }
inline ll get_sum(pnode t) { return t ? t->sum : 0; }

inline void lazyUpdate(pnode t){
    if(!t or !t->lazy) return;
    t->val += t->lazy;
    t->sum += t->lazy * getSize(t);
    if(t->l) t->l->lazy += t->lazy;
    if(t->r) t->r->lazy += t->lazy;
    t->lazy=0;
}

/// operation of segment tree and size,parent update
inline void operation(pnode t) {
    if(!t) return;
    lazyUpdate(t->l); lazyUpdate(t->r); ///imp:propagate lazy before combining t->l,t->r;
    t->sz = getSize(t->l) + 1 + getSize(t->r);
    t->sum = get_sum(t->l) + t->val + get_sum(t->r); /// updateing sum
    if(t->l) t->l->p = t;
    if(t->r) t->r->p = t;
}

/// The subarray[1:pos] is saved in node l, the rest in r
/// add --> Number of nodes that are not in t's subtree and has index less that t
void split(pnode t, pnode &l, pnode &r, int pos, int add = 0){
    if(!t) return void( l = r = NULL) ;
    lazyUpdate(t);
    int curr_pos = add + getSize(t->l)+1;
    if(curr_pos <= pos) split(t->r, t->r, r, pos, curr_pos), l = t;
    else split(t->l, l, t->l, pos, add), r = t;
    operation(t);
}

void merge(pnode &t, pnode l, pnode r){
    lazyUpdate(l); lazyUpdate(r);
    if(!l or !r) t = l ? l : r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    operation(t);
}

pnode newNode(ll val){
    pnode ret = (pnode)malloc(sizeof(node));
    ret->prior = rand();
    ret->sz = 1;
    ret->val = ret->sum = val;
    ret->lazy = 0;
    ret->p = ret->l = ret->r = NULL;
    return ret;
}


///changes the value of the node at position id to val
inline void point_update(pnode &t, int id, ll val) {
    int sz = getSize(t->l);
    if( sz == (id-1) ) {
        t->val = val;
        pnode cur = t;
        while(cur != NULL) operation(cur), cur = cur->p;
    }
    else if(sz < (id-1) ) point_update(t->r, id-sz-1, val);
    else point_update(t->l, id, val);
}

/***
    * changes the value of the node at position id to val
    * Slower
    * Parent er track na rakhle use kora lagte pare
    void point_update(pnode &t, int id, ll val){
        pnode L, mid, R;
        split(t, L, mid, id-1);
        split(mid, t, R, 1);
        t->val = val;
        merge(mid, L, t);
        merge(t, mid, R);
    }
***/

/// deletes the node at position id
void Remove(pnode &t, int id){
    pnode L, mid, R, X;
    split(t, L, mid, id-1);
    split(mid, X, R, 1);
    delete X;
    merge(t, L, R);
}

/// inserts a node at position id having array value = val
void Insert(pnode &t, int id, ll val){
    pnode L, R, mid;
    pnode it = newNode(val);
    split(t, L, R, id-1);
    merge(mid, L, it);
    merge(t, mid, R);
}

/// add val to all the nodes [i:j]
void range_update(pnode t, int i, int j, ll val){
    pnode L, M, R;
    split(t, L, M, i-1);
    split(M, t, R, j-i+1);
    t->lazy += val;
    merge(M, L, t);
    merge(t, M, R);
}

/// range query [i:j]
ll range_query(pnode t, int i, int j){
    pnode L, M, R;
    split(t, L, M, i-1);
    split(M, t, R, j-i+1);
    ll ans = t->sum;
    merge(M, L, t);
    merge(t, M, R);
    return ans;
}

/// Freeing memory after each test case
void Delete(pnode &t){
    if(!t) return;
    if(t->l) Delete(t->l);
    if(t->r) Delete(t->r);
    delete(t);
    t = NULL;
}

ll ara[11];

int main(){
    ///creating a treap to use it as an interval tree of ara (1 based)
    int n = 10;
    for(int i=1; i<=n; i++) merge(Treap,Treap,newNode(ara[i]));
    Delete(Treap);  /// Deleting when work done
    return 0;
}


/*
/// Maximum contiguous sum merging
void operation(pnode t){
    if(!t)return;
    t->sum = get_sum(t->l) + t->val + get_sum(t->r);
    t->res = max( max(get_res(t->l), get_res(t->r)), max(0, get_rsum(t->l)) + t->val + max(0, get_lsum(t->r)));
    t->lsum = max(max(0,get_lsum(t->r)) + t->val + get_sum(t->l),get_lsum(t->l));
    t->rsum = max(get_sum(t->r) + t->val + max(0,get_rsum(t->l)),get_rsum(t->r));
}
*/
