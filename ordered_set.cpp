#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T, typename comp = less<T>>
using ordered_set = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;

using osi = ordered_set<int>;           using osll = ordered_set<ll>;

template<typename T> inline ostream& operator<<(ostream &os, const ordered_set<T> &o) {return streamByIterators(os, o.begin(), o.end()); }

/*osi X;
X.insert(1);
X.insert(2);
X.insert(4);
X.insert(8);
X.insert(16);

cout<<*X.find_by_order(1)<<endl; // 2
cout<<*X.find_by_order(2)<<endl; // 4
cout<<*X.find_by_order(4)<<endl; // 16
cout<<(end(X)==X.find_by_order(6))<<endl; // true
    
cout<<X.order_of_key(-5)<<endl;  // 0
cout<<X.order_of_key(1)<<endl;   // 0
cout<<X.order_of_key(3)<<endl;   // 2
cout<<X.order_of_key(4)<<endl;   // 2
cout<<X.order_of_key(400)<<endl; // 5*/
