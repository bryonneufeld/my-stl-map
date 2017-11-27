#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <class T, class U>
map_set<T,U>::map_set(bool multi_switch)
{
  root=NULL;
  begin=NULL;
  multi_query = multi_switch;
  //end is a new node, but isn't ever assigned any values
  end = new node<T,U>;
}

template <class T, class U>
map_set<T,U>::~map_set()
{
  destroy_tree();
}

template <class T, class U>
void map_set<T,U>::destroy_tree()
{
  destroy_tree(root);
  delete end;
}

template <class T, class U>
void map_set<T,U>::destroy_tree(node<T,U> *leaf)
{
  if(leaf!=NULL)
  {
	// cout << leaf->key_value << " destroyed" << endl;
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}

template <class T, class U>
void map_set<T,U>::insert(T key, U asc_val)
{
  if(root!=NULL)
    insert(key,asc_val,root);
  else
  {
    root=new node<T,U>;
    root->key_value=key;
	root->asc_val=asc_val;
    root->left=NULL;
    root->right=NULL;
	root->parent=NULL;
  }
  
	//right now, I am setting up to make begin update at each insertion
	node<T,U> *leaf;
  
	if(root->left == NULL)
	{
		leaf = root;
	}
	else
	{
		leaf = root->left;
		while(leaf->left != NULL)
		{
		  leaf = leaf->left;
		}
	}
	begin = leaf; 

}

template <class T, class U>
void map_set<T,U>::insert(T key, U asc_val, node<T,U> *leaf)
{
  if(key < leaf->key_value)
  {
    if(leaf->left!=NULL)
     insert(key,asc_val,leaf->left);
    else
    {
      leaf->left=new node<T,U>;
      leaf->left->key_value=key;
	  leaf->left->asc_val=asc_val;
      leaf->left->left=NULL;    //Sets the left child of the child node to null
      leaf->left->right=NULL;   //Sets the right child of the child node to null
  	  leaf->left->parent=leaf;
    }  
  }
  else if(right_check(key,leaf->key_value))
  {
    if(leaf->right!=NULL)
      insert(key,asc_val,leaf->right);
    else
    {
      leaf->right=new node<T,U>;
      leaf->right->key_value=key;
	  leaf->right->asc_val=asc_val;
      leaf->right->left=NULL;  //Sets the left child of the child node to null
      leaf->right->right=NULL; //Sets the right child of the child node to null
      leaf->right->parent=leaf; //Sets the right child of the child node to null
    }
  }
}

template <class T, class U>
void map_set<T,U>::remove(T key)
{
	//find if there is a key existing:
	node<T,U> * points_to = search(key);

	if(points_to != NULL)
	{
		//track who the parent is:
		node<T,U> * up_one = points_to->parent;
		
		vector <T> collection1;
		vector <U> collection2;
		//collect the ints below points_to, skipping points_to:
		collect_for_remove(points_to->left,collection1,collection2);
		collect_for_remove(points_to->right,collection1,collection2);
		//now destroy, which goes from top, to down
		destroy_tree(points_to);
		
		//real pain here, ensures parent still points to either NULL or valid branch:
		//probably a smart pointer would help here
		if(key >= up_one->key_value)
		{
			up_one->right=NULL;
		}
		else
		{
			up_one->left=NULL;
		}
		
		//rebuild the collected branches:
		for(int i = 0; i < collection1.size(); i++)
		{
			insert(collection1[i],collection2[i]);
		}
	}
	else
	{
		cout << "could not remove key, " << key << " was not found" << endl;
	}
}

template <class T, class U>
void map_set<T,U>::collect_for_remove(node<T,U> *leaf, vector <T> & collect1, vector <U> & collect2)
{
	if(leaf !=NULL)
	{
		collect_for_remove(leaf->left,collect1,collect2);
		collect1.push_back(leaf->key_value);
		collect2.push_back(leaf->asc_val);
		collect_for_remove(leaf->right,collect1,collect2);
	}
}

template <class T, class U>
void map_set<T,U>::search_key(T key)
{
	node<T,U> * points_to = search(key);

	if(points_to == NULL)
	{
		cout << "No Match" << endl;
	}
	else
	{
		cout << "Found " << points_to->key_value << endl;
	}	
}

template <class T, class U>
node<T,U> *map_set<T,U>::search(T key)
{
  return search(key, root);
}

template <class T, class U>
node<T,U> *map_set<T,U>::search(T key, node<T,U> *leaf)
{
  if(leaf!=NULL)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else if(right_check(key,leaf->key_value))
      return search(key, leaf->right);
  }
  else return NULL;
}

template <class T, class U>
void map_set<T,U>::printOrder()
{
	printOrder(root);
	cout << endl;
}

template <class T, class U>
void map_set<T,U>::printOrder(node<T,U> *leaf)
{
	if(leaf !=NULL)
	{
		printOrder(leaf->left);		
		cout << leaf->key_value << " " << leaf->asc_val << endl;
		printOrder(leaf->right);
	}
}

template <class T, class U>
void map_set<T,U>::printQuiet()
{
	printQuiet(root);
}

template <class T, class U>
void map_set<T,U>::printQuiet(node<T,U> *leaf)
{
	if(leaf !=NULL)
	{
		printQuiet(leaf->left);
		leaf->key_value;
		leaf->asc_val;
		printQuiet(leaf->right);
	}
}

template <class T, class U>
bool map_set<T,U>::check_sorted()
{
	bool b1 = true;
	T place_value = begin->key_value;
	place_value--;
	check_sorted(root,place_value,b1);
	return b1;
}

template <class T, class U>
void map_set<T,U>::check_sorted(node<T,U> *leaf, T & place_value, bool & b1)
{
	if(leaf !=NULL)
	{
		check_sorted(leaf->left,place_value,b1);
		if(leaf->key_value < place_value)
		{
			b1 = false;
			place_value = leaf->key_value;
		}
		else
		{
			place_value = leaf->key_value;
		}
		check_sorted(leaf->right,place_value,b1);
	}	
}

//finds the next in line node to the right sub-branch
template <class T, class U>
node<T,U> * find_right(node<T,U> *leaf)
{
	node<T,U> *temp;

	if(leaf->right == NULL)
	{
		temp == NULL;
		return temp;
	}
	else
	{
		temp = leaf->right;
	}

	if(temp->left == NULL)
	{
		return temp;
	}
	else
	{	
		while(temp->left != NULL)
		{
			temp = temp->left;
		}
	}

	return temp;
}

//finds next in line for parent (to right side)
template <class T, class U>
node<T,U> * find_parent_right(node<T,U> *leaf)
{
	node<T,U> *temp = NULL;

	if(leaf->parent == NULL)
	{
		temp == NULL;
		return temp;
	}
	else
	{
		temp = leaf;
		while(temp->parent != NULL)
		{
			temp = temp->parent;
			if(map_set<T,U>::parent_right_check(temp->key_value,leaf->key_value))
			{
				return temp;
			}
		}
	}

	return temp;
	
}

template <class T, class U>
void incr(node<T,U> * &to_increment)
{

	node<T,U> * placer;
	
	//priority 1: over right
	if(to_increment->right != NULL)
	{
		placer = find_right(to_increment);
	}
	//priority 2: up parent
	else if(to_increment->parent != NULL)
	{
		placer = find_parent_right(to_increment);
	}
	//priority 3: we are at the end
	if(placer == NULL || placer->key_value < to_increment->key_value)
	{
		placer = map_set<T,U>::end;
	}

	to_increment = placer;

}















