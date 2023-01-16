#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include "../BinaryTree/BinaryTree.h"
#include "IBinarySearchTree.h"

/**
 * Implementazione di un albero binario di ricerca.
 *
 * @tparam T: Tipo di dato da salvare
 */
template <class T>
class BinarySearchTree : public IBinarySearchTree<T, BinaryTreeNode<T>*>
{
    public:
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Iterator Iterator;
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Type Type;

    private:
        void _link(Iterator parent, Iterator child, Type childValue);
        void _updateLevels(Iterator startingNode, uint32_t initLevel);
        bool _isNodeEmpty(Iterator node);
        void _decreaseLevel(Iterator root, uint32_t decrementFactor);

    private:
        BinaryTree<T>* _bTree; // Radice dell'albero di ricerca binario

    public:
        BinarySearchTree();
        BinarySearchTree(Type rootValue);
        ~BinarySearchTree();

        void insert(Type nodeValue);
        void remove(Type needle);
        Iterator lookup(Type needle);

        Iterator successor(Iterator node);
        Iterator predecessor(Iterator node);

        Iterator min(Iterator start);
        Iterator max(Iterator start);

        Iterator getRoot();
        BinarySearchTree<T>* subTree(Iterator root);

        bool isLeftEmpty(Iterator leftChild);
        bool isRightEmpty(Iterator rightChild);

        bool isEmpty();
        void travers();
};

/**
 * Costruttore della classe. Crea un albero binario di ricerca vuoto
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 */
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    this->_bTree = new BinaryTree<T>();
};

/**
 * Costruttore della classe. Crea un albero binario di ricerca con
 * la radice con valore rootValue.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param rootValue: Valore della radice
 */
template <class T>
BinarySearchTree<T>::BinarySearchTree(Type rootValue)
{
    this->_bTree = new BinaryTree<T>(rootValue);
}

/**
 * Restituisce il puntatore alla radice dell'albero
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @return Puntatore della radice dell'albero
 */
template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::getRoot()
{
    return this->_bTree->getRoot();
}

/**
 * Distruttore della classe.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 */
template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    this->_bTree->~BinaryTree();
}


/**
 * Inserisce un nuovo nodo, con valore nodeValue, all'interno
 * dell'albero binario di ricerca.
 * Se e' gia' presente un nodo con lo stesso valore di nodeValue, allora
 * non viene inserito.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param nodeValue: Valore del nuovo nodo da inserire
 */
template <class T>
void BinarySearchTree<T>::insert(Type nodeValue)
{
    Iterator parent = nullptr;
    Iterator iter = this->_bTree->getRoot();

    if (this->_bTree->getRoot() == nullptr)
    {
        this->_bTree = new BinaryTree<T>(nodeValue);
        return;
    }

    while (iter)
    {
        parent = iter;

        if (iter->getNodeValue() == nodeValue)
        {
            return;
        }

        if (nodeValue < iter->getNodeValue())
        {
            iter = iter->getNodeLeftChild();
        }

        else if (nodeValue > iter->getNodeValue())
        {
            iter = iter->getNodeRightChild();
        }
    }

    Iterator child = new BinaryTreeNode<T>(nodeValue);
    this->_link(parent, child, nodeValue);
    this->_updateLevels(child, parent->getNodeLevel());

    if ((child->getNodeLevel() > parent->getNodeLevel()) && (this->_bTree->getHeight() != child->getNodeLevel()))
    {
        Iterator root = this->_bTree->getRoot();
        this->_bTree->setHeight(this->_bTree->calculateMaxLevel(root));
    }
}

/**
 * Ricerca e restituisce un puntatore al nodo con valore needle.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param needle: Valore del nodo da cercare
 * @return Puntatore al nodo con valore needle
 */
template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::lookup(Type needle)
{
    Iterator it = this->_bTree->getRoot();

    while (!this->_isNodeEmpty(it) && it->getNodeValue() != needle)
    {
        if (needle < it->getNodeValue())
        {
            it = it->getNodeLeftChild();
        }

        else if (needle > it->getNodeValue())
        {
            it = it->getNodeRightChild();
        }
    }

    return it;
}


/**
 * Rimuove un nodo contenente il valore needle
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param needle: Valore del nodo da rimuovere
 */
