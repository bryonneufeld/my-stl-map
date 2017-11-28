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

//size of the map (number of keys)
int size_set = 1000;

//these are static members of map_set
/**************************************/
//pointer to beginning of the map (left most)
template <class T, class U>
node<T,U> * map_set<T,U>::begin;

//pointer to the end of the map (right most)
template <class T, class U>
node<T,U> * map_set<T,U>::end;

//is it a multi-map?  set in the constructor argument
template <class T, class U>
bool map_set<T,U>::multi_query;
/***************************************/

int main()
{
    //a couple of vectors for building the map, using ints and strings
    vector <int> pass_key(size_set);
    vector <string> pass_assoc(size_set);

    //just filling up with random ints and the same string each time
    for(int i = 0; i < size_set; i++)
    {
        int j = rand() % size_set + 1;
        pass_key[i] = j;
        pass_assoc[i] = "testing";
    }

    //make with a unique pointer:
    unique_ptr < map_set<int,string> > map_tree = make_unique < map_set<int,string> >(true);

    //insert into the map:
    for(int i = 0; i < size_set; i++)
    {
        map_tree->insert(pass_key[i],pass_assoc[i]);
    }

    //does a print of the map:
    map_tree->printOrder();

    //for inserting:
    int j = rand() % size_set + 1;
    cout << j << endl;

    map_tree->insert(j,"testing1");

    //check if sorted correctly
    cout << "Sorted Correctly?: " << map_tree->check_sorted() << endl;
    map_tree->printOrder();

    //search and remove the new key
    map_tree->search_key(j);

    map_tree->remove(j);

    //verify still sorted correctly
    cout << "Sorted Correctly?: " << map_tree->check_sorted() << endl;
    map_tree->printOrder();

    //my personal iterator for traversing the map, only have increment implemented so far
    node<int,string> * my_iterator;

    for(my_iterator = map_set<int,string>::begin; my_iterator != map_set<int,string>::end; incr(my_iterator))
    {
      cout << my_iterator->key_value << endl;
    }

    //one last sorting check:
    cout << map_tree->check_sorted() << endl;

}










