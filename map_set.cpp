#include <iostream>
#include <memory>
#include <vector>
#include <stdlib.h> 
#include <time.h>
#include <chrono>
#include <algorithm>
#include "map_set_headers.h"
#include "map-set.h"

using namespace std;

//to do: add decrement

int size_set = 30;

//void time_stamps(const unique_ptr <sorts> & sort_type, const vector <int> & pass_data);

template <class T, class U>
node<T,U> * map_set<T,U>::begin;
template <class T, class U>
node<T,U> * map_set<T,U>::end;

template <class T, class U>
bool map_set<T,U>::multi_query;	

int main()
{
  
  vector <int> pass_key(size_set);
  vector <string> pass_assoc(size_set);
  
  for(int i = 0; i < size_set; i++)
  { 
	  int j = rand() % size_set + 1;
	  pass_key[i] = j;
  	  pass_assoc[i] = "testing";
  }

  unique_ptr < map_set<int,string> > map_tree = make_unique < map_set<int,string> >(true);
   
  for(int i = 0; i < size_set; i++)
  {
	  map_tree->insert(pass_key[i],pass_assoc[i]);
  }
  
  map_tree->printOrder();
  
	int j = rand() % size_set + 1;
	cout << j << endl;
	
    map_tree->insert(j,"testing1");
	
	cout << "Sorted Correctly?: " << map_tree->check_sorted() << endl;
	map_tree->printOrder();
	
    map_tree->search_key(j);

    map_tree->remove(j);
	
	cout << "Sorted Correctly?: " << map_tree->check_sorted() << endl;
	map_tree->printOrder();

  node<int,string> * my_iterator;
  
  int count = 0;
  for(my_iterator = map_set<int,string>::begin; my_iterator != map_set<int,string>::end; incr(my_iterator))
  {
	  cout << my_iterator->key_value << endl;	 
  }
  
  cout << map_tree->check_sorted() << endl;

  // cout << "end (parent)" << endl;
  // cout << map_tree->end->parent->key_value << endl;
  // cout << map_tree->end->parent->asc_val << endl;
  
  // cout << "Binary Tree Stats:" << endl;
  // cout << endl;
  // time_stamps(bin_tree,pass_data);
  
  // unique_ptr <sorts> quicks = make_unique <quick>();

  // cout << endl;  
  // cout << "Quick Stats:" << endl;
  // cout << endl;
  // time_stamps(quicks,pass_data);
  
  // unique_ptr <sorts> merged = make_unique <_merge>();

  // cout << endl;  
  // cout << "Merge Stats:" << endl;
  // cout << endl;
  // time_stamps(merged,pass_data);
  
}

// void time_stamps(const unique_ptr <sorts> & sort_type, const vector <int> & pass_data)
// {	

	// auto begin = chrono::high_resolution_clock::now();
    // sort_type->build(pass_data);
	// auto end = chrono::high_resolution_clock::now();
	// double timeSec = chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()*1.0e-9;
	// cout << "Time to build: " << timeSec << endl;
	
    // cout << "Sorted Correctly?: " << sort_type->check_sorted() << endl;
	
	// begin = chrono::high_resolution_clock::now();
    // sort_type->printQuiet();
	// end = chrono::high_resolution_clock::now();
	// timeSec = chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()*1.0e-9;
	// cout << "Time to Traverse: " << timeSec << endl;
	
	// int j = rand() % size_set + 1;
	
	// begin = chrono::high_resolution_clock::now();
    // sort_type->insert(j);
	// end = chrono::high_resolution_clock::now();
	// timeSec = chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()*1.0e-9;
	// cout << "Time to Insert new Key: " << timeSec << endl;
	
	 // cout << "Sorted Correctly?: " << sort_type->check_sorted() << endl;
	
	// begin = chrono::high_resolution_clock::now();
    // sort_type->search_key(j);
	// end = chrono::high_resolution_clock::now();
	// timeSec = chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()*1.0e-9;
	// cout << "Time to Search Key: " << timeSec << endl;

	// begin = chrono::high_resolution_clock::now();
    // sort_type->remove(j);
	// end = chrono::high_resolution_clock::now();
	// timeSec = chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()*1.0e-9;
	// cout << "Time to Remove Key: " << timeSec << endl;
	
	// cout << "Sorted Correctly?: " << sort_type->check_sorted() << endl;
	
// }

















