cmake_minimum_required(VERSION 3.0.0)
project(structures VERSION 0.1.0)


include(CTest)
enable_testing()

add_executable(structures tester.cpp
    ./LinkedList/LinkedList.h ./LinkedList/ILinkedList.h
    ./SortedLinkedList/SortedLinkedList.h ./SortedLinkedList/ISortedLinkedList.h
    ./Stack/Stack.h ./Stack/IStack.h ./Stack/ArrayStack.h   
    ./Queue/Queue.h ./Queue/IQueue.h ./Queue/ArrayQueue.h   
    ./Set/ISet.h ./Set/Set.h
    ./BinaryTree/IBinaryTree.h ./BinaryTree/BinaryTree.h
    ./BST/BinarySearchTree.h LinkedList/ArrayLinkedList.h PriorityQueue/PriorityQueue.h PriorityQueue/IPriorityQueue.h Dictionary/Dictionary.h Dictionary/IDictionary.h Graph/IGraph.h Graph/Graph.h Tree/Tree.h Tree/ITree.h Lib/random.h soluzioni-tracce-esami/even_father.h soluzioni-tracce-esami/eo_strings.h soluzioni-tracce-esami/zero_one_binary_tree.h BST/IBinarySearchTree.h soluzioni-tracce-esami/bst.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
