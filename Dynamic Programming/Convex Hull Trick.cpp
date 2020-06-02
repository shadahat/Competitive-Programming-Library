#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
//using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair <int,int> PII;
typedef pair <long long,long long> PLL;

#define si(a)           scanf("%d",&a)
#define sii(a,b)        scanf("%d %d",&a,&b)
#define siii(a,b,c)     scanf("%d %d %d",&a,&b,&c)

#define sl(a)           scanf("%lld",&a)
#define sll(a,b)        scanf("%lld %lld",&a,&b)
#define slll(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)

#define un(x)           x.erase(unique(all(x)), x.end())
#define xx              first
#define yy              second
#define pb              push_back
#define mp              make_pair
#define all(v)          v.begin(),v.end()
#define D(x)            cerr << #x " = " << x << '\n'
#define DBG             cerr << "Hi!" << '\n'

#define CLR(a)          memset(a,0,sizeof(a))
#define SET(a)          memset(a,-1,sizeof(a))

#define PI              acos(-1.0)

int setBit(int n,int pos) { return n = n | (1 << pos); }
int resetBit(int n,int pos) { return n = n & ~(1 << pos); }
bool checkBit(ll n,ll pos) { return (bool)(n & (1LL << pos)); }

//int fx[] = {+0, +0, +1, -1, -1, +1, -1, +1};
//int fy[] = {-1, +1, +0, +0, +1, +1, -1, -1}; //Four & Eight Direction

/******************************************************************************************/

const int MAX = 200010;
const int INF = 2000000000000000;
//const int MOD = 1000000007;


/**
    *   Lines should be added non-increasing order of m for minimizing
        Non-decreasing order of m for maximizing
    *   Intersection point of two lines (m1,c1) , (m2,c2) is
        x = (c2-c1)/(m1-m2)
**/

ll M[MAX] , C[MAX];

struct CHT {
    int len , cur;
    void init() {
        len = 0 ,cur = 0;
    }

    /// returns true if line[len-1] is unnecessary when we add line(nm,nc)
    inline bool isBad(ll nm,ll nc) {
        return ( (C[len-1]-C[len-2])/(double)(M[len-2]-M[len-1]) >= (nc-C[len-2])/(double)(M[len-2]-nm) );
        //return ( (C[len-1]-C[len-2])*(M[len-2]-nm) >= (M[len-2]-M[len-1])*(nc-C[len-2]) );
    }

    inline void addLine(ll nm,ll nc) {
        if(len == 0) M[len] = nm , C[len] = nc , ++len;
        else if( M[len-1] == nm ) {
            if(C[len-1] <= nc) return; /// <= to minimize, >= to maximize
            else C[len-1] = nc;
        }
        else {
            while(len >= 2 && isBad(nm,nc)) --len;
            M[len] = nm , C[len] = nc , ++len;
        }
    }

    inline ll getY(int id , ll x) {
        return ( M[id]*x + C[id] );
    }

    inline ll sortedQuery( ll x ) {
        if(cur >= len ) cur = len-1;
        while( cur < len-1 && getY(cur+1,x) >= getY(cur,x) ) cur++; /// <= to minimize, >= to maximize
        return getY(cur,x);
    }

    inline ll TS( ll x ) {
        int low = 0, high = len-1 , mid ;
        while( high - low > 1 ) {
            mid = low + high >> 1;
            if(getY(mid,x) < getY(mid+1,x)) low = mid + 1; /// > to minimize , < to maximize
            else high = mid;
        }
        return max(getY(low,x),getY(high,x)); /// adjust min/max
    }
};

int main() {
    CHT cht;
    cht.init();
    /// add line or make a query
    return 0;
}
