# aPackageIndexer

##Concept:

Use a binary tree container to hold "package nodes" 
reason: fast searching

Packages and dependencies are both considered "tree_nodes"
the only difference is a dependency has a flag that indicates a package is dependent on it 
and dependencies store the name of the package that is dependent on it

Package names are hashed into numbers "keys" and set as the key_vale of the "tree_node"

###Indexing:
If there are dependencies they are indexed first before the package that is dependent on it is indexed 
that package is called the "head package"

###Query 
Hash the package name and search the try with key

###Removal:
Two variables assist with removal:

```
"isDependent" tells us of the package is a dependency and 
"headPackage" tells us which package was dependent on it 
```

This way a package need not keep track of all its dependencies instead
"REMOVE" checks if the packages still exist, 
if it does it checks if is a dependency and 
	if it is, "REMOVE" checks if dependent package still exist
otherwise the package can be removed 
