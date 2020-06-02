/*** Vector ***/

    vector <int> V;
    V.assign(n,0); /// resizes to n and makes every element 0

    vector < vector <int> > V;
    //int n = number of rows, m = number of columns;
    M.resize(n, vector<int>(m)); // not tested

    // idx contains the index of the leftmost element in the vector which is greater than val
    int idx = upper_bound( V.begin() , V.end() , val ) - V.begin();

    // idx contains the index of the leftmost element in the vector which is not less than val
    int idx = lower_bound( V.begin() , V.end() , val ) - V.begin();

    // idx = V.size() if no such element in both cases

    /***
        V.begin() and V.end() are iterators
        To get the value in a range [L,R) :
        V.begin() should be replaced by iterator to L
        V.end() should be replaced by iterator to R

        Iterator to the elemnet at index i = ( v.begin() + i )
    ***/

    // returns true if val is in the vector, false otherwise
    binary_search ( V.begin() , V.end() , val )

    // merging two sorted vectors V1 and V2 to vector V
    V.resize( V1.size() + V2.size() );
    merge(V1.begin(),V1.end(),V2.begin(),V2.end(),V.begin());


    vector <vector <int>> V(n, vector <int>(n)); // a n*n vector
    //or
    vector <vector <int>> V(n);
    for(int i=0;i<n;i++) V[i] = vector <int> (n);





/*** Priority Queue ***/
    // to keep the elements in ascending order
    priority_queue < int , vector < int > , greater <int> > Q;



/*** Set ***/
    set <int> S;
    S.find(x) returns the iterator to the element x ( returns S.end() if x is not in S)
    S.lower_bound(x) returns the iterator to the first element >= x
    S.upper_bound(x) returns the iterator to the first element > x
    In both cases if there is no such element, the functions returns
    the iterator to the end of the set



/*** Multiset ***/

    multiset <int> S;
    S.erase(x) deletes all the occurrences of x from the set
    S.erase(it) deletes the element pointed by it
    S.erase(it1,it2) deletes the elements of range [it1,it2)
    S.find(x) returns a iterator to one of the occurrences of x ( returns X.end() if not present)
    S.count(x) returns the number of occurrences of x in S
    upper_bound and lower_bound is same as normal set


/*** Bitset ***/
    // A bitset of size S
    bitset < S > B;
    // A bitset of size S initialized with bits of 10("1010")
    bitset < S > B(10); //...00001010
    // A bitset of size S initialized with bits of 10("1010")
    bitset < S > B(string("1010")) //...00001010

    bitset < S > B[MAX] // array of bitsets each having size S
    // to access the j'th element of the i't bitset B[i][j] is to be used

    B.set(); // makes all the bits 1 (if no parameter given)
    B.reset(); // makes all the bits 0 (if no parameter given)
    B.flip(i); // flips all the bits (if no parameter given)
    B.any(); // returns true if some bits are set
    B.count(); // how many ones

    and, or, xor , right shift, left shift operations are also allowed in bitsets

    bitset < S > B1,B2,B;
    Example
    B = B1 ^ B2;

    // prints all the bits that are 1
    // _Find_first(), _Find_next(i) works in O(n/32)
    for(int i=B._Find_first();i<B.size();i=B._Find_next(i)) cout<<i<<endl;
