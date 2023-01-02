#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


// Ordered Map
template <typename key, typename value, typename comparator = less<key>>
using ordered_map = tree<key, value, comparator, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	
	ordered_map<int, char> mp;
	
	mp[1] = 'a';
	mp[2] = 'b';
	mp[3] = 'c';
	mp[4] = 'd';
	mp[5] = 'a';
	mp[5] = 'b';
	mp[5] = 'e';
	
	// mp = {{1 : 'a'}, {2 : 'b'}, {3 : 'c'}, {4 : 'd'}, {5 : 'e'}}
	
	/* 1) mp.order_of_key(key) : return the count of an keys strictly lesser than the 'key'. */
	
	cout << mp.order_of_key(3) << endl; // output : 2
	cout << mp.order_of_key(5) << endl; // output : 4
	
	//-----------------------------------------------------------------------------------
	
	/* 2) mp.find_by_order(i) : returns an iterator pointing to i'th element (0-indexed) in the map. */ 
	
	cout << (*mp.find_by_order(0)).first << endl;	// output : 1
	cout << (*mp.find_by_order(2)).first << endl;	// output : 3
	cout << (*mp.find_by_order(0)).second << endl;	// output : a
	cout << (*mp.find_by_order(2)).second << endl;	// output : c
	
	//-----------------------------------------------------------------------------------
	
	/* 3) mp.lower_bound(k) : returns an iterator pointing to key >= k */
	cout << (*mp.lower_bound(2)).second << endl;	// output : b
	cout << (mp.lower_bound(9) == end(mp)) << endl; // output : 1
	
	//-----------------------------------------------------------------------------------
	
	/* 4) mp.upper_bound(k) : returns an iterator pointing to key > k */
	cout << (*mp.upper_bound(2)).second << endl;	// output : c
	cout << (mp.upper_bound(9) == end(mp)) << endl; // output : 1
	
	//-----------------------------------------------------------------------------------
	
	/* 5) mp.find(key) : returns an iterator pointing to the 'key' in the set if it exists.
						 else returns an iterator pointing to end of map. */
							
	cout << (*mp.find(2)).first << endl;		// output : 2
	cout << (*mp.find(5)).second << endl;		// output : e
	cout << (mp.find(6) == end(mp)) << endl;	// output : 1
	
	//-----------------------------------------------------------------------------------
							
	/* 6) mp.erase(key) : erases key and its value from map if it exists. */
	
	mp.erase(3); 
	for(auto& x : mp) cout << x.first << " : " << x.second << endl;  
	// mp = {{1 : 'a'}, {2 :'b'}, {4 : 'd'}, {5 : 'e'}}
	
	mp.erase(9); 
	for(auto& x : mp) cout << x.first << " : " << x.second << endl;  
	// mp = {{1 : 'a'}, {2 :'b'}, {4 : 'd'}, {5 : 'e'}}
	
	//-----------------------------------------------------------------------------------
	
	return 0;
}