// solves how many distinct elements in a range
// Complexity = nb * N + block_sz * Q
// ara[], query[], res[] 0 based

int block_sz;
int ara[MAXN], freq[MAXV], res[MAXQ];
int ans;

struct data{
    int l, r, id, bn;
    data() {}
    data(int _l, int _r, int _id){
        l = _l, r = _r, id = _id;
        bn = l / block_sz;
    }
    bool operator < (const data& other) const{
        if (bn != other.bn) return (bn < other.bn);
        return ((bn & 1) ? (r < other.r) : (r > other.r));
    }

} query[MAXQ];

void Add(int id){
    freq[ara[id]]++;
    if(freq[ara[id]] == 1) ++ans;
}

void Rmv(int id){
    freq[ara[id]]--;
    if(freq[ara[id]] == 0) --ans;
}

void Mo(int q){
    sort(query, query + q);
    int L = 0, R = 0, l, r;
    ans = 0;
    Add(0);
    for(int i=0; i<q; i++) {
        l = query[i].l;
        r = query[i].r;

        while(L > l) Add(--L);
        while(R < r) Add(++R);

        while(L < l) Rmv(L++);
        while(R > r) Rmv(R--);

        res[query[i].id] = ans;
    }
}

// assign block_sz
