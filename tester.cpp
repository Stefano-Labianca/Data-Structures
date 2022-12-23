
#include <iostream>
#include "BST/BinarySearchTree.h"

int main(int argc, char const *argv[])
{
    BinaryTree<int> binaryTree(1);

    binaryTree.addLeftChild(2);
    binaryTree.addRightChild(3);

    BinaryTree<int>::Iterator it = binaryTree.getRoot()->getNodeRightChild();

    binaryTree.addLeftChild(it, 4);
    binaryTree.addRightChild(it, 7);

    BinaryTree<int>::Iterator itS = it->getNodeLeftChild();

    binaryTree.addRightChild(itS, 5);

    BinaryTree<int>* sub = binaryTree.subTree(it);
    sub->levelOrderTraversal(sub->getRoot());

    return 0;
}
