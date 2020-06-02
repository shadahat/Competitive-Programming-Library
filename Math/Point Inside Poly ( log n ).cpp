/***
    * The following code determines if point p is inside the polygon or not
    * works for convex polygon only
    * Complexity O( log n )
***/

struct pt {
    double x, y;
    pt() {}
    pt(double x, double y) : x(x) , y(y) {}
    pt(const pt &p) : x(p.x) , y(p.y) {}

    pt operator + (const pt &p) const { return pt( x+p.x , y+p.y ); }
    pt operator - (const pt &p) const { return pt( x-p.x , y-p.y ); }
    pt operator * (double c) const { return pt( x*c , y*c ); }
};

inline double dot(pt u, pt v) { return u.x*v.x + u.y*v.y; }
inline double cross(pt u, pt v) {return u.x*v.y - u.y*v.x;}
inline double triArea2(pt a,pt b,pt c) { return cross(b-a,c-a); }

inline bool inDisk(pt a, pt b, pt p) { return dot(a-p, b-p) <= 0; }
inline bool onSegment(pt a, pt b, pt p) { return triArea2(a,b,p) == 0 && inDisk(a,b,p); }

// points of the polygon has to be in ccw order
// if strict, returns false when a is on the boundary
inline bool insideConvexPoly(pt* C, int nc, pt  p, bool strict) {
    int st = 1, en = nc - 1, mid;
    while(en - st > 1) {
        mid = (st + en)>>1;
        if(triArea2(C[0], C[mid], p) < 0) en = mid;
        else st = mid;
    }
    if(strict) {
        if(st==1) if(onSegment(C[0],C[st],p)) return false;
        if(en==nc-1) if(onSegment(C[0],C[en],p)) return false;
        if(onSegment(C[st],C[en],p)) return false;
    }
    if(triArea2(C[0], C[st], p) < 0) return false;
    if(triArea2(C[st], C[en], p) < 0) return false;
    if(triArea2(C[en], C[0], p) < 0) return false;
    return true;
}

