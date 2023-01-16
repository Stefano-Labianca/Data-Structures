#include <iostream>

#include "../BinaryTree/BinaryTree.h"
#include "../LinkedList/ArrayLinkedList.h"

#include <vector>

using Iterator = BinaryTree<int>::Iterator;

bool hasTwoChild(Iterator root);
bool zeroOneStruct(Iterator root);
bool oneZeroStruct(Iterator root);
bool isLeaf(Iterator node);

bool check(Iterator root);

BinaryTree<int> vectorToBinaryTree(const std::vector<int>& vector);

template <class T>
class zero_one_binary_tree
{
    public:
        /** Stabilisce se l’albero rispetta le propieta' di un albero zero-one, ovvero:
        *   1) la radice ha valore 0;
        *   2) ogni nodo 0, ha come figli due nodi 1;
        *   3) ogni nodo 1, ha come figli due nodi 0.
        */
        bool is_zero_one(const BinaryTree<T> &B);

        /* Restituisce il numero di nodi 0 dell’abero */
        int zero_nodes(const BinaryTree<T> &B);
};

template <class T>
bool zero_one_binary_tree<T>::is_zero_one(const BinaryTree<T> &B)
{
    if (B.getRoot()->getNodeValue() == 1)
    {
        return false;
    }

    return check(B.getRoot());
}

/**
 * Restituisce true se l'albero in esame e'un zero_one, altrimenti
 * restituisce false.
 *
 * @param root: Radice dell'albero o sottoalbero
 * @return True se ho un albero zero_one, altrimenti false.
 */
bool check(Iterator root)
{
    bool res = false;

    /**
     * Visito in postvisita l'albero con radice root e controllo se ogni nodo, diverso dalla
     * foglia, rispetta delle condizioni.
     *
     *  1. La radice deve avere valore 0
     *  2. Se il genitore ha 1, allora i suoi figli devono avere entrambi 0
     *  3. Se il genitore ha 0, allora i suoi figli devono avere entrambi 1
     *  4. Se un nodo non ha due figli, allora non abbiamo un albero zero_one
     */

    if (root)
    {
        res = check(root->getNodeLeftChild());
        res = res && check(root->getNodeRightChild());


        // --- Radice dell'albero ---

        if (root->getNodeParent() == nullptr && root->getNodeValue() == 0)
        {
            /**
             * Dato che e' l'ultima ad essere analizzata nella postvisita
             * restituisco il risultato finale
             */
            return res;
        }

        // --- Restanti nodi ---

        if (isLeaf(root)) // Sono ad un nodo foglia
        {
            return true;
        }

        // Quando la prima condizione diventa false, allora bisogna
        // bloccare tutta la catena ricorsiva

        if (!hasTwoChild(root)) // Non ho due figli in root
        {
            return false;
        }

        if (root->getNodeValue() == 1)
        {
            return oneZeroStruct(root);
        }

        return zeroOneStruct(root);
    }

    return true;
}


template <class T>
int zero_one_binary_tree<T>::zero_nodes(const BinaryTree<T> &B)
{
    Queue<Iterator> queue;

    queue.enqueue(B.getRoot());
    uint32_t amount = 0;

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();

        if (iter->getNodeValue() == 0)
        {
            amount++;
        }


        if (iter->getNodeLeftChild())
        {
            queue.enqueue(iter->getNodeLeftChild());
        }

        if (iter->getNodeRightChild())
        {
            queue.enqueue(iter->getNodeRightChild());
        }
    }

    return amount;
}

/**
 * Converte un vettore in un albero binario
 *
 * @param vector : Vettore contenente i valori dell'albero
 * @return Albero binario contenente i valori di vector
 */
BinaryTree<int> vectorToBinaryTree(const std::vector<int>& vector)
{
    BinaryTree<int> bTree(vector[0]);
    ArrayLinkedList<Iterator> nodeList(vector.size());

    Iterator current = bTree.getRoot();
    nodeList.append(current);

    for (int i = 0; i < vector.size(); i++)
    {
        bool isUpdated = false;

        if ((2 * i + 1) < vector.size())
        {
            int left = vector[2 * i + 1];
            bTree.addLeftChild(current, left);

            nodeList.append(current->getNodeLeftChild());
            isUpdated = true;
        }

        if ((2 * i + 2) < vector.size())
        {
            int right = vector[2 * i + 2];
            bTree.addRightChild(current, right);

            nodeList.append(current->getNodeRightChild());
            isUpdated = true;
        }

        if (!isUpdated)
        {
            return bTree;
        }

        current = nodeList[i + 1];
    }
}

/**
 * Verifica se un nodo ha esattamente due figli, restituendo true.
 * In caso abbia uno o zero figli, allora restituisce false.
 *
 * @param root : Nodo radice di un albero o sottoalbero
 * @return True se ha due figli, altrimenti false se ne ha meno di due
 */
bool hasTwoChild(Iterator root)
{
    if (root)
    {
        return (root->getNodeLeftChild() != nullptr) && (root->getNodeRightChild() != nullptr);
    }

    return false;
}


/**
 * Resituisce true se root (genitore) ha valore 0
 * ed entrambi i suoi figli hanno valore 1
 *
 * @param root: Genitore da controllare
 * @return True se il genitore ha valore 0 e i suoi figli hanno entrambi
 * valore 1, altrimenti false.
 */
bool zeroOneStruct(Iterator root)
{
    if (root->getNodeValue() == 1) // Il genitore non ha valore 0
    {
        return false;
    }

    if (root->getNodeLeftChild()->getNodeValue() == 0) // Il figlio sinistro non ha valore 1
    {
        return false;
    }

    if (root->getNodeRightChild()->getNodeValue() == 0) // Il figlio destro non ha valore 1
    {
        return false;
    }

    // Il genitore ha valore 0 ed entrambi i suoi figli hanno valore 1

    return true;
}

/**
 * Resituisce true se root (genitore) ha valore 1
 * ed entrambi i suoi figli hanno valore 0
 *
 * @param root: Genitore da controllare
 * @return True se il genitore ha valore 1 e i suoi figli hanno entrambi
 * valore 0, altrimenti false.
 */
bool oneZeroStruct(Iterator root)
{
    if (root->getNodeValue() == 0) // Il genitore non ha valore 1
    {
        return false;
    }

    if (root->getNodeLeftChild()->getNodeValue() == 1) // Il figlio sinistro non ha valore 0
    {
        return false;
    }

    if (root->getNodeRightChild()->getNodeValue() == 1) // Il figlio destro non ha valore 0
    {
        return false;
    }

    // Il genitore ha valore 0 ed entrambi i suoi figli hanno valore 1
    return true;
}


/**
 * Restituisce true se node e' una foglia, altrimenti false
 *
 * @param node: Nodo da controllare
 * @return True se e' una foglia, altrimenti false
 */
bool isLeaf(Iterator node)
{
    return (node->getNodeLeftChild() == nullptr) && (node->getNodeRightChild() == nullptr);
}