/***
    * 1 based
    * Initially the tree array is set to zero
    * Point Update(Adding v to index p)
    * query(id) returns sum of the range [1,id]
    * range_query(i,j) returns sum of range [i,j]

    * tree[idx] = sum of range [a,b]
      b = idx
      a = ( idx - (idx & -idx) ) + 1

***/

int tree[MAX]; /// size >= n

/// n --> size of the array
/// v --> value to be added to index idx
void update(int n,int id,int v){
    while( id<=n ) tree[id] += v , id += id & (-id);
}

/// returns sum of range[1,id]
int query(int id){
    int sum = 0;
    while(id > 0) sum += tree[id], id -= id & (-id);
    return sum;
}

/// returns sum of range[l,r]
int range_query(int l,int r){
    return (l > r) ? 0 : query(r)-query(l-1);
}

#define LOGN 20

/// returns the lowest index id such that sum[1,id]>= v
/// if returned id > n, there is no such index then
/// The code is not tested
int tree_search(int n, int v) {
	int sum = 0, pos = 0;
	for(int i=LOGN; i>=0; i--) {
		if(pos + (1 << i) <= n and sum + tree[pos + (1 << i)] < v) {
			sum += tree[pos + (1 << i)];
			pos += (1 << i);
		}
	}
	return pos + 1;
}

