//
//  package-Btree.cpp
//  
//
//
//

#include "package-Btree.h"


binary_tree::binary_tree()
{
    root = NULL;
}


binary_tree::~binary_tree()
{
    destroy(root);
}

void binary_tree::destroy (tree_node *& tree_ptr)
{
    // postorder traversal
    if (tree_ptr != NULL) {
        destroy (tree_ptr->left); //
        destroy (tree_ptr->right);
        delete tree_ptr;
        tree_ptr = NULL;
    }
}

tree_node *binary_tree::search(unsigned long key_value)
{
    return search(root, key_value);
}

tree_node * binary_tree:: search(tree_node * & current, unsigned long key_value)
{
    if ( current == NULL )
        return NULL;
    else {
        if ( key_value < current->key )
            return search (current->left, key_value);
        else if ( key_value > current->key )
            return search ( current->right, key_value);
        else
            return current;
    }
}

void binary_tree:: insert(unsigned long key_value, std :: string name_value, std :: string headPackage_value, bool dependencyFlag){
    
    if(root!=NULL)
        insert(root,key_value,name_value,headPackage_value,dependencyFlag);
    else
    {
        root=new tree_node;
        root->key=key_value;
        root->name=name_value;
        root->isDependency=dependencyFlag;
        root->headPackage=headPackage_value;
        root->left=NULL;
        root->right=NULL;
    }

}


void binary_tree::insert(tree_node * & current, unsigned long key_value, std :: string name_value, std :: string headPackage_value, bool dependencyFlag){
    
    if(key_value< current->key)
    {
        if(current->left==NULL){
            current->left=new tree_node;
            current->left->key=key_value;
            current->left->name=name_value;
            current->left->isDependency=dependencyFlag;
            current->left->headPackage=headPackage_value;
            current->left->left=NULL;
            current->left->right=NULL; //Sets the right child of the child node to null
        }
        else
        {
            insert(current->left, key_value,name_value, headPackage_value, dependencyFlag);
            
        }
    }
    else if(key_value>=current->key)
    {
        if(current->right==NULL){
            current->right=new tree_node;
            current->right->key=key_value;
            current->right->name=name_value;
            current->right->isDependency=dependencyFlag;
            current->right->headPackage=headPackage_value;
            current->right->left=NULL;
            current->right->right=NULL; //Sets the right child of the child node to null
        }
        else
        {
            insert(current->right, key_value,name_value, headPackage_value, dependencyFlag);

        }
    }
}


void binary_tree::remove(unsigned long key_value ){
    remove(root,key_value);
}



void binary_tree::remove(tree_node * & current, unsigned long key_value ){
    
    tree_node * temp_ptr;
    tree_node * old_node;

    if ( current == NULL )
        return; // the item was not found
    else if ( key_value < current->key )
        remove( current->left, key_value );
    else if ( key_value > current->key )
        remove( current->right, key_value );
    else {
        // item is equal to the item in the node; it is found
        // Check how many children it has
        if ( current->left != NULL && current->right != NULL ) {
            // It has two children. We need to replace it by the
            // smallest item in the right subtree. Assume there
            // is a function, find_min() that returns a pointer
            // to the smallest item in a tree.
            // get the pointer to the smallest item in right subtree
            temp_ptr = find_min( current->right );
            // Copy the item into the current node
            current->key = temp_ptr->key;
            current->name = temp_ptr->name;
            current->isDependency = temp_ptr->isDependency;
            current->headPackage = temp_ptr->headPackage;
            // Recursively call delete to delete the item that was just
            // copied. It is in the right subtree.
            remove( current->right, current->key );
        }
        else {
            // The current node has at most one child. Copy the value of
            // current temporarily
            old_node = current;
            // If the left child is not empty, then make the left child the
            // child of the parent of current. By assigning to current this
            // achieves that.
            // If the left child is empty, then either the right is empty or it is not
            // In either case we can set current to point to its right child.
            if ( current->left != NULL )
                current = current->left;
                else
                    current = current->right;
                    // Delete the node that current used to point to
                    delete old_node;
        }
    }
}

tree_node * binary_tree::find_min( tree_node *current )
{
    if ( current == NULL )
        return NULL;
    if ( current->left == NULL )
        return current;
    return find_min( current->left );
}

bool binary_tree::getDependencyFlag(unsigned long key_value){
    if (search(key_value) == NULL)
            {
            throw 0;
        }
    tree_node *tmp = search(root,key_value);
    return tmp->isDependency;
}

std::string binary_tree::getHeadPack(unsigned long key_value){
    if (search(key_value) == NULL)
    {
        throw 0;
    }
    tree_node *tmp = search(root,key_value);
    return tmp->headPackage;
}
