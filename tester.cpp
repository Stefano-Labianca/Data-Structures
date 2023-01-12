#include "Tree/Tree.h"

int main(int argc, char const *argv[])
{
    Tree<int> tree(2);

    tree.insertSibling(tree.getRoot(), 5);
    tree.insertSibling(tree.getRoot(), 6);

    Tree<int>::Iterator s = tree.getFirstChild(tree.getRoot());
    Tree<int>::Iterator t = tree.getNextSibling(s);

    tree.insertFirstChild(s, 30);
    tree.insertFirstChild(s, 20);

    tree.insertFirstChild(t, 7);

    std::cout << tree.nodesPerLevel(1);

    return 0;
}
