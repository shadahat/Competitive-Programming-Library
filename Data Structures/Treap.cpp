#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/***
    * Treap is cartesian tree
    * Every node has two values(A BST value and a heap value)
    * The tree is built in such a way that if the tree is a BST WRT the BST values
      and also a heap WRT to heap values
    * Heap values are chosen randomly and thus the tree has height logn (approximate)

    * If there are multiple nodes having same key, make them unique somehow
      For example(Convert them to pair from integers)

***/

struct node{
    int prior; /// Heap value generated randomly
    int key; /// BST value
    int sz; /// Subtree Size(including this node)
    ll sum; /// This bst maintains the sum of it's child nodes
    struct node *l, *r, *p;
};

typedef node* pnode;

pnode Treap;

inline int getSize(pnode t) { return t ? t->sz : 0; }
inline ll get_sum(pnode t) { return t ? t->sum : 0; }

inline void update(pnode t){
    if(!t) return;
    if(t->l) t->l->p = t;
    if(t->r) t->r->p = t;
    t->sz = getSize(t->l) + 1 + getSize(t->r);
    t->sum = get_sum(t->l) + t->key + get_sum(t->r);
}

inline pnode newNode(int key){
    pnode ret = (pnode)malloc(sizeof(node));
    ret->sum = ret->key = key;
    ret->sz = 1;
    ret->prior = rand();
    ret->p = ret->l = ret->r = NULL;
    return ret;
}

/// l will contain the nodes having BST value <= key, rest will go to r
void split(pnode t, pnode &l, pnode &r, int key){
    if(!t) l = r = NULL;
    else if(t->key <= key) split(t->r, t->r, r, key), l = t;
    else split(t->l, l, t->l, key), r = t;
    update(t);
}

/// lowest value of r has to be > that largest value of l
void merge(pnode &t, pnode l, pnode r){
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l ;
    else merge(r->l, l, r->l), t = r ;
    update(t);
}

/// inserting a new node into BST
void insert(pnode &t, pnode it){
    if(!t) t = it ;
    else if(it->prior > t->prior) split(t, it->l, it->r, it->key), t = it ;
    else if(t->key <= it->key) insert(t->r, it);
    else insert(t->l, it);
    update(t);
}

/// Removing a node having BST value = key
void remove(pnode &t, int key){
    if(!t)return;
    else if( t->key == key ){
        pnode temp = t;
        merge(t, t->l, t->r);
        free(temp);
    }
    else if(t->key<key) remove(t->r,key);
    else remove(t->l,key);
    update(t);
}

/// Deleting the treap, freeing memory
void Delete(pnode &t){
    if(!t) return;
    if(t->l) Delete(t->l);
    if(t->r) Delete(t->r);
    delete(t);
    t = NULL;
}

int main() {
    return 0;
}
