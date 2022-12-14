
#include <iostream>
#include "BinaryTree/BinaryTree.h"

int main(int argc, char const *argv[])
{
//    BinaryTree<int> bTree;
    BinaryTree<int> bTree(1);
    BinaryTree<int> sTree(10);

    BinaryTree<int>::Iterator node = new BinaryTreeNode<int>(2);

    bTree.addLeftChild(node, bTree.getRoot());
    bTree.addRightChild(5);

    bTree.addRightChild(3);
    bTree.addRightChild(7);

    sTree.addLeftChild(8);
    sTree.addLeftChild(6);
    sTree.addRightChild(30);

    bTree.addLeftChild(sTree.getRoot(), node);


    std::cout << "Altezza: " << bTree.getHeight() << std::endl;
    std::cout << "Numero di nodi: " << bTree.calculateNodesAmount() << std::endl;
    std::cout << "Altezza Massima: " << bTree.calculateMaxLevel(bTree.getRoot(), bTree.getRoot()->getNodeLevel()) << std::endl;

    bTree.levelOrderTraversal(bTree.getRoot());

    return 0;
}
