#include <iostream>
#include <vector>
#include "../BinaryTree/BinaryTree.h"
#include "../LinkedList/ArrayLinkedList.h"

using Iterator = BinaryTree<int>::Iterator;
using Type = BinaryTree<int>::Type;


BinaryTree<int> vectorToBinaryTree(const std::vector<int>& vector);

class BST
{
    public:
        BST();
        BST(int vRoot);
        ~BST();

        /* stabilisce se l’albero binario rispetta i vincoli di un BST */
        bool is_bst();

        /* inserisce in modo ordinato nel BST il valore passato */
        void insert(int nodeValue);

        /* verifica se un elemento appartiene al BST */
        bool search(int needle);

        bool isNodeEmpty(Iterator node);
        void link(Iterator parent, Iterator child, Type childValue);
        void updateLevels(Iterator startingNode, uint32_t initLevel);

        Iterator min(Iterator start);

        bool isLeftEmpty(Iterator leftChild);
        bool isRightEmpty(Iterator rightChild);
        Iterator successor(Iterator node);

        void getInorderList(Iterator start, ArrayLinkedList<int> list);


    private:
        BinaryTree<int>* T;
};


BST::BST()
{
    this->T = new BinaryTree<int>();
}


BST::BST(int vRoot)
{
    this->T = new BinaryTree<int>(vRoot);
}


BST::~BST()
{
    this->T->~BinaryTree();
}



void BST::insert(int nodeValue)
{
    Iterator parent = nullptr;
    Iterator iter = this->T->getRoot();

    if (this->T->getRoot() == nullptr)
    {
        this->T = new BinaryTree<int>(nodeValue);
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

    Iterator child = new BinaryTreeNode<int>(nodeValue);
    this->link(parent, child, nodeValue);
    this->updateLevels(child, parent->getNodeLevel());

    if ((child->getNodeLevel() > parent->getNodeLevel()) && (this->T->getHeight() != child->getNodeLevel()))
    {
        Iterator root = this->T->getRoot();
        this->T->setHeight(this->T->calculateMaxLevel(root));
    }
}

bool BST::search(int needle)
{
    Iterator it = this->T->getRoot();

    while (!this->isNodeEmpty(it) && it->getNodeValue() != needle)
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

    return !this->isNodeEmpty(it);
}


bool BST::is_bst()
{
    int minV;
    ArrayLinkedList<int> inorderList;
    this->getInorderList(T->getRoot(), inorderList);

    if (inorderList.getSize() == 1)
    {
        return true;
    }

    // Se la lista non e' in ordine crescente allora non e' un bst.
    for (int i = 1; i < inorderList.getSize(); i++)
    {
        if (inorderList[i] < inorderList[i - 1])
        {
            return false;
        }
    }

    return true;
}



/**
 * Restituisce una lista contenente i nodi attraversati secondo la logica "simmetrica"
 *
 * @param start : Radice albero o sottoalbero
 * @param list : Lista contentente i nodi visitati in maniera "simmetrica"
 */
void BST::getInorderList(Iterator start, ArrayLinkedList<int> list)
{
    if (start)
    {
        this->getInorderList(start->getNodeLeftChild(), list);
        list.append(start->getNodeValue());
        this->getInorderList(start->getNodeRightChild(), list);
    }
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

 * @param node: Nodo a cui trovare il successore
 * @return Puntatore al predecessore di node.
 */
Iterator BST::successor(Iterator node)
{
    if (this->isNodeEmpty(node))
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
 * Restituisce il puntatore al nodo con valore minimo
 * contenuto nell'albero o sottoalbero con radice start.
 *
 * @param start: Radice dell'albero o sottoalbero
 * @return Puntatore al nodo con valore minimo
 */
Iterator BST::min(Iterator start)
{
    Iterator it = start;

    while (!this->isLeftEmpty(it))
    {
        it = it->getNodeLeftChild();
    }

    return it;
}


/**
 * Restituisce true se il figlio sinistro di leftChild e' vuoto, altrimenti false.
 * In caso leftChild sia vuoto, viene restituito true
 *
 * @param leftChild: Puntatore al nodo a cui controllare il figlio sinistro
 * @return True se il figlio sinistro di leftChild, o se leftChild, e' vuoto,
 * altrimenti false
 */
bool BST::isLeftEmpty(Iterator leftChild)
{
    if (this->isNodeEmpty(leftChild))
    {
        return true;
    }

    return this->isNodeEmpty(leftChild->getNodeLeftChild());
}


/**
 * Restituisce true se il figlio destro di rightChild e' vuoto, altrimenti false.
 * In caso rightChild sia vuoto, viene restituito true
 *
 * @param rightChild: Puntatore al nodo a cui controllare il figlio destro
 * @return True se il figlio destro di rightChild, o se rightChild, e' vuoto,
 * altrimenti false
 */
bool BST::isRightEmpty(Iterator rightChild)
{
    if (this->isNodeEmpty(rightChild))
    {
        return true;
    }

    return this->isNodeEmpty(rightChild->getNodeRightChild());
}


/**
 * Permette di collegare un nodo padre parent, ad un nodo figlio child e, a seconda del valore
 * contenuto in childValue, child diventera' figlio destro o sinistro di parent.
 *
 * La scelta viene fatta confrontando il valore contenuto in parent con il valore di childValue
 *
 * @param parent: Puntatore al padre
 * @param child: Puntatore del figlio da collegare a parent
 * @param childValue: Valore di child
 */
void BST::link(Iterator parent, Iterator child, Type childValue)
{
    if (!isNodeEmpty(child))
    {
        child->setNodeParent(parent);
    }

    if (!isNodeEmpty(parent))
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
 * @param startingNode: Radice di un sottoalbero a cui aggiornare i livelli a tutti
 * i suoi figli
 * @param initLevel: Livello di partenza
 */
void BST::updateLevels(Iterator startingNode, uint32_t initLevel)
{
    if (!this->isNodeEmpty(startingNode))
    {
        startingNode->setNodeLevel(initLevel + 1);
        this->updateLevels(startingNode->getNodeLeftChild(), startingNode->getNodeLevel());
        this->updateLevels(startingNode->getNodeRightChild(), startingNode->getNodeLevel());
    }
}


/**
 * Verifica se un nodo e' vuoto, restituendo true altrimenti false.
 *
 * @param node: Puntatore al nodo da controllare
 * @return True se e' vuoto, altrimenti false
 */
bool BST::isNodeEmpty(Iterator node)
{
    return (node == nullptr);
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