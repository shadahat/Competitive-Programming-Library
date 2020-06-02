tree[nd].maxsum = max(max(tree[2*nd].maxsum, tree[2*nd+1].maxsum),
                     tree[2*nd].suffixsum + tree[2*nd+1].prefixsum);

tree[nd].prefixsum = max(tree[2*nd].prefixsum,
                        tree[2*nd].sum + tree[2*nd+1].prefixsum);
tree[nd].suffixsum = max(tree[2*nd+1].suffixsum,
                        tree[2*nd+1].sum + tree[2*nd].suffixsum);

tree[nd].sum = tree[2*nd].sum + tree[2*nd+1].sum;
