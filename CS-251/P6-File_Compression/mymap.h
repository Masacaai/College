/*
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains the mymap class used to implement a
    map using a self-balancing threaded binary search tree.
*/

#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {
            NODE* node = curr;
            curr = curr->right;
            NODE* prev = curr;

            if (!node->isThreaded) {
                while(curr) {
                    prev = curr;
                    curr = curr->left;
                }
                curr = prev;
            }
            return iterator(curr);
        }
    };

    //
    // _string:
    //
    // This function is called recursively to perform in-order traversal
    // for toString()
    // O(n)
    //
    void _string(NODE* cur, stringstream &s) {
        if (cur) {
            _string(cur->left, s);
            s << "key: " << cur->key << " value: " << cur->value << endl;
            if (!cur->isThreaded) {
                _string(cur->right, s);
            }
        }
    }

    //
    // _vector:
    //
    // This function is called recursively to perform in-order traversal
    // for toVector()
    // O(n)
    //
    void _vector(NODE* cur, vector<pair<keyType, valueType>> &v) {
        if (cur) {
            _vector(cur->left, v);
            v.push_back({cur->key, cur->value});
            if (!cur->isThreaded) {
                _vector(cur->right, v);
            }
        }
    }

    //
    // _vectorN:
    //
    // This function is called recursively to perform in-order traversal
    // for balance()
    // O(n)
    //
    void _vectorN(NODE* cur, vector<NODE*> &v) {
        if (cur) {
            _vectorN(cur->left, v);
            v.push_back(cur);
            if (!cur->isThreaded) {
                _vectorN(cur->right, v);
            }
        }
    }

    //
    // _clear:
    //
    // This function is called recursively to perform post-order traversal
    // for clear()
    // O(n)
    //
    void _clear(NODE* cur, NODE* prev) {
        if (cur) {
            _clear(cur->left, cur);
            if (!cur->isThreaded) {
                _clear(cur->right, cur);
            }
            delete cur;
        }
    }

    //
    // putCopy:
    //
    // This function is used to insert nodes into the tree when making a copy
    // for copy operator and copy constructor
    // O(logn)
    //
    void putCopy(keyType key, valueType value) {
        NODE* prev = nullptr;
        NODE* cur = root;

        while (cur != nullptr) {
            if (key < cur->key) {
                cur->nL++;
                prev = cur;
                cur = cur->left;
            } else {
                cur->nR++;
                prev = cur;
                if (cur->isThreaded) {
                    cur = nullptr;
                } else {
                    cur = cur->right;
                }
            }
        }
        addNode(cur, prev, key, value);
    }

    //
    // _copy:
    //
    // This function is called recursively to perform pre-order traversal
    // for =operator and copy constructor
    // O(nlogn)
    //
    void _copy(NODE* otherNode) {
        if (otherNode) {
            putCopy(otherNode->key, otherNode->value);
            _copy(otherNode->left);
            if (!otherNode->isThreaded) {
                _copy(otherNode->right);
            }
        }
    }

    //
    // _check:
    //
    // This function is called recursively to perform pre-order traversal
    // for checkBalance()
    // O(n)
    //
    void _check(NODE* cur, stringstream &s) {
        if (cur) {
            s << "key: " << cur->key << ", nL: " << cur->nL << ", nR: " << cur->nR << endl;
            _check(cur->left, s);
            if (!cur->isThreaded) {
                _check(cur->right, s);
            }
        }
    }

    //
    // addNode:
    //
    // This function is used to add a node to the tree in the map
    // O(1)
    //
    void addNode(NODE* cur, NODE* prev, keyType key, valueType value) {
        NODE* n = new NODE();
        n->key = key;
        n->value = value;
        n->nL = 0;
        n->nR = 0;
        n->left = nullptr;
        n->right = nullptr;

        if (!prev) {
            root = n;
        } else if (key < prev->key) {
            prev->left = n;
            n->right = prev;
            n->isThreaded = true;
        } else {
            if (prev->isThreaded) {
                n->right = prev->right;
                n->isThreaded = true;    
                prev->right = n;
                prev->isThreaded = false;
            } else {
                prev->right = n;
            }
        }
        size++;
    }
    
    //
    // checkSeeSaw:
    //
    // This function is used to check the see-saw balance property
    // and return the violator and parent node if not satisfied.
    // O(1)
    //
    void checkSeeSaw(NODE* cur, NODE* prev, NODE* &vio, NODE* &par) {
        if (max(cur->nL, cur->nR) > 2 * min(cur->nL, cur->nR) + 1) {
            vio = cur;
            par = prev;
        }
    }

    //
    // _balance:
    //
    // This function is called recursively to perform pre-order traversal
    // for balanceTree()
    // O(n)
    //
    int _balance(vector<NODE*> v, NODE* prev, int start, int end) {
        if (start > end) {
            return 0;
        } else {
            int mid = (start + end) / 2;
            NODE* n = v[mid];
            n->isThreaded = false;
            n->left = nullptr;
            n->right = nullptr;
            if (!prev) {    
                root = n;
            } else if (n->key < prev->key) {
                prev->left = n;
                n->right = prev;
                n->isThreaded = true;
            } else {
                if (prev->isThreaded) {
                    n->right = prev->right;
                    n->isThreaded = true;    
                    prev->right = n;
                    prev->isThreaded = false;
                } else {
                    prev->right = n;
                }
            }   
            n->nL = _balance(v, v[mid], start, mid - 1);
            n->nR = _balance(v, v[mid], mid + 1, end);
            return n->nL + n->nR + 1;
        }
    }

    //
    // balanceTree:
    //
    // This function is used to check and balance the tree
    // O(n)
    //
    void balanceTree(NODE* vio, NODE* par) {
        vector<NODE*> v;
        _vectorN(vio, v);
        _balance(v, par, 0, v.size() - 1);
    }

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
        root = nullptr;
        size = 0;
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) {
        root = nullptr;
        size = 0;
        _copy(other.root);
    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) {
        clear();
        _copy(other.root);
        return *this;
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {
        _clear(root, nullptr);
        root = nullptr;
        size = 0;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {
        clear();
    }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {
        NODE* prev = nullptr;
        NODE* cur = root;
        NODE* vio = nullptr; // Variable used to store violator node
        NODE* par = nullptr; // Variable used to store parent of violator node
        bool isPresent = contains(key); 

        while (cur != nullptr) {
            if (key == cur->key) {
                cur->value = value;
                return;
            }
            if (key < cur->key) {
                if (!isPresent) { // If key is NOT present in the tree...
                    cur->nL++;
                    if (!vio) {  // If violator has not been found already...  
                        checkSeeSaw(cur, prev, vio, par);
                    }
                }
                prev = cur;
                cur = cur->left;
            } else {
                if (!isPresent) { // If key is NOT present in the tree...
                    cur->nR++;
                    if (!vio) {   // If violator has not been found already... 
                        checkSeeSaw(cur, prev, vio, par);
                    }
                }
                prev = cur;
                if (cur->isThreaded) {
                    cur = nullptr;
                } else {    
                    cur = cur->right;
                }
            }
        }

        addNode(cur, prev, key, value);
        
        if (vio) { // If violator node was found...
            balanceTree(vio, par); 
        }
    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) {
        NODE* prev = nullptr;
        NODE* cur = root;

        while (cur != nullptr) {
            if (key == cur->key) {
                return true;
            }
            if (key < cur->key) {
                prev = cur;
                cur = cur->left;
            } else {
                prev = cur;
                if (cur->isThreaded) {
                    cur = nullptr;
                } else {    
                    cur = cur->right;
                }
            }
        }
        return false;  
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) {
        NODE* prev = nullptr;
        NODE* cur = root;

        while (cur != nullptr) {
            if (key == cur->key) {
                return cur->value;
            }
            if (key < cur->key) {
                prev = cur;
                cur = cur->left;
            } else {
                prev = cur;
                if (cur->isThreaded) {
                    cur = nullptr;
                } else {    
                    cur = cur->right;
                }
            }
        }
        return valueType();
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {
        NODE* prev = nullptr;
        NODE* cur = root;
        NODE* vio = nullptr; // Variable used to store violator node
        NODE* par = nullptr; // Variable used to store parent of violator node
        bool isPresent = contains(key);

        while (cur != nullptr) {
            if (key == cur->key) {
                return cur->value;
            }
            if (key < cur->key) {
                if (!isPresent) { // If key is NOT present in the tree...
                    cur->nL++;
                    if (!vio) {  // If violator has not been found already...  
                        checkSeeSaw(cur, prev, vio, par);
                    }
                } 
                prev = cur;
                cur = cur->left;
            } else {
                if (!isPresent) { // If key is NOT present in the tree...
                    cur->nR++;
                    if (!vio) {   // If violator has not been found already...
                        checkSeeSaw(cur, prev, vio, par);
                    }
                }
                prev = cur;
                if (cur->isThreaded) {
                    cur = nullptr;
                } else {    
                    cur = cur->right;
                }
            }
        }

        addNode(cur, prev, key, valueType());

        if (vio) { // If violator node was found...
            balanceTree(vio, par);
        }
        
        return valueType();  
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {
        return size; 
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() {
        NODE* prev = nullptr;
        NODE* cur = root;
        
        while (cur != nullptr) {
            prev = cur;
            cur = cur->left;
        }
        return iterator(prev);
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // 
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(nullptr);
    }

    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() {
        stringstream s("");
        _string(root, s);
        return s.str();  
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<pair<keyType, valueType> > toVector() {
        vector<pair<keyType, valueType>> vec;
        _vector(root, vec);
        return vec;
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() {
        stringstream s;
        _check(root, s);
        return s.str();
    }
};
