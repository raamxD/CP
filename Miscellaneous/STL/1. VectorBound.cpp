#include <bits/stdc++.h>
using namespace std;

int main() {
   
   
/*
               vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
                  

   rend(v)  begin(v)                                                rbegin(v)  end(v)
      .       .                                                         .       .
      |       |                                                         |       |
      V       V                                                         V       V
   +--------------------------------------------------------------------------------+
   | start |   1  |  3  |     .  .  .  .  key   .  .  .  .            | 12 | finish |
   +--------------------------------------------------------------------------------+
   
   Declaring forward iterator : vector<int>::iterator itr;
   Declaring reverse iterator : vector<int>::reverse_iterator itr;

   or simply use auto keyword.
      
*/    
   
   /*
    * lower_bound(start iterator, end iterator, key) : 
    *
    * On ascending sorted vector,
    * 	*lower_bound(begin(v), end(v), key) 						->	returns First Element >= key  
    *
    * On descending sorted vector,
    * 	*lower_bound(begin(v), end(v), key, greater<int>()) 	->	returns First Element <= key
    *
	 */

   /*
    * upper_bound(start iterator, end iterator, key)
    * 
    * On ascending sorted vector,
    * 	*upper_bound(begin(v), end(v), key) 						->	returns First Element > key   
    *
    * On descending sorted vector,
    * 	*upper_bound(begin(v), end(v), key, greater<int>())   ->	returns  First Element < key
    *
    */
   
   
/// FOR ASCENDING SORTED ARRAY
/////////////////////////////////////////////////////////////////////////////////////

   /*    LAST ELEMENT STRICTLY SMALLER THAN THE KEY VALUE      */

   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 1;
   auto it = upper_bound(rbegin(v), rend(v), key, greater<int>());
   if(it == rend(v)){
      cout << "No Such Element!!\n";
   }else{
      cout << "Last Element Strictly Smaller than key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS STRICTLY SMALLER THAN THE KEY VALUE */
   
   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 7;
   int cnt = lower_bound(begin(v), end(v), key) - v.begin();
   cout << "Count of Elements Strictly Smaller than key : " << cnt << "\n";
   
/////////////////////////////////////////////////////////////////////////////////////

   /*    FIRST ELEMENT STRICTLY GREATER THAN THE KEY VALUE     */

   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 12;
   auto it = upper_bound(begin(v), end(v), key);
   if(it == end(v)){
      cout << "No Element!!\n";
   }else{
      cout << "First Element Strictly Greater than key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS STRICTLY GREATER THAN THE KEY VALUE */
   
   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 6;
   int cnt = end(v) - upper_bound(begin(v), end(v), key);
   cout << "Count of Elements Strictly Greater than key : " << cnt << "\n";

   
/////////////////////////////////////////////////////////////////////////////////////
   
   /*    LAST ELEMENT SMALLER THAN OR EQUAL TO THE KEY VALUE      */
   
   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 15;
   auto it = lower_bound(rbegin(v), rend(v), key, greater<int>());
   if(it == rend(v)){
      cout << "No Element!!\n";
   }else{
      cout << "Last Element Smaller than or equal to key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS SMALLER THAN OR EQUAL TO THE KEY VALUE    */
   
   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 12;
   int cnt = upper_bound(begin(v), end(v), key) - begin(v);
   cout << "Count of Elements Smaller than or equal to key : " << cnt << "\n";

/////////////////////////////////////////////////////////////////////////////////////

   /*    FIRST ELEMENT GREATER THAN OR EQUAL TO THE KEY VALUE     */

   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 11;
   auto it = lower_bound(begin(v), end(v), key);
   if(it == end(v)){
      cout << "No Element!!\n";
   }else{
      cout << "First Element Greater than or equal to key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS GREATER THAN OR EQUAL TO THE KEY VALUE    */
   
   vector<int> v = {1, 3, 5, 7, 7, 8, 9, 9, 10, 12};
   int key = 6;
   int cnt = end(v) - lower_bound(begin(v), end(v), key);
   cout << "Count of Elements Greater than or equal to key : " << cnt << "\n";

/////////////////////////////////////////////////////////////////////////////////////


/// FOR DESCENDING SORTED ARRAY
/////////////////////////////////////////////////////////////////////////////////////
   
   /*    FIRST ELEMENT STRICTLY SMALLER THAN THE KEY VALUE     */

   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = 11;
   auto it = upper_bound(begin(v), end(v), key, greater<int>());
   if(it == end(v)){
      cout << "No Such Element!!\n";
   }else{
      cout << "First Element Strictly Smaller than key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS STRICTLY SMALLER THAN THE KEY VALUE */
   
   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = 12;
   int cnt = end(v) - upper_bound(begin(v), end(v), key, greater<int>());
   cout << "Count of Elements Strictly Smaller than key : " << cnt << "\n";
   
/////////////////////////////////////////////////////////////////////////////////////

   /*    LAST ELEMENT STRICTLY GREATER THAN THE KEY VALUE      */

   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = -25;
   auto it = upper_bound(rbegin(v), rend(v), key);
   if(it == rend(v)){
      cout << "No Element!!\n";
   }else{
      cout << "Last Element Strictly Greater than key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS STRICTLY GREATER THAN THE KEY VALUE */
   
   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = 1;
   int cnt = rend(v) - upper_bound(rbegin(v), rend(v), key);
   cout << "Count of Elements Strictly Greater than key : " << cnt << "\n";

   
/////////////////////////////////////////////////////////////////////////////////////
   
   /*    FIRST ELEMENT SMALLER THAN OR EQUAL TO THE KEY VALUE     */
   
   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = 9;
   auto it = lower_bound(begin(v), end(v), key, greater<int>());
   if(it == end(v)){
      cout << "No Element!!\n";
   }else{
      cout << "First Element Smaller than or equal to key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS SMALLER THAN OR EQUAL TO THE KEY VALUE    */
   
   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = 9;
   int cnt = end(v) - lower_bound(begin(v), end(v), key, greater<int>());
   cout << "Count of Elements Smaller than or equal to key : " << cnt << "\n";

/////////////////////////////////////////////////////////////////////////////////////

   /*    LAST ELEMENT GREATER THAN OR EQUAL TO THE KEY VALUE      */

   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = 13;
   auto it = lower_bound(rbegin(v), rend(v), key);
   if(it == rend(v)){
      cout << "No Element!!\n";
   }else{
      cout << "Last Element Greater than or equal to key : " << *it << "\n";
   }
   
   /*    COUNT OF ELEMENTS GREATER THAN OR EQUAL TO THE KEY VALUE    */
   
   vector<int> v = {12, 10, 9, 9, 8, 7, 7, 5, 3, 1};
   int key = 1;
   int cnt = rend(v) - lower_bound(rbegin(v), rend(v), key);
   cout << "Count of Elements Greater than or equal to key : " << cnt << "\n";

/////////////////////////////////////////////////////////////////////////////////////

   return 0;
}