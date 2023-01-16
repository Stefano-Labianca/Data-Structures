#include "soluzioni-tracce-esami/bst.h"
//#include "Graph/Graph.h"


int main(int argc, char const *argv[])
{
    BST b;

    b.insert(1);
    b.insert(4);
    b.insert(5);
    b.insert(7);
    b.insert(4);

    std::cout << b.is_bst();

    return 0;
}
