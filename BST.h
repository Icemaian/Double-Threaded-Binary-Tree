// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

/*
* File:   BST.h
* CSIS 215-<D01>
* Author Isaac Craig 
* source https://algorithms.tutorialhorizon.com/binary-tree-postorder-traversal-non-recursive-approach/
*/

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"
#include <string>
#include <stack>

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key,E> {
private:
  BSTNode<Key,E>* root;     // Root of the BST
  BSTNode<Key, E>* parent;  // temp storage Node
  int nodecount;		    // Number of nodes in the BST

  // Private "helper" functions
  void clearhelp(BSTNode<Key, E>*);
  BSTNode<Key,E>* inserthelp(BSTNode<Key, E>*,
                              const Key&, const E&);
  BSTNode<Key,E>* deletemin(BSTNode<Key, E>*);
  BSTNode<Key,E>* getmin(BSTNode<Key, E>*);
  BSTNode<Key,E>* removehelp(BSTNode<Key, E>*, const Key&);
  E* findhelp(BSTNode<Key, E>*, const Key&) const;
  void printhelp(BSTNode<Key, E>*, int) const;
  void vist(BSTNode<Key, E>*) const;

public:
  BST() { root = NULL; nodecount = 0; }  // Constructor
  
  //Note from Prof Sipantzi -- I've commented out the destructor
  //since you would have to change clearhelp() to make it work with
  //doubly-threaded trees and that is not part of the assignment.
  //~BST() { clearhelp(root); }            // Destructor

  void clear()   // Reinitialize tree
  {clearhelp(root); root = NULL; nodecount = 0;};

  // Insert a record into the tree.
  // k Key value of the record.
  // e The record to insert.
  void insert(const Key& k, const E& e) {
    root = inserthelp(root, k, e);
    nodecount++;
  }

  // Remove a record from the tree.
  // k Key value of record to remove.
  // Return: The record removed, or NULL if there is none.
  E* remove(const Key& k) {
    E* temp = findhelp(root, k);   // First find it
    if (temp != NULL) {
      root = removehelp(root, k);
      nodecount--;
    }
    return temp;
  }
  // Remove and return the root node from the dictionary.
  // Return: The record removed, null if tree is empty.
  E* removeAny() {  // Delete min value
    if (root != NULL) {
      E* temp = new E;
      *temp = root->element();
      root = removehelp(root, root->key());
      nodecount--;
      return temp;
    }
    else return NULL;
  }

  // Return Record with key value k, NULL if none exist.
  // k: The key value to find. */
  // Return some record matching "k".
  // Return true if such exists, false otherwise. If
  // multiple records match "k", return an arbitrary one.
  E* find(const Key& k) const { return findhelp(root, k); }

  // Return the number of records in the dictionary.
  int size() { return nodecount; }

  void print() const { // Print the contents of the BST
    if (root == NULL) cout << "The BST is empty.\n";
    else printhelp(root, 0);
  }
  
  // prints root in order
  void inOrder() const {
	  if (root == NULL)
		  cout << "The BST is empty.\n";
	  else
		  inOrderHelper(root, nodecount);
  }

  void postOrder() const {
	  if (root == NULL)
		  cout << "The BST is empty.\n";
	  else
		  postOrderHelper(root, nodecount);
  }
};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key,E>* r) const {
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
  if (root == NULL) return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(
	BSTNode<Key, E>* root, const Key& k, const E& it) {
	if (root == NULL) {// Empty tree: create node
		BSTNode<Key, E>* child = new BSTNode<Key, E>(k, it, NULL, NULL);
		if (parent == NULL)
			return child;

		if (child->key()  < parent->key() ) { // if new node was placed on the left
			if(parent->left() ==NULL)
				child->setLeft(parent);
			else
				child->setLeft(parent->left());
			child->setRight(parent);
		}
		else {					// if new node was placed on the right
			if (parent->right() == NULL)
				child->setRight(parent);
			else
				child->setRight(parent->right());
			child->setLeft(parent);
		}
		return child;
	}
	parent = root;
  if (k < root->key()) {
	  if (root->getLeftBit() == 1) {
		  root->setLeft(inserthelp(NULL, k, it));
		  parent->setLeftBit(0);
	  }
	  else
		  root->setLeft(inserthelp(root->left(), k, it));
  }
  else {
	  if (root->getRightBit() == 1) {
		  root->setRight(inserthelp(NULL, k, it));
		  root->setRightBit(0);
	  }
	  else
		  root->setRight(inserthelp(root->right(), k, it));
  }
  return root;       // Return tree with node inserted
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL)
    return rt;
  else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL) // Found min
    return rt->right();
  else {                      // Continue left
    rt->setLeft(deletemin(rt->left()));
    return rt;
  }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
  if (rt == NULL) return NULL;    // k is not in tree
  else if (k < rt->key())
    rt->setLeft(removehelp(rt->left(), k));
  else if (k > rt->key())
    rt->setRight(removehelp(rt->right(), k));
  else {                            // Found: remove it
    BSTNode<Key, E>* temp = rt;
    if (rt->left() == NULL) {     // Only a right child
      rt = rt->right();         //  so point to right
      delete temp;
    }
    else if (rt->right() == NULL) { // Only a left child
      rt = rt->left();          //  so point to left
      delete temp;
    }
    else {                    // Both children are non-empty
      BSTNode<Key, E>* temp = getmin(rt->right());
      rt->setElement(temp->element());
      rt->setKey(temp->key());
      rt->setRight(deletemin(rt->right()));
      delete temp;
    }
  }
  return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const {
  if (root == NULL) return NULL;          // Empty tree
  if (k < root->key())
    return findhelp(root->left(), k);   // Check left
  else if (k > root->key())
    return findhelp(root->right(), k);  // Check right
  else {
      E* temp = new E;
      *temp = root->element();
      return temp;  // Found it
  }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const {
	if (root == NULL) return;           // Empty tree
	if (root->getLeftBit()==0)
		printhelp(root->left(), level + 1);   // Do left subtree
	for (int i = 0; i < level; i++)         // Indent to level
		cout << "  ";
	cout << root->key() << "\n";        // Print node value
	if(root->getRightBit()==0)
		printhelp(root->right(), level + 1);  // Do right subtree

}

template <typename Key, typename E>
void postOrderHelper(BSTNode<Key, E>* root, int size) { // Post order print
	stack<BSTNode<Key, E>* > stack1;					// source https://algorithms.tutorialhorizon.com/binary-tree-postorder-traversal-non-recursive-approach/
	stack<BSTNode<Key, E>* > stack2;
	stack1.push(root);

	while (!stack1.empty()) {
		BSTNode<Key, E>*  temp = stack1.top();
		stack1.pop();
		stack2.push(temp);
		if (temp->getLeftBit() == 0) {
			stack1.push(temp->left());
		}
		if (temp->getRightBit() == 0) {
			stack1.push(temp->right());
		}
	}

	while (stack2.empty() == false) {
		BSTNode<Key, E>*  temp = stack2.top();
		cout << temp->element() << endl;
		stack2.pop();
	}
}

template <typename Key, typename E>
void inOrderHelper(BSTNode<Key, E>* root, int size) { // In order print
		// create an empty stack
		stack<BSTNode<Key, E>* > stack;
		bool empty = false;
		// start from root node (set current node to root node)
		BSTNode<Key, E>*  curr = root;
		// if current node is null and stack is also empty, we're done

		while (!empty)
		{
			// if current node is not null, push it to the stack (defer it)
			// and move to its left child
			if (curr->getLeftBit() == 0 ) {
				stack.push(curr);
				curr = curr->left();
			}
			else if (curr->getRightBit() == 0) {
				cout << curr->element() << endl;
				size--;
				curr = curr->right();
			}
			else {
				if (curr->getLeftBit() == 1 && curr->getRightBit() == 1) {
					cout << curr->element() << endl;
					size--;
					curr = stack.top();
					cout << curr->element() << endl;
					size--;
					stack.pop();
					curr = curr->right();

				}
				else {
					curr = stack.top();
					stack.pop();
					cout << curr->element() << endl;
					size--;
					curr = curr->right();
				}
			}
			if (size == 0)
				empty = true;
		}
}

template <typename Key, typename E>
int height(BSTNode<Key, E>* root) { // Gets the height of the Binary Tree
	if (root == NULL)	return 0;
	else {
		int lDepth = 0;
		int rDepth = 0;
		if (root->getLeftBit() == 0) {
			lDepth = height(root->left());
		}
		else if (root->getRightBit() == 0) {
			rDepth = height(root->right());
		}
		if (lDepth > rDepth)
			return lDepth + 1;
		else
			return rDepth + 1;
	}
}

template <typename Key, typename E> // prints a nodes key based off of a pointer
void printNode(BSTNode<Key, E>* root) {
	cout << root->key();
}
#endif