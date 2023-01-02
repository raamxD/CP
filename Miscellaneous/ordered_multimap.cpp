#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// IMPORTANT!! (for using less_equals<key>)
// using less_equals<key> makes lower_bound works as upper_bound and vice-versa
// for erase use: any.erase(any.find_by_order(any.order_of_key(key)));
// don't use .find() because it will always return .end()

// Ordered Multimap
template <typename key, typename value, typename comparator = less_equal<key>>
using ordered_multimap = tree<key, value, comparator, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	
	ordered_multimap<int, char> mp;
	
	mp[1] = 'a';
	mp[2] = 'b';
	mp[3] = 'c';
	mp[4] = 'd';
	mp[4] = 'e';
	mp[5] = 'f';
	mp[5] = 'g';
	mp[5] = 'h';
	
	for(auto& x : mp) cout << x.first << " : " << x.second << endl;  
	// mp = {{1 : 'a'}, {2 : 'b'}, {3 : 'c'}, {4 : 'd'}, {4 : 'e'}, {5 : 'f'}, {5 : 'g'}, {5 : 'h'}}
	
	/* 1) mp.order_of_key(key) : return the count of an keys strictly lesser than the 'key'. */
	
	cout << mp.order_of_key(3) << endl; // output : 2
	cout << mp.order_of_key(5) << endl; // output : 5
	
	//-----------------------------------------------------------------------------------
	
	/* 2) mp.find_by_order(i) : returns an iterator pointing to i'th element (0-indexed) in the map. */ 
	
	cout << (*mp.find_by_order(0)).first << endl;	// output : 1
	cout << (*mp.find_by_order(2)).first << endl;	// output : 3
	cout << (*mp.find_by_order(5)).first << endl;	// output : 5
	cout << (*mp.find_by_order(0)).second << endl;	// output : a
	cout << (*mp.find_by_order(2)).second << endl;	// output : c
	cout << (*mp.find_by_order(5)).second << endl;	// output : f
	
	//-----------------------------------------------------------------------------------
	
	/* 3) mp.lower_bound(k) : returns an iterator pointing to key > k */
	cout << (*mp.lower_bound(2)).second << endl;	// output : c
	cout << (mp.lower_bound(9) == end(mp)) << endl; // output : 1
	
	//-----------------------------------------------------------------------------------
	
	/* 4) mp.upper_bound(k) : returns an iterator pointing to key >= k */
	cout << (*mp.upper_bound(2)).second << endl;	// output : b
	cout << (mp.upper_bound(9) == end(mp)) << endl; // output : 1
	
	//-----------------------------------------------------------------------------------
	
	/* 5) mp.find(key) : returns an iterator pointing to end of map. */
							
	cout << (mp.find(2) == end(mp)) << endl;	// output : 1
	cout << (mp.find(6) == end(mp)) << endl;	// output : 1
	
	//-----------------------------------------------------------------------------------
							
	/* 6) mp.erase(mp.find_by_order(mp.order_of_key(key))) :  erases 'key' from map if it exists. */
	
	mp.erase(mp.find_by_order(mp.order_of_key(3))); 
	for(auto& x : mp) cout << x.first << " : " << x.second << endl;  
	// mp = {{1 : 'a'}, {2 : 'b'}, {4 : 'd'}, {4 : 'e'}, {5 : 'f'}, {5 : 'g'}, {5 : 'h'}}
	
	mp.erase(mp.find_by_order(mp.order_of_key(4))); 
	for(auto& x : mp) cout << x.first << " : " << x.second << endl;  
	// mp = {{1 : 'a'}, {2 : 'b'}, {4 : 'e'}, {5 : 'f'}, {5 : 'g'}, {5 : 'h'}}
	
	mp.erase(mp.find_by_order(mp.order_of_key(9))); 
	for(auto& x : mp) cout << x.first << " : " << x.second << endl;  
	// mp = {{1 : 'a'}, {2 : 'b'}, {4 : 'e'}, {5 : 'f'}, {5 : 'g'}, {5 : 'h'}}
	
	//-----------------------------------------------------------------------------------
	
	return 0;
}