//
//  main.cpp
//  Binary Package Tree
//
//  Copyright (c) 2017 Dustin Shasho. All rights reserved.
//

#include <iostream>
#include "package-Btree.h"

int main(int argc, const char * argv[]) {
    binary_tree tree;
    
    tree.insert(1000, "first", "head", 1);
    tree.insert(2000, "first", "head", 1);
    tree.insert(1500, "first", "head", 1);
    tree.insert(3000, "first", "head", 1);
    tree.remove(1000);
    tree.search(1000);
    tree.search(2000);
    
    try {
        std:: cout << tree.getDependencyFlag(1500);
    }
    catch( int r){
        std::cout << "searching for dead package";
    }
    
    try {
        std:: cout << tree.getHeadPack(1500);
    }
    catch( int r){
        std::cout << "searching for dead package";
    }
    
    return 0;
}