template <class T>
void BinarySearchTree<T>::remove(Type needle)
{
    Iterator node = this->lookup(needle);

    if (!this->_isNodeEmpty(node))
    {
        if (!this->isLeftEmpty(node) && !this->isRightEmpty(node))
        {
            Iterator it = node->getNodeRightChild();

            while (!this->isLeftEmpty(it))
            {
                it = it->getNodeLeftChild();
            }

            node->setNodeValue(it->getNodeValue());
            node = it;
        }

        Iterator newChild;

        if (!this->isLeftEmpty(node) && this->isRightEmpty(node))
        {
            newChild = node->getNodeLeftChild();
        }

        else
        {
            newChild = node->getNodeRightChild();
        }

        this->_link(node->getNodeParent(), newChild, needle);
        uint32_t newH = this->_bTree->calculateMaxLevel(this->_bTree->getRoot());
        this->_bTree->setHeight(newH);

        delete node;
        node = nullptr;
    }
}


/**
 * Restituisce il puntatore al nodo con valore minimo
 * contenuto nell'albero o sottoalbero con radice start.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param start: Radice dell'albero o sottoalbero
 * @return Puntatore al nodo con valore minimo
 */
template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::min(Iterator start)
{
    Iterator it = start;

    while (!this->isLeftEmpty(it))
    {
        it = it->getNodeLeftChild();
    }

    return it;
}

/**
 * Restituisce il puntatore al nodo con valore massimo
 * contenuto nell'albero o sottoalbero con radice start.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param start: Radice dell'albero o sottoalbero
 * @return Puntatore al nodo con valore massimo
 */
template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::max(Iterator start)
{
    Iterator it = start;

    while (!this->isRightEmpty(it))
    {
        it = it->getNodeRightChild();
    }

    return it;
}


/**
 * Restituisce il puntatore del nodo successivo a node.
 * Ovvero il nodo la cui chiave segue immediatamente dopo quella di node, in base
 * all'ordinamento scelto
 *
 * Esempio:
 *  node.value = 40;
 *  succ.value = 42;
 *
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param node: Nodo a cui trovare il successore
 * @return Puntatore al predecessore di node.
 */
template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::successor(Iterator node)
{
    if (this->_isNodeEmpty(node))
    {
        return node;
    }

    if (!this->isRightEmpty(node))
    {
        return this->min(node->getNodeRightChild());
    }

    Iterator it = node->getNodeParent();

    while (it && node == it->getNodeRightChild())
    {
        node = it;
        it = it->getNodeParent();
    }

    return it;
}


/**
 * Restituisce il puntatore del nodo precedente a node.
 * Ovvero il nodo la cui chiave precede immediatamente prima quella di node, in base
 * all'ordinamento scelto
 *
 * Esempio:
 *  node.value = 40;
 *  succ.value = 37;
 *
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param node: Nodo a cui trovare il predecessore
 * @return Puntatore al predecessore di node.
 */
template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::predecessor(Iterator node)
{
    if (this->_isNodeEmpty(node))
    {
        return node;
    }

    if (!this->isLeftEmpty(node))
    {
        return this->max(node->getNodeLeftChild());
    }

    Iterator it = node->getNodeParent();

    while (it && node == it->getNodeLeftChild())
    {
        node = it;
        it = it->getNodeParent();
    }

    return it;
}

/**
 * Restituisce true se l'albero e' vuoto, altrimenti false.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @return True se l'albero e' vuoto, altrimenti false.
 */
template <class T>
bool BinarySearchTree<T>::isEmpty()
{
    return (this->_bTree->getRoot() == nullptr);
}


/**
 * Restituisce true se il figlio sinistro di leftChild e' vuoto, altrimenti false.
 * In caso leftChild sia vuoto, viene restituito true
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param leftChild: Puntatore al nodo a cui controllare il figlio sinistro
 * @return True se il figlio sinistro di leftChild, o se leftChild, e' vuoto,
 * altrimenti false
 */
template <class T>
bool BinarySearchTree<T>::isLeftEmpty(Iterator leftChild)
{
    if (this->_isNodeEmpty(leftChild))
    {
        return true;
    }

    return this->_isNodeEmpty(leftChild->getNodeLeftChild());
}

/**
 * Restituisce true se il figlio destro di rightChild e' vuoto, altrimenti false.
 * In caso rightChild sia vuoto, viene restituito true
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param rightChild: Puntatore al nodo a cui controllare il figlio destro
 * @return True se il figlio destro di rightChild, o se rightChild, e' vuoto,
 * altrimenti false
 */
