#include "../Tree/Tree.h"

template <class T>
int even_father(const Tree<T>& tree, typename Tree<T>::Iterator root);


template <class T>
int even_father(const Tree<T>& tree, typename Tree<T>::Iterator root)
{
    uint32_t i = 1;
    int counter = 0;

    if (root == nullptr)
    {
        return 0;
    }

    uint32_t k = 0;

    if (tree.getParent(root))
    {
        if (tree.getParent(root)->getValue() % 2 == 0)
        {
            counter++;
        }
    }

    typename Tree<T>::Iterator it = tree.getFirstChild(root);

    // Attuo l'ordine simmetrico sui primi i figli di root
    while (it && k < i)
    {
        k++;
        counter += even_father(tree, it);
        it = tree.getNextSibling(it);
    }

    // Attuo l'ordine simmetrico sui successivi i + 1 figli di root
    while (it)
    {
        counter += even_father(tree, it);
        it = tree.getNextSibling(it);
    }

    return counter;
}
