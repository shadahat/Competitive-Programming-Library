// A vector can be added to the space at any moment
// Following queries can be made on the current basis at any moment

const int B = ?;

struct space {

    int base[B];
    int sz;

    void init() {
        CLR(base); sz = 0;
    }
    // if the vector val is not currently in the vector space,
    // then adds val as a basis vector
    void add(int val) {
        for(int i = B-1; i >= 0; i--) {
            if( val & (1<<i) ) {
                if(!base[i]) {
                    base[i] = val; ++sz; return;
                }
                else val ^= base[i];
            }
        }
    }

    int getSize() { return sz; }

    // returns maximum possible ret such that, ret = (val ^ x)
    // and x is also in the vector space of the current basis
    int getMax(int val) {
        int ret = val;
        for(int i = B - 1; i >= 0; i--) {
            if(ret & (1<<i)) continue;
            ret ^= base[i];
        }
        return ret;
    }

    // returns minimum possible ret such that, ret = (val ^ x)
    // and x is also in the vector space of the current basis
    int getMin(int val) {
        int ret = val;
        for(int i = B - 1; i >= 0; i--) {
            if( !(ret & (1<<i)) ) continue;
            ret ^= base[i];
        }
        return ret;
    }
    // returns true if val is in the vector space
    bool possible(int val) {
        for(int i = B - 1; i >= 0; i--) {
            if(val & (1<<i)) val ^= base[i];
        }
        return (val == 0);
    }

    // returns the k'th element of the current vector space
    // if we sort all the elements according to their values
    int query(int k) {
        int ret = 0;
        int tot = 1 << getSize();
        for(int i = B - 1; i >= 0; i--) {
            if(!base[i]) continue;
            int low = tot >> 1;
            if ((low < k && (ret & 1 << i) == 0) || (low >= k && (ret & 1 << i) > 0))
                ret ^= base[i];
            if (low < k) k -= low;
            tot /= 2;
        }
        return ret;
    }
};
