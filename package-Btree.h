//
//  package-Btree.h
//  
//
//
//

#ifndef ____package_Btree__
#define ____package_Btree__

#include <stdio.h>
#include <iostream>

struct tree_node
{
    unsigned long key;
    std :: string name;
    std :: string headPackage;
    bool isDependency;
    tree_node *left;
    tree_node *right;
};


class binary_tree
{
public:
    // constructors:
    binary_tree (); // default
    // destructor:
    ~binary_tree();
    // binary tree operations:
    int size() const;
    int height() const;
    void remove(unsigned long key_value );
    void insert(unsigned long key_value, std :: string name_value, std :: string headPackage_value, bool dependencyFlag);
    tree_node* search(unsigned long key_value);
    bool getDependencyFlag(unsigned long key_value);
    std::string getHeadPack(unsigned long key_value);



private:
    binary_tree (tree_node *nodePtr); // private constructor
    // A function to copy the tree to a new tree
    void copy_tree (tree_node *tree_ptr,
                    tree_node *& new_ptr) const;
    // private function called by public destructor
    void destroy (tree_node *& tree_ptr);
    void insert(tree_node * & current, unsigned long key_value, std :: string name_value, std :: string headPackage_value, bool dependencyFlag);
    void remove(tree_node * & current, unsigned long key_value );
    tree_node * find_min( tree_node *current );
    tree_node * search(tree_node * & current, unsigned long key_value);
    
    // pointer to root of tree
    tree_node *root;
};

#endif /* defined(____package_Btree__) */