template <class T>
bool BinarySearchTree<T>::isRightEmpty(Iterator rightChild)
{
    if (this->_isNodeEmpty(rightChild))
    {
        return true;
    }

    return this->_isNodeEmpty(rightChild->getNodeRightChild());
}

/**
 * Mostra tutti i valori contenuti nell'albero seguendo l'ordinamento
 * per chiave (dal piu' piccolo al piu' grande)
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 */
template <class T>
void BinarySearchTree<T>::travers()
{
    Iterator it = this->min(this->_bTree->getRoot());

    while (!this->_isNodeEmpty(it))
    {
        std::cout << it->getNodeValue() << " ";
        it = this->successor(it);
    }
}


/**
 * Restituisce un sottoalbero di root.
 * Se root e' la radice, viene restituito il puntatore
 * dell'intero albero
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Puntatore della radice del sottoalbero da prelevare
 * @return Puntatore alla radice del sottoalbero
 */
template <class T>
BinarySearchTree<T>* BinarySearchTree<T>::subTree(Iterator root)
{
    if (root == this->_bTree->getRoot())
    {
        return this;
    }

    BinarySearchTree<T>* subT = new BinarySearchTree<T>();
    Iterator subRoot = new BinaryTreeNode<T>(root->getNodeValue());

    subRoot->setNodeRightChild(root->getNodeRightChild());
    subRoot->setNodeLeftChild(root->getNodeLeftChild());

    subT->_bTree->setRoot(subRoot);
    this->_decreaseLevel(subRoot, root->getNodeLevel());

    uint32_t newH = this->_bTree->calculateMaxLevel(subRoot);
    subT->_bTree->setHeight(newH);

    return subT;
}


/**
 * Permette di collegare un nodo padre parent, ad un nodo figlio child e, a seconda del valore
 * contenuto in childValue, child diventera' figlio destro o sinistro di parent.
 *
 * La scelta viene fatta confrontando il valore contenuto in parent con il valore di childValue
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param parent: Puntatore al padre
 * @param child: Puntatore del figlio da collegare a parent
 * @param childValue: Valore di child
 */
template <class T>
void BinarySearchTree<T>::_link(Iterator parent, Iterator child, Type childValue)
{
    if (!this->_isNodeEmpty(child))
    {
        child->setNodeParent(parent);
    }

    if (!this->_isNodeEmpty(parent))
    {
        if (childValue < parent->getNodeValue())
        {
            parent->setNodeLeftChild(child);
        }

        else
        {
            parent->setNodeRightChild(child);
        }
    }

}

/**
 * Aggiorna tutti i livelli dei figli di startingNode partendo dal suo livello initLevel.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param startingNode: Radice di un sottoalbero a cui aggiornare i livelli a tutti
 * i suoi figli
 * @param initLevel: Livello di partenza
 */
template <class T>
void BinarySearchTree<T>::_updateLevels(Iterator startingNode, uint32_t initLevel)
{
    if (!this->_isNodeEmpty(startingNode))
    {
        startingNode->setNodeLevel(initLevel + 1);
        this->_updateLevels(startingNode->getNodeLeftChild(), startingNode->getNodeLevel());
        this->_updateLevels(startingNode->getNodeRightChild(), startingNode->getNodeLevel());
    }
}


/**
 * Verifica se un nodo e' vuoto, restituendo true altrimenti false.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param node: Puntatore al nodo da controllare
 * @return True se e' vuoto, altrimenti false
 */
template <class T>
bool BinarySearchTree<T>::_isNodeEmpty(Iterator node)
{
    return (node == nullptr);
}


/**
 * Decremente tutti i livelli dei figli di root di un fattore pari a decrementFactor.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Nodo della radice o del sottoalbero
 * @param decrementFactor: Numero di livelli da togliere a tutti i figli di root
 */
template <class T>
void BinarySearchTree<T>::_decreaseLevel(Iterator root, uint32_t decrementFactor)
{
    if (!this->_isNodeEmpty(root))
    {
        if (root->_level > 0)
        {
            root->_level -= decrementFactor;
        }

        this->_decreaseLevel(root->getNodeLeftChild(), decrementFactor);
        this->_decreaseLevel(root->getNodeRightChild(), decrementFactor);
    }
}


#endif // _BINARYSEARCHTREE_H
