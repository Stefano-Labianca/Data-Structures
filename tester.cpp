
#include <iostream>
//#include "BST/BinarySearchTree.h"
#include "LinkedList/LinkedList.h"

int main(int argc, char const *argv[])
{
    LinkedList<int> list;

    list.append(1);
    list.append(3);

    LinkedList<int> list1;

    list1.append(1);

    std::cout << (list == list1) << std::endl;
    std::cout << (list1 != list);

    return 0;
}
