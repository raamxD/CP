#include "bits/stdc++.h"
using namespace std;

#define  inf  1061109567
#define _inf -1061109568


struct state{
    int a,b,c;
    pair<int,double> p;
};

int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); 


    //////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * memset(structure, val, sizeof(structure))
     * Initializing with memset()
     */

    
        int ar[3]; 
        
        memset(ar,  0, sizeof(ar));     //   0
        memset(ar, -1, sizeof(ar));     //  -1
        memset(ar, 0x3f, sizeof(ar));   //  1061109567 > 1e9     inf
        memset(ar, 0xc0, sizeof(ar));   // -1061109568 < -1e9   _inf
        
        cout << ar[2] << "\n";
    

    //////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * lower_bound(key)
     * 
     * a) works only on "sorted" vector or set
     * b) returns an iterator pointing to first element >= key
     * c) we can use *lower_bound() for set/multiset but can't perform 2nd and 3rd
     *   operation as set is rb_tree and you can access to tree structure in o(logn)
     */
        
    
        vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};  int key = 6; 

        // 1. get value of 1st element greater than or equal to 'key' if present else *v.end()
    
        cout << *lower_bound(v.begin(), v.end(), key) << "\n";


        // 2. get count of elements strictly lesser than 'key'
    
        cout << (lower_bound(v.begin(), v.end(), key) - v.begin()) << "\n";
     
        
        // 3. get count of elements which are greater than equal to 'key'
    
        cout << (v.end() - lower_bound(v.begin(), v.end(), key)) << "\n";

    

    //////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * upper_bound(key)
     * 
     * a) Works only on "sorted" vector or set.
     * b) Returns an iterator pointing to first element > key.
     * c) We can use *upper_bound() for set/multiset but can't perform 2nd and 3rd
     *    operation as set is rb_tree and you can access to tree structure in O(logn).
     */
     
    
        vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};  int key = 8;

        // 1. get value of 1st element strictly greater than 'key' if present else *v.end()
    
        cout << *upper_bound(v.begin(), v.end(), key) << "\n";


        // 2. get count of elements lesser than or equal to 'key'
    
        cout << (upper_bound(v.begin(), v.end(), key) - v.begin()) << "\n";
     
        
        // 3. get count of elements which are strictly greater than 'key'
    
        cout << (v.end() - upper_bound(v.begin(), v.end(), key)) << "\n";
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////
   
    
        // Features of C++17 support

        map<string, int> m = {{"first", 1}, {"second", 2}};
        for (auto &[key, value] : m) {
            ++value;
            cout << key << " " << value << endl;
        }

        vector<state> v = {{1, 2, 3, {8, 7.5}}, {4, 5, 6, {9, 6.9}}};
        for (auto &it : v) {
            auto [a, b, c, p] = it;
            cout << "{a : " << a << ", b : " << b << ", c : " << c << "} ";
            cout << "{p : " << p.first << ", " << p.second << "}\n";
        }

    
    
    //////////////////////////////////////////////////////////////////////////////////////////////

    
        // Features of C++11 support

        // Lambda Functions

            // ok: return type is bool
            auto f1 = [](int a, int b) {return a < b;}; 
        
            // error: is return type double or int?
            auto f2 = [](int a, double b) {
                if (a == 0) return b;
                else return a;
            }; 
        
            // ok: return type is double
            auto f3 = [](int a, double b)->double {
                if (a == 0) return b;
                else return a;
            }; 

            // ok: return type is double
            auto f4 = [](double a, double b) {
                if (a < 0) return a;
                else return pow(a, b);}; 
            
            // We can also access function by storing this into variable 
            auto square = [](int i){ 
                return i * i; 
            }; 
            cout << "Square of 5 is : " << square(5) << endl; 

        // Sorting with help of lambda comparators
            
            vector<int> v = {5, 6, 9, 1, 3, 6};
            sort(v.begin(), v.end(), [](int a, int b){return a < b;});
            for(auto i : v) cout << i << " "; cout << "\n";

            vector<state> u = {{1, 2, 3, {8, 7.5}}, {4, 5, 6, {9, 6.9}}};
            sort(u.begin(), u.end(), [](const state &s1, const &state s2){return s1.a > s2.a;});
            for (auto &it : u) {
                auto [a, b, c, p] = it;
                cout << "{a : " << a << ", b : " << b << ", c : " << c << "} ";
                cout << "{p : " << p.first << ", " << p.second << "}\n";
            }
        
        // Capture in lambdas i.e []
            
            auto var = 42;
            [](int value) {
                return 0 < value && value < var; 
                // doesn't compile, WTF is var?
            }

            // case 1.  Capture nothing             [](){}
            // case 2.  Capture by value            [var](){}
            // case 3.  Capture by reference        [&var](){}
            // case 4.  Capture all by value        [=](){}
            // case 5.  Capture all by ref          [&](){}
            // case 6.  Capture all by val but var  [=, &var](){}
            // case 7.  Capture all by ref but var  [&, var](){}
                       
        
    
     //////////////////////////////////////////////////////////////////////////////////////////////
     




}
