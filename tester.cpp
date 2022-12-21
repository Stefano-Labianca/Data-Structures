
#include <iostream>
#include "BST/BinarySearchTree.h"

int main(int argc, char const *argv[])
{
    BinarySearchTree<int> bSearch;

    bSearch.insert(17);
    bSearch.insert(7);
    bSearch.insert(33);
    bSearch.insert(40);
    bSearch.insert(42);
    bSearch.insert(37);
    bSearch.insert(21);
    bSearch.insert(27);
    bSearch.insert(7);
    bSearch.insert(8);
    bSearch.insert(13);
    bSearch.insert(1);
    bSearch.insert(5);

    bSearch.remove(33);

    BinarySearchTree<int>::Iterator s = bSearch.getRoot();

    std::cout << bSearch.successor(s)->getNodeValue() << std::endl;

    BinarySearchTree<int>* sub;

    sub = bSearch.subTree(bSearch.getRoot()->getNodeRightChild());
    sub->travers();



    return 0;
}
