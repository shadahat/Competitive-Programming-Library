/*** Policy Based Data Structures ***/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
/// we can replace int with other data types
/// If the data type is user defined, we need to define less operator for that type
typedef tree<
    int ,
    null_type ,
    less < int > , // "less_equal<int>," for multiset
    rb_tree_tag,
    tree_order_statistics_node_update > ordered_set;
/// ordered_set has become a data type, OS is an ordered_set
ordered_set OS;
/***
    * this ordered_set is a set basically
    * ordered_set declared as above can supports all the set operations
      like insert() , erase() , find() , lower_bound() , upper_bound()

    * Ordered set supports two extra functions
        OS.find_by_order(x)
                returns the iterator to the k'th largest element starting count from 0
        OS.order_of_key(x)
                returns number of items in the set strictly smaller than x
*/

int main(){
    OS.insert(1);
    OS.insert(2);
    OS.insert(4);
    OS.insert(8);
    OS.insert(16);
    cout << ( *OS.find_by_order(0) ) << endl; /// 1
    cout << ( *OS.find_by_order(2) ) << endl; /// 4
    cout << ( *OS.find_by_order(4) ) << endl; /// 16
    cout << ( end(OS) == OS.find_by_order(5) ) <<endl; /// true
    cout << OS.order_of_key(-5) << endl;  /// 0
    cout << OS.order_of_key(3) << endl;   /// 2
    cout << OS.order_of_key(400) << endl; /// 5
    return 0;
}
