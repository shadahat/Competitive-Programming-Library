#include<bits/stdc++.h>
using namespace std;
using DT = int;

/***
    Subtree size can be calculated in the same way as subSum calculation
    set_value(), link(), cut(), ::normalize(), ::sum_update() functions are to be changed
    in Node() constructor, add a variable 'subSize = 1' and a sz_lazy = 0
***/

struct Node {
    int sz, label;
    DT value, lazy, sum, subSum;
    /// sum -> sum of the values of the nodes on the path from this node to root
    Node *p, *pp, *l, *r; /// parent, path-parent, left, right pointers
    Node() {
        p = pp = l = r = 0;
        subSum = sum = lazy = value = 0;
        sz = 1;
    }
};

///PUSH THE LAZY DOWN
void normalize(Node *x) {
	if(x->lazy){
		if(x->l){
			x->l->lazy += x->lazy;
			x->l->subSum += x->lazy;
		}
		if(x->r){
			x->r->lazy += x->lazy;
			x->r->subSum += x->lazy;
		}
		x->lazy = 0;
	}
}

void update(Node *x) {
    assert(!x->lazy);
    x->sz = 1;
    x->sum = x->value;
    if(x->l) x->sz += x->l->sz, x->sum += x->l->sum;
    if(x->r) x->sz += x->r->sz, x->sum += x->r->sum;
}

void rotr(Node *x) {
    Node *y, *z;
    y = x->p, z = y->p;
    normalize(y);
    normalize(x);

    if((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z)) {
        if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void rotl(Node *x) {
    Node *y, *z;
    y = x->p, z = y->p;
    normalize(y);
    normalize(x);

    if((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z)) {
        if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void splay(Node *x) {
    Node *y, *z;
    while(x->p) {
        y = x->p;
        if(y->p == 0) {
            if(x == y->l) rotr(x);
            else rotl(x);
        }
        else {
            z = y->p;
            if(y == z->l) {
                if(x == y->l) rotr(y), rotr(x);
                else rotl(x), rotr(x);
            }
            else {
                if(x == y->r) rotl(y), rotl(x);
                else rotr(x), rotl(x);
            }
        }
    }
    normalize(x);
    update(x);
}

Node *access(Node *x) {
    splay(x);
    if(x->r) {
        x->r->pp = x;
        x->r = x->r->p = 0;
        update(x);
    }

    Node *last = x;
    while(x->pp) {
        Node *y = x->pp;
        last = y;
        splay(y);
        if(y->r) {
            y->r->pp = y;
            y->r->p = 0;
        }
        y->r = x;
        x->p = y;
        x->pp = 0;
        update(y);
        splay(x);
    }
    return last;
}

Node *root(Node *x) {
    access(x);
    while(x->l) x = x->l;
    splay(x);
    return x;
}

void cut(Node *x) {
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y) {
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *lca(Node *x, Node *y) {
    access(x);
    return access(y);
}

int depth(Node *x) {
    access(x);
    return x->sz - 1;
}

DT query_pathSum(Node *x) {
	access(x);
	return x->sum;
}

DT query_subSum(Node *x) {
	access(x);
	return x->subSum;
}

DT query_value(Node *x) {
	access(x);
	return x->value;
}

void set_value(Node *x, DT v){
	access(x);
	x->value = v;
	update(x);
}

void sum_update(Node *x, DT lz) {
	access(x);
	x->lazy += lz;
	x->subSum += lz;
}

Node *special_root(Node *x) {
	access(x);
	Node *r = root(x);
	splay(r);
	r = r->r;
	while(r->l) r = r->l;
	return r;
}

class LinkCut {
    Node *x;
    int *par; /// lavel/index of parent of a node
public:
    int n;
    LinkCut(int _n) {
        n = _n;
        x = new Node[n+1];
        par = new int[n+1];
        for(int i = 1; i <= n; i++) {
            par[i] = -1;
            x[i].label = i; /// label is the index of the node
            update(&x[i]);
        }
    }

    virtual ~LinkCut() { delete[] x; }

    void set_value(int u, DT v) {
        DT val = ::query_value(&x[u]);
        ::set_value(&x[u],v);
        ::sum_update(&x[u],v-val);
    }

    /// makes u a child of v. It must be the case that u is
    /// the root of a tree. Also u and v must be in different trees.
    void link(int u, int v) {
        par[u] = v;

        int s = ::query_subSum(&x[u]);
		::sum_update(&x[v], s);

        ::link(&x[u], &x[v]);
    }

    /// cuts the edge between u and it's parent
    /// fails if u is the root
    void cut(int u) {
		int s = ::query_subSum(&x[u]);
		if( par[u] ) ::sum_update(&x[par[u]], -s);
        ::cut(&x[u]);
    }

    int query_root(int u) { return ::root(&x[u])->label; }

    /// Returns the immediate child of root which is also an ancestor of node u.
    /// Fails if u itself is the root of it's tree
    int special_root(int u) { return ::special_root(&x[u])->label; }

    int query_depth(int u) { return ::depth(&x[u]); }

    /// u and v must be in same tree
    int query_lca(int u, int v) { return ::lca(&x[u], &x[v])->label; }

    DT query_pathSum(int u){ return ::query_pathSum(&x[u]); }

    DT query_pathSum(int u,int v) {
        if( ::root(&x[u]) != ::root(&x[v]) ) assert(false);
        int a = ::lca(&x[u], &x[v])->label;
        return ::query_pathSum(&x[u]) + ::query_pathSum(&x[v]) - ::query_pathSum(&x[a]) + query_value(&x[a]);
    }

    DT query_subSum(int u){ return ::query_subSum(&x[u]); }

} *tree;

int main() {
    int n = 10;
    tree = new LinkCut(n);
    for(int i=1;i<=n;i++) tree->set_value(i,i);
    tree->link(4,2);
	tree->link(5,2);
	tree->link(2,1);
	tree->link(3,1);
	tree->link(6,3);
	tree->link(7,3);
	tree->link(8,7);
	tree->link(9,7);
	tree->link(10,1);
	for(int i=1;i<=10;i++) {
        cout << i << " " << tree->query_subSum(i) << endl;
	}
	return 0;
}
