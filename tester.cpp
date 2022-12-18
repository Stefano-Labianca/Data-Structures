
#include <iostream>
#include "BinaryTree/BinaryTree.h"

int main(int argc, char const *argv[])
{
    BinaryTree<int> fTree(1);
    BinaryTree<int> sTree(100);

    BinaryTreeNode<int>* sNode;

    sTree.addLeftChild(200);
    sTree.addRightChild(300);

    sTree.addRightChild(sTree.getRoot()->getNodeLeftChild(), 400);
    sTree.addLeftChild(sTree.getRoot()->getNodeRightChild(), 500);

    sTree.addLeftChild(sTree.getRoot()->getNodeRightChild()->getNodeLeftChild(), 600);
    sTree.addRightChild(sTree.getRoot()->getNodeRightChild()->getNodeLeftChild(), 700);

    fTree.addLeftChild(2);
    fTree.addRightChild(3);
    fTree.addRightChild(fTree.getRoot()->getNodeLeftChild(), 4);


    return 0;
}
