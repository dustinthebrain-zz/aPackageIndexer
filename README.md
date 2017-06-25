# aPackageIndexer

## Concept

Use a binary tree container to hold "package nodes" 
reason: fast searching

Packages and dependencies are both considered "tree_nodes"
the only difference is a dependency has a flag that indicates a package is dependent on it 
and dependencies store the name of the package that is dependent on it

Package names are hashed into numbers "keys" and set as the key_vale of the "tree_node"

### Indexing
If there are dependencies they are indexed first before the package that is dependent on it is indexed 
that package is called the "head package"

### Query 
Hash the package name and search the try with key

### Removal
Two variables assist with removal:

```
"isDependent" tells us if the package is a dependency and 
"headPackage" tells us which package was dependent on it 
```

This way a package need not keep track of all its dependencies, instead
a dependency knows if a package is depending on it by a flag and what the name of the package is

"REMOVE" checks if the packages still exist, 
if it does it checks if is a dependency and 
	if it is, "REMOVE" checks if the package depending on it still exist
otherwise the package can be removed 

# INSTALL, RUN & TEST

## Install 
you will need: GCC env > 4.9d
and the program is compiled with c++11

## build
`g++ -std=c++11 main.cpp package-Btree.cpp -o PTREE`
## run
`./PTREE`
## interface
	telnet from as multiple terminals and send messages 
`telnet 127.0.0.1 8080`

## test
_Here is a sample of the program working as I think it should_

I’m not sure why the provided test is not able to see removal, it is possible I have misunderstood the instructions and am not sending the correct command, one thing that did not make sense was sending OK if a package was removed but was not found.

The debug command did not provide me any extra info.

```
root@compute-test:~# telnet 127.0.0.1 8080
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
INDEX|cloog|gmp,isl,pkg-config
OK
REMOVE|ceylon|
OK
REMOVE|gmp|
FAIL
REMOVE|cloog|
OK
QUERY|cloog|
FAIL
REMOVE|gmp|
OK
REMOVE|isl|
OK
REMOVE|pkg-config|
OK
QUERY|gmp|
FAIL
QUERY|isl|
FAIL
QUERY|pkg-config|
FAIL
QUERY|cloog|
FAIL
REMOVE|pkg-config|
OK
^]
telnet> q
Connection closed.
root@compute-test:~# 
```


