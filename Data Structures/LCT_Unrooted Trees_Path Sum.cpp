#include<bits/stdc++.h>

using namespace std;

using DT = int;

struct Node {
    int sz, label;
    DT val, sum;
    bool flip;
    Node *p, *pp, *l, *r;
    Node() {
        p = pp = l = r = 0;
        flip = false;
        val = sum = 0;
    }
};

void update(Node *x) {
	x->sum = x->val;
    x->sz = 1;
    if(x->l) x->sz += x->l->sz, x->sum += x->l->sum;
    if(x->r) x->sz += x->r->sz, x->sum += x->r->sum;
}

void normalize(Node *x){
	if(x->flip){
		if(x->l){
			x->l->flip ^= 1;
			swap(x->l->l, x->l->r);
		}
		if(x->r){
			x->r->flip ^= 1;
			swap(x->r->l, x->r->r);
		}
		x->flip = 0;
	}
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
        x->r->p = 0;
        x->r = 0;
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

Node *query_root(Node *x) {
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
    access(x), access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *query_lca(Node *x, Node *y) {
    access(x);
    return access(y);
}

int query_depth(Node *x) {
    access(x);
    return x->sz - 1;
}


void set_value(Node *x, DT v) {
    access(x);
    x->val = v;
    update(x);
}

void make_root(Node *x){
	access(x);
	x->flip = true;
	swap(x->l, x->r);
}

class LinkCut {
    Node *x;

public:
    LinkCut(int n) {
        x = new Node[n+1];
        for(int i = 1; i <= n; i++) {
            x[i].label = i;
            update(&x[i]);
        }
    }

    virtual ~LinkCut() { delete[] x; }

    void make_root(int u) { return ::make_root(&x[u]); }

    void link(int u, int v) {
		::make_root(&x[u]);
        ::link(&x[u], &x[v]);
    }

    void set_value(int u, DT val) {
		::set_value(&x[u], val);
	}

	/// There has to be a direct edge between u and v
    void cut(int u, int v) {
		if(query_depth(u) > query_depth(v)) ::cut(&x[u]);
		else ::cut(&x[v]);
    }

    int query_root(int u) {
        return ::query_root(&x[u])->label;
    }

    int query_depth(int u) {
        return ::query_depth(&x[u]);
    }

    int query_lca(int u, int v) {
        return ::query_lca(&x[u], &x[v])->label;
    }

    DT query_pathSum(int u) {
		::access(&x[u]);
		return x[u].sum;
	}
} *tree;

int ara[30010];

int main(){
    int n; cin >> n;
    tree = new LinkCut(n);
    for(int i=1;i<=n;i++) {
        cin >> ara[i];
        tree->set_value(i,ara[i]);
    }

    int q; cin >> q;
    string s;
    int u,v;
    for(int i=1;i<=q;i++) {
        cin >> s;
        if(s[0] == 'b') {
            cin >> u >> v;
            if(tree->query_root(u) == tree->query_root(v)) cout << "no\n";
            else {
                cout << "yes\n";
                tree->link(u,v);
            }
        }
        else if(s[0] == 'p') {
            cin >> u >> v;
            tree->set_value(u,v);
        }
        else {
            cin >> u >> v;
            if(tree->query_root(u) != tree->query_root(v)) cout << "impossible\n";
            else {
                tree->make_root(u);
                cout << tree->query_pathSum(v) << "\n";
            }
        }
    }
	return 0;
}
