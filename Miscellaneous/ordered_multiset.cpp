#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


// IMPORTANT!! (for using less_equals<key>)
// using less_equals<key> makes lower_bound works as upper_bound and vice-versa
// for erase use: any.erase(any.find_by_order(any.order_of_key(val)));
// don't use .find() because it will always return .end()

// Ordered Multiset
template <typename key, typename comparator = less_equal<key>>
using ordered_multiset = tree<key, null_type, comparator, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	ordered_multiset<int> os;
	
	os.insert(1);
	os.insert(2);
	os.insert(3);
	os.insert(4);
	os.insert(4);
	os.insert(5);
	os.insert(5);
	os.insert(5);
	os.insert(5);
	
	for(auto& x : os) cout << x << endl;
	// os = {1, 2, 3, 4, 4, 5, 5, 5, 5}
	
	/* 1) os.order_of_key(key) : return the count of an items strictly lesser than the 'key'. */
	
	cout << os.order_of_key(3) << endl; // output : 2
	cout << os.order_of_key(5) << endl; // output : 5
	
	//-----------------------------------------------------------------------------------
	
	/* 2) os.find_by_order(i) : returns an iterator pointing to i'th element (0-indexed) in the set. */ 
	
	cout << *os.find_by_order(0) << endl; // output : 1
	cout << *os.find_by_order(2) << endl; // output : 3
	cout << *os.find_by_order(5) << endl; // output : 5
	
	//-----------------------------------------------------------------------------------
	
	/* 3) os.lower_bound(k) : returns an iterator pointing to item > k */
	cout << (*os.lower_bound(2)) << endl;			// output : 3
	cout << (os.lower_bound(9) == end(os)) << endl; // output : 1
	
	//-----------------------------------------------------------------------------------
	
	/* 4) os.upper_bound(k) : returns an iterator pointing to item >= k */
	cout << (*os.upper_bound(2)) << endl;			// output : 2
	cout << (os.upper_bound(9) == end(os)) << endl; // output : 1
	
	//-----------------------------------------------------------------------------------
	
	/* 5) os.find(value) :  returns an iterator pointing to end of set. */
							
	cout << (os.find(5) == end(os)) << endl;	// output : 1
	cout << (os.find(6) == end(os)) << endl;	// output : 1
	
	//-----------------------------------------------------------------------------------
							
	/* 6) os.erase(os.find_by_order(os.order_of_key(value))) :  erases 'value' from set if it exists. */
	
	os.erase(os.find_by_order(os.order_of_key(3))); 
	for(auto& x : os) cout << x << endl;  
	// os = {1, 2, 4, 4, 5, 5, 5, 5}
	
	os.erase(os.find_by_order(os.order_of_key(5))); 
	for(auto& x : os) cout << x << endl;  
	// os = {1, 2, 4, 4, 5, 5, 5}
	
	os.erase(os.find_by_order(os.order_of_key(9))); 
	for(auto& x : os) cout << x << endl;  
	// os = {1, 2, 4, 4, 5, 5, 5}
	
	//-----------------------------------------------------------------------------------
	
	return 0;
}