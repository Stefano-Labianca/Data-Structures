cmake_minimum_required(VERSION 3.0.0)
project(structures VERSION 0.1.0)


include(CTest)
enable_testing()

add_executable(structures tester.cpp
    ./LinkedList/LinkedList.h ./LinkedList/ILinkedList.h
    ./Stack/Stack.h ./Stack/IStack.h ./Stack/ArrayStack.h   
    ./Queue/Queue.h ./Queue/IQueue.h ./Queue/ArrayQueue.h   
    ./Set/ISet.h ./Set/Set.h
    ./BinaryTree/IBinaryTree.h ./BinaryTree/BinaryTree.h
    ./BST/BinarySearchTree.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
