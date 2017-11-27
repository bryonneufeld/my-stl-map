#include <iostream>
#include <memory>
#include <vector>
#include <stdlib.h> 
#include <time.h>
#include <chrono>

using namespace std;

//for the btree
template <class T, class U>
struct node
{
  T key_value;
  U asc_val;
  node *left;
  node *right;
  node *parent;
};

template <class T, class U>
class map_set
{
    public:
		//true for multimap, false for map
        map_set(bool multi_switch);
        ~map_set();
		
		static bool multi_query;	

        void insert(T key, U asc_val);
	    void remove(T key);
        void destroy_tree();
		void printOrder();
		void printQuiet();
		bool check_sorted();
		void search_key(T key);
		
		//the static here allows us to access outside of class members
		//will point to the begin (left most key)
        static node<T,U> *begin;
		//will point to the end (NULL that is 'right' of the right most)
        static node<T,U> *end;
		
		//friend overloads of increment, decrement (returns pointer to node):
		template <class V, class W>
		friend void incr(node<V,W> * &to_increment);
		// node<T,U>* operator--(node<T,U> *to_decrement);
		//finds the next in line node to the right sub-branch
		template <class V, class W>
		friend node<V,W> * find_right(node<V,W> *leaf);
		//finds the next in line parent node (to right side)
		template <class V, class W>
		friend node<V,W> * find_parent_right(node<V,W> *leaf);

   private:
        void destroy_tree(node<T,U> *leaf);
        void insert(T key, U asc_val, node<T,U> *leaf);
        node<T,U> *search(T key);
        node<T,U> *search(T key, node<T,U> *leaf);
		void printOrder(node<T,U> *leaf);
		void printQuiet(node<T,U> *leaf);
		void check_sorted(node<T,U> *leaf, T & place_value, bool & b1);
		//collects the integers below the leaf, so we can remove a key
		void collect_for_remove(node<T,U> *leaf, vector <T> & collect1, vector <U> & collect2);

		bool right_check(T key1, T key2)
		{
			if(multi_query)
			{
			    return key1 >= key2;
			}
			else
			{
				return key1 > key2;
			}			
		}
		
		static bool parent_right_check(T key1, T key2)
		{
			if(multi_query)
			{
			    return key1 > key2;
			}
			else
			{
				return key1 >= key2;
			}			
		}
		
        node<T,U> *root;

};
















