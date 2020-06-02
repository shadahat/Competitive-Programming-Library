/***
    A = I + (B/2) - 1;

    A = Area of the polygon(Should be a simple polygon
                            and the vertexes should be lattice points)
    I = Number of Interior Lattice Points
    B = Number of Boundary Lattice Points

    P   =   N umber of lattice points in the line (x_0,y_0)-->(x_1,y_1)
    Suppose, X   =   x_1 - x_0 , Y = y_1 - y_0
    Then,   P   = gcd(X,Y)+1
    The boundary points can be counted by this way.

    Area can be calculated by any standard way.

    Then the only unknown will be I.
***/
