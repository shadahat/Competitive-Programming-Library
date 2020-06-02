/***
    ConvexHull : Graham's Scan O( n * lg(n) )

    0 based P and C

    P[]: holds all the Points, C[]: holds Points on the hull(in anti clockwise order)

    np: number of Points in P[], nc: number of Points in C[]

    If there are duplicate Points in P, call makeUnique() before
    calling convexHull(), call convexHull() if you have np >= 3

    to remove co-linear Points on hull, call compress() after convexHull()

    Call getBakiPoints() to get all the points that lie in the perimeter of
    the convex hull


    In case you get TLE, you might try changing the data type of point from int to double
***/


struct pt {
    double x, y;
    pt() {}
    pt(double x, double y) : x(x) , y(y) {}

    pt operator - (const pt &p) const { return pt( x-p.x , y-p.y ); }

    bool operator == (const pt &p) const { return ( fabs( x - p.x ) < EPS && fabs( y - p.y ) < EPS ); }
    bool operator != (const pt &p) const { return !(pt(x,y) == p); }
};

pt P[MAX], C[MAX], P0;

bool nisi[MAX];

inline double dot(pt u, pt v) { return u.x*v.x + u.y*v.y; }
inline double cross(pt u, pt v) {return u.x*v.y - u.y*v.x;}
inline double triArea2(pt a,pt b,pt c) { return cross(b-a,c-a); }

inline bool comp(const pt &a, const pt &b) {
    double d = triArea2(P0, a, b);
    if(d < 0) return false;
    if(d == 0 && dot(P0-a,P0-a) > dot(P0-b,P0-b)) return false;
    return true;
}

void convexHull(int &np, int &nc) {
    int i, j, pos = 0;
    for(i = 1; i < np; i++)
        if(P[i].y<P[pos].y || ( fabs(P[i].y - P[pos].y) < EPS && P[i].x<P[pos].x ) )
            pos = i;
    swap(P[0], P[pos]);
    P0 = P[0];
    sort(P+1, P+np, comp);
    for(i = 0; i < 3; i++) C[i] = P[i];
    for(i = j = 3; i < np; i++) {
        while(triArea2(C[j-2], C[j-1], P[i]) < 0) j--;
        C[j++] = P[i];
    }
    nc = j;
}

inline bool normal(const pt &a, const pt &b) {
    return ( fabs( a.x - b.x ) < EPS ? a.y < b.y : a.x < b.x);
}

inline void makeUnique(int &np) {
    sort(P , P+np , normal);
    np = unique(P , P+np) - P;
}

void compress(int &nc) {
    int i, j;
    double d;
    C[nc] = C[0];
    for(i=j=1; i < nc; i++) {
        d = triArea2(C[j-1], C[i], C[i+1]);
        if( d != 0 || ( d == 0 && C[j-1] == C[i+1]) ) C[j++] = C[i];
    }
    nc = j;
}

void getBakiPoints(int &np, int &nc){
    int j = 0;
    for(int i=0;i<nc;i++){
        while( C[i] != P[j] ) j++;
        nisi[j] = true; /// If the point is already taken
    }

    int last = nc;
    for(int i = np-1; i >= 0 ; i--){
        if(!nisi[i]){
            if( P[i] != C[0] && P[i] != C[last-1] )
                if( triArea2(P[i],C[0],C[nc-1]) == 0 )
                    C[nc++] = P[i];
        }
    }
}
