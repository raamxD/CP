#include "bits/stdc++.h"
using namespace std;

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
        
        //for 32 bit value
        
        const int  inf = 0x3f3f3f3f; 
        const int _inf = 0xc0c0c0c0;

        int arr1[100]; 

        memset(arr1,  0,   sizeof(arr1));    
        memset(arr1, -1,   sizeof(arr1));     
        memset(arr1, 0x3f, sizeof(arr1));   // arr1[i] =  inf;
        memset(arr1, 0xc0, sizeof(arr1));   // arr1[i] = _inf;

         //for 64 bit value
        
        const long long  Inf = 0x3f3f3f3f3f3f3f3f; 
        const long long _Inf = 0xc0c0c0c0c0c0c0c0;

        long long arr2[100]; 

        memset(arr2,  0,     sizeof(arr2));    
        memset(arr2, -1,     sizeof(arr2));     
        memset(arr2, 0x3f3f, sizeof(arr2));   // arr2[i] =  INF
        memset(arr2, 0xc0c0, sizeof(arr2));   // arr2[i] = _INF

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
