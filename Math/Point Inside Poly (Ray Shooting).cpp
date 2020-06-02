/***
    * The following code determines if point a is inside the polygon or not
    * ray is shot from point a to the right of a
    * works for both convex and concave polygon
    * Complexity O(n)
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

// check if segment pq crosses ray from point a
inline bool crossesRay(pt a, pt p, pt q) {
    int mul = (q.y>=a.y) - (p.y>=a.y);
    return (mul * triArea2(a,p,q)) > 0;
}

// if strict, returns false when a is on the boundary
inline bool insidePoly(pt *P, int np, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0; i < np; i++) {
        if (onSegment(P[i], P[(i+1)%np], a)) return !strict;
        numCrossings += crossesRay(a, P[i], P[(i+1)%np]);
    }
    return (numCrossings & 1); // inside if odd number of crossings
}
