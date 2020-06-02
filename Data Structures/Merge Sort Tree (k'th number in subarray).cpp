// Problem : Given a static array (ara), you will be asked q queries
// of the form (x, y, k)
// You have to print the k'th largest number in ara[x:y]
// Answers each query in O(log(n) * log(n))


#include <bits/stdc++.h>
using namespace std;

const int MAX = 100005;

int ara[MAX];
pair <int, int> nums[MAX];
vector <int> tree[4*MAX];

void build(int n, int st, int ed) {
	if(st == ed) {
		tree[n].push_back(nums[st].second);
		return ;
	}
	int mid = (st + ed) >> 1;
	build(n + n, st, mid);
	build(n + n + 1, mid+1, ed);
	merge(tree[n + n].begin(), tree[n + n].end(), tree[n + n + 1].begin(), tree[n + n + 1].end(), back_inserter(tree[n]));
}

int query_kth(int n, int st, int ed, int x, int y, int k) {
	if(st == ed) return tree[n][0];
	auto it = upper_bound(tree[n + n].begin(), tree[n + n].end(), y);
	int total = it - lower_bound(tree[n + n].begin(), tree[n + n].end(), x);
	int mid = (st + ed) >> 1;
	if (total >= k) return query_kth(n + n, st, mid, x, y, k);
	else return query_kth(n + n + 1, mid + 1, ed, x, y, k-total);
}

int main() {
	int n, q; cin >> n >> q;
	for(int i=1;i<=n;i++) {
		cin >> ara[i];
		nums[i] = {ara[i], i};
	}
	sort(nums + 1, nums + n + 1);
	build(1, 1, n);
	int x, y, k, idx;
	while (q--) {
		cin >> x >> y >> k;
		idx = query_kth(1, 1, n, x, y, k);
		cout << ara[idx] << '\n';
	}
	return 0;
}

