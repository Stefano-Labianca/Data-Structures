
#include <iostream>
#include "BinaryTree/BinaryTree.h"

int main(int argc, char const *argv[])
{
//    BinaryTree<int> bTree;
    BinaryTree<int> bTree;

    bTree.addLeftChild(10);
    bTree.addLeftChild(23);
    bTree.addRightChild(41);

    bTree.addLeftChild(bTree._root->_leftChild, 1);
    bTree.addRightChild(bTree._root->_leftChild, 100);

    bTree.addRightChild(bTree._root->_rightChild, 40);


    bTree.leverOrderTraversal(bTree._root);

    return 0;
}
