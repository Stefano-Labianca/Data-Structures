#ifndef _BINARYTREE_H
#define _BINARYTREE_H


#include "./IBinaryTree.h"
#include "../Queue/Queue.h"

template <class T>
class BinaryTree;

/**
 * Descrive un nodo di un albero binario
 * 
 * @tparam T : Contenuto del nodo
 */
template <class T>
class BinaryTreeNode
{
    friend class BinaryTree<T>;

    private:
        T _value; // Valore del nodo
        BinaryTreeNode<T>* _parent; // Puntatore al genitore
        BinaryTreeNode<T>* _leftChild; // Puntatore al figlio sinistro
        BinaryTreeNode<T>* _rightChild; // Puntatore al figlio destro

        uint32_t _level; // Livello del nodo all'interno dell'albero

    public:
        BinaryTreeNode();
        BinaryTreeNode(T value);
        BinaryTreeNode(T value, uint32_t level, BinaryTreeNode<T>* parent);
        BinaryTreeNode(const BinaryTreeNode<T>& source);

        void setNodeValue(T value);
        void setNodeParent(BinaryTreeNode<T>* parent);
        void setNodeLeftChild(BinaryTreeNode<T>* left);
        void setNodeRightChild(BinaryTreeNode<T>* right);

        T getNodeValue();
        BinaryTreeNode<T>* getNodeParent();
        BinaryTreeNode<T>* getNodeLeftChild();
        BinaryTreeNode<T>* getNodeRightChild();

        uint32_t getNodeLevel();
        void setNodeLevel(uint32_t newLvl);
};

/**
 * Crea un nodo di un albero binario vuoto
 * 
 * @tparam T : Contenuto del nodo
 */
template <class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
    this->_level = 0;
    this->_parent = nullptr;
    this->_leftChild = nullptr;
    this->_rightChild = nullptr;
}

/**
 * Costruttore di un nodo dell'albero binario
 * 
 * @tparam T : Contenuto del nodo
 * @param value : Valore del nodo
 */
template <class T>
BinaryTreeNode<T>::BinaryTreeNode(T value)
{
    this->_value = value;
    this->_level = 0;
    this->_parent = nullptr;
    this->_leftChild = nullptr;
    this->_rightChild = nullptr;
}

/**
 * Costruttore di un nodo dell'albero binario
 * 
 * @tparam T : Contenuto del nodo
 * @param value : Valore del nodo
 * @param level : Livello del nodo
 * @param parent : Puntatore al padre
 */
template <class T>
BinaryTreeNode<T>::BinaryTreeNode(T value, uint32_t level, BinaryTreeNode<T>* parent)
{
    this->_level = level;
    this->_value = value;
    this->_parent = parent;
    this->_leftChild = nullptr;
    this->_rightChild = nullptr;
}

/**
 * Costruttore di copia
 * 
 * @tparam T : Contenuto dell'albero
 * @param source : Nodo da copiare
 */
template <class T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& source)
{
    this->_value = source._value;
    this->_parent = source._parent;
    this->_rightChild = source._rightChild;
    this->_leftChild = source._leftChild;
    this->_level = source._level;
}

/**
 * Restituisce il valore contenuto nel nodo
 * 
 * @tparam T : Contenuto del nodo
 * @return Valore del nodo
 */
template <class T>
T BinaryTreeNode<T>::getNodeValue()
{
    return this->_value;
}

/**
 * Imposta un valore al nodo
 * 
 * @tparam T : Contenuto del nodo
 * @param value : Valore da impostare
 */
template <class T>
void BinaryTreeNode<T>::setNodeValue(T value)
{
    this->_value = value;
}

/**
 * Imposta il genitore del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @param parent : Puntatore del genitore 
 */
template <class T>
void BinaryTreeNode<T>::setNodeParent(BinaryTreeNode<T>* parent)
{
    this->_parent = parent;
}

/**
 * Imposta il figlio sinistro del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @param left : Puntatore del figlio sinistro 
 */
template <class T>
void BinaryTreeNode<T>::setNodeLeftChild(BinaryTreeNode<T>* left)
{
    this->_leftChild = left;
}

/**
 * Imposta il figlio destro del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @param right : Puntatore del figlio destro 
 */
template <class T>
void BinaryTreeNode<T>::setNodeRightChild(BinaryTreeNode<T>* right)
{
    this->_rightChild = right;
}

/**
 * Imposta il livello del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @param newLvl : Nuovo livello del nodo
 */
template <class T>
void BinaryTreeNode<T>::setNodeLevel(uint32_t newLvl)
{
    this->_level = newLvl;
}

/**
 * Restituisce il genitore del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @return Puntatore al genitore
 */
template <class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getNodeParent()
{
    return this->_parent;
}

/**
 * Restituisce il figlio sinistro del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @return Puntatore al figlio  sinistro
 */
template <class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getNodeLeftChild()
{
    return this->_leftChild;
}

/**
 * Restituisce il figlio destro del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @return Puntatore al figlio destro
 */
template <class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getNodeRightChild()
{
    return this->_rightChild;
}

/**
 * Restituisce il livello  del nodo
 * 
 * @tparam T : Contenuto del nodo
 * @return Livello del nodo
 */
template <class T>
uint32_t BinaryTreeNode<T>::getNodeLevel()
{
    return this->_level;
}


// ---------------------------------------------



/**
 * Descrive la struttura dati dell'albero binario
 * 
 ** @tparam T : Tipo di dato contenuto nell'albero
 */
template <class T>
class BinaryTree : public IBinaryTree<T, BinaryTreeNode<T>*>
{
    public:
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Type Type;
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Iterator Iterator;

    private:
        Iterator _root; // Puntatore alla radice dell'albero binario
        uint32_t _height; // Altezza massima dell'albero

    protected:
        bool _isNodeEmpty(Iterator node);
        void _updateHeight();
        void _updateHeight(uint32_t subTreeHeight, uint32_t parentH);
        void _updateLevels(Iterator startingNode, uint32_t initLevel);
        void _erase(Iterator root);
        void _decreaseLevel(Iterator root, uint32_t decrementFactor);

    public:
        BinaryTree();
        BinaryTree(Type rootValue);
        ~BinaryTree();

        void create() {};

        void addLeftChild(Type value);
        void addRightChild(Type value);

        void addLeftChild(Iterator node, Type value);
        void addRightChild(Iterator node, Type value);

        void addLeftChild(Iterator child, Iterator parent);
        void addRightChild(Iterator child, Iterator parent);

        void addLeftChild(BinaryTree<Type>* child, Iterator parent);
        void addRightChild(BinaryTree<Type>* child, Iterator parent);

        void deleteLeft(Iterator node);
        void deleteRight(Iterator node);

        Iterator getRoot() const;
        Iterator getLeftChild(Iterator node);
        Iterator getRightChild(Iterator node);
        Iterator getParent(Iterator node);

        void setRoot(Iterator newRoot);
        void setHeight(uint32_t newH);

        void preorderTraversal(Iterator root);
        void postorderTraversal(Iterator root);
        void inorderTraversal(Iterator root);
        void levelOrderTraversal(Iterator root);

        bool isLeftEmpty(Iterator leftChild);
        bool isRightEmpty(Iterator rightChild);
        bool isBinaryTreeEmpty();
        bool isLeaf(Iterator node);
        bool isRoot(Iterator node);

        uint32_t getHeight();
        uint32_t calculateNodesAmount();
        uint32_t calculateMaxLevel(Iterator node);

        BinaryTree<T>* subTree(Iterator root);
};

/**
 * Crea un albero binario vuoto
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 */
template <class T>
BinaryTree<T>::BinaryTree()
{
    this->_root = nullptr;
    this->_height = 0;
}

/**
 * Crea un albero binario con radice con valore rootValue
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param rootValue : Valore della radice
 */
template <class T>
BinaryTree<T>::BinaryTree(Type rootValue)
{
    this->_root = new BinaryTreeNode<T>(rootValue);
    this->_height = 0;
}

/**
 * Distruttore
 * 
 * @tparam T : Tipo di dato contenuto nell'albero 
 */
template <class T>
BinaryTree<T>::~BinaryTree()
{
    this->_erase(this->_root);
}



/**
 * Inserisce un nodo sinistra alla foglia piu' a sinistra dell'albero
 *
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param value - Valore della foglia
 */
template <class T>
void BinaryTree<T>::addLeftChild(Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator it = this->_root;

    while (it)
    {
        if (this->isLeftEmpty(it))
        {
            Iterator newLeftChild = new BinaryTreeNode<T>(value, it->_level + 1, it);
            it->_leftChild = newLeftChild;
            this->_updateHeight();

            return;
        }

        it = it->_leftChild;
    }

}

/**
 * Inserisce un figlio sinistro al nodo con radice node.
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node :  Radice in cui  inserire il  figlio  sinistro
 * @param value : Valore del figlio sinistro
 */
template <class T>
void BinaryTree<T>::addLeftChild(Iterator node, Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator leftNode = node->_leftChild;

    if (this->isLeftEmpty(leftNode))
    {
        Iterator newLeftChild = new BinaryTreeNode<T>(value, node->_level + 1, node);
        node->_leftChild = newLeftChild;
        this->_updateHeight();

        return;
    }
}

/**
 * Inserisce un nodo destro alla foglia piu' a destra dell'albero
 *
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param value - Valore della foglia
 */
template <class T>
void BinaryTree<T>::addRightChild(Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator it = this->_root;

    while (it)
    {
        if (this->isRightEmpty(it))
        {
            Iterator newRightChild = new BinaryTreeNode<T>(value, it->_level + 1, it);
            it->_rightChild = newRightChild;

            this->_updateHeight();

            return;
        }

        it = it->_rightChild;
    }


}

/**
 * Inserisce un figlio destro al nodo con radice node.
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node :  Radice in cui  inserire il  figlio  destro
 * @param value : Valore del figlio destro
 */
template <class T>
void BinaryTree<T>::addRightChild(Iterator node, Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator rightNode = node->_rightChild;

    if (this->isRightEmpty(rightNode))
    {
        Iterator newRightChild = new BinaryTreeNode<T>(value, node->_level + 1, node);
        node->_rightChild = newRightChild;
        this->_updateHeight();

        return;
    }

    node->_rightChild->_value = value;
}

/**
 * Aggiunge un nodo sinistro ad un nodo con radice parent
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param child : Puntatore al figlio sinitro  di parent
 * @param parent : Puntatore del nodo genitore di child
 */
template <class T>
void BinaryTree<T>::addLeftChild(Iterator child, Iterator parent)
{
    if (this->isLeftEmpty(parent))
    {
        parent->_leftChild = child;
        child->_parent = parent;
        this->_updateLevels(child, parent->_level);
        uint32_t childH = this->calculateMaxLevel(child);

        this->_updateHeight(childH, parent->_level);
    }
}

/**
 * Aggiunge un nodo destro ad un nodo con radice parent
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param child : Puntatore al figlio destro  di parent
 * @param parent : Puntatore del nodo genitore di child
 */
template <class T>
void BinaryTree<T>::addRightChild(Iterator child, Iterator parent)
{
    if (this->isRightEmpty(parent))
    {
        parent->_rightChild = child;
        child->_parent = parent;
        this->_updateLevels(child, parent->_level);
        uint32_t childH = this->calculateMaxLevel(child);

        this->_updateHeight(childH, parent->_level);
    }
}

/**
 * Aggiunge un sotto-albero, di radice child, a sinistro di un nodo con radice parent
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param child : Puntatore alla radice del sotto-albero
 * @param parent : Puntatore del nodo genitore di child
 */
template <class T>
void BinaryTree<T>::addLeftChild(BinaryTree<Type>* child, Iterator parent)
{
    this->addLeftChild(child->_root, parent);
}


/**
 * Aggiunge un sotto-albero, di radice child, a destra di un nodo con radice parent
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param child : Puntatore alla radice del sotto-albero
 * @param parent : Puntatore del nodo genitore di child
 */
template <class T>
void BinaryTree<T>::addRightChild(BinaryTree<Type>* child, Iterator parent)
{
    this->addRightChild(child->_root, parent);
}


/**
 * Elimina node, cioe' il figlio  sinistro di un nodo
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node : Figlio  sinistro  di  un nodo
 */
template <class T>
void BinaryTree<T>::deleteLeft(Iterator node)
{
    this->_erase(node);

    if (!this->_isNodeEmpty(this->_root))
    {
        node = nullptr;

        uint32_t newH = this->calculateMaxLevel(this->_root);
        this->_height = newH;
    }
}

/**
 * Elimina node, cioe' il figlio  destro di un nodo
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node : Figlio  destro  di  un nodo
 */
template <class T>
void BinaryTree<T>::deleteRight(Iterator node)
{
    this->_erase(node);

    if (!this->_isNodeEmpty(this->_root))
    {
        node = nullptr;

        uint32_t newH = this->calculateMaxLevel(this->_root);
        this->_height = newH;
    }
}

/**
 * Restituisce il  puntatore ad un sottoalbero di radice root.
 * Se root e' uguale alla radice dell'albero allora vieene restituito this
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param root : Radice del sottoalbero da restituire
 * @return Sottoalbero di radice root
 */
template <class T>
BinaryTree<T>* BinaryTree<T>::subTree(Iterator root)
{
    if (root == this->_root)
    {
        return this;
    }

    BinaryTree<T>* subT = new BinaryTree<T>;
    Iterator subRoot = new BinaryTreeNode<T>(root->_value);

    subRoot->_leftChild = root->_leftChild;
    subRoot->_rightChild = root->_rightChild;

    subT->_root = subRoot;
    this->_decreaseLevel(subRoot, root->_level);

    uint32_t newH = subT->calculateMaxLevel(subT->_root);
    subT->_height = newH;

    return subT;
}

/**
 * Attraversa l'albero con ordine previsita
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param root : Nodo di partenza della visita
 */
template <class T>
void BinaryTree<T>::preorderTraversal(Iterator root)
{
    if (root)
    {
        std::cout << root->_value << " ";
        this->preorderTraversal(root->_leftChild);
        this->preorderTraversal(root->_rightChild);
    }
}

/**
 * Attraversa l'albero con ordine postvisita
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param root : Nodo di partenza della visita
 */
template <class T>
void BinaryTree<T>::postorderTraversal(Iterator root)
{
    if (root)
    {
        this->postorderTraversal(root->_leftChild);
        this->postorderTraversal(root->_rightChild);
        std::cout << root->_value << " ";
    }
}

/**
 * Attraversa l'albero con ordine simmetrico
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param root : Nodo di partenza della visita
 */
template <class T>
void BinaryTree<T>::inorderTraversal(Iterator root)
{
    if (root)
    {
        this->inorderTraversal(root->_leftChild);
        std::cout << root->_value << " ";
        this->inorderTraversal(root->_rightChild);
    }
}

/**
 * Attraversa l'albero con visita a livelli
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param root : Nodo di partenza della visita
 */
template <class T>
void BinaryTree<T>::levelOrderTraversal(Iterator root)
{
    Queue<Iterator> queue;
    queue.enqueue(root);

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();

        std::cout << iter->_value << " ";

        if (iter->_leftChild)
        {
            queue.enqueue(iter->_leftChild);
        }

        if (iter->_rightChild)
        {
            queue.enqueue(iter->_rightChild);
        }
    }
}

/**
 * Restituisce true se il nodo sinistro di leftChild e' vuoto, altrimenti false
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param leftChild : Nodo a cui  controllare il nodo sinistro
 * @return True se il nodo sinistro di leftChild e' vuoto, altrimenti false
 */
template <class T>
bool BinaryTree<T>::isLeftEmpty(Iterator leftChild)
{
    if (this->_isNodeEmpty(leftChild))
    {
        return true;
    }

    return this->_isNodeEmpty(leftChild->_leftChild);
}

/**
 * Restituisce true se il nodo destro di rightChild e' vuoto, altrimenti false
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param leftChild : Nodo a cui  controllare il nodo destro
 * @return True se il nodo destro di leftChild e' vuoto, altrimenti false
 */
template <class T>
bool BinaryTree<T>::isRightEmpty(Iterator rightChild)
{
    if (this->_isNodeEmpty(rightChild))
    {
        return true;
    }

    return this->_isNodeEmpty(rightChild->_rightChild);
}

/**
 * Restituisce true se l'albero e' vuoto, altrimenti false.
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @return True se l'albero e' vuoto, altrimenti false.
 */
template <class T>
bool BinaryTree<T>::isBinaryTreeEmpty()
{
    return this->_isNodeEmpty(this->_root);
}

/**
 * Restituisce l'altezza totale dell'albero
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @return Altezza albero
 */
template <class T>
uint32_t BinaryTree<T>::getHeight()
{
    return this->_height;
}

/**
 * Immposta una nuova altezza all'albero
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param newH : Nuova altezzza dell'albero
 */
template <class T>
void BinaryTree<T>::setHeight(uint32_t newH)
{
    this->_height = newH;
}

/**
 * Restituisce il  numero totale di  nodi contenuti nell'albero
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @return Numero totale di nodi nell'albero
 */
template <class T>
uint32_t BinaryTree<T>::calculateNodesAmount()
{
    Queue<Iterator> queue;
    queue.enqueue(this->_root);
    uint32_t amount = 0;

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();
        amount++;

        if (iter->_leftChild)
        {
            queue.enqueue(iter->_leftChild);
        }

        if (iter->_rightChild)
        {
            queue.enqueue(iter->_rightChild);
        }
    }

    return amount;
}

/**
 * Restituisce il  puntatore alla radice dell'albero
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @return Puntatore alla radice
 */
template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getRoot() const
{
    return this->_root;
}


/**
 * Restituisce il  puntatore al figlio sinistro di node
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @return puntatore al figlio sinistro di node
 */
template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getLeftChild(Iterator node)
{
    return node->_leftChild;
}


/**
 * Restituisce il  puntatore al figlio destro di node
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @return puntatore al figlio destro di node
 */
template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getRightChild(Iterator node)
{
    return node->_rightChild;
}

/**
 * Restituisce il  puntatore al padre di  node
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node : Nodo a cui prendere il padre
 * @return Puntatore al padre di  node
 */
template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getParent(Iterator node)
{
    return node->_parent;
}

/**
 * Restituisce true se node e'  una foglia, altrimenti false
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node : Nodo da controllare
 * @return true se node e'  una foglia, altrimenti false
 */
template <class T>
bool BinaryTree<T>::isLeaf(Iterator node)
{
    return (this->isLeftEmpty(node)) && (this->isRightEmpty(node));
}

/**
 * Imposta la radice dell'albero
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param newRoot : Nuova radice
 */
template <class T>
void BinaryTree<T>::setRoot(Iterator newRoot)
{
    this->_root = newRoot;
}

/**
 * Restituisce il livello massimo dell'albero con radice node
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node : Radice albero o sottoalbero
 * @return Livello massimo
 */
template <class T>
uint32_t BinaryTree<T>::calculateMaxLevel(Iterator node)
{
    uint32_t leftH = 0;
    uint32_t rightH = 0;

    if (this->isLeaf(node))
    {
        return 0;
    }

    if (this->isLeftEmpty(node))
    {
        leftH = 0;
    }

    else
    {
        leftH = this->calculateMaxLevel(node->_leftChild) + 1;
    }

    if (this->isRightEmpty(node))
    {
        rightH = 0;
    }

    else
    {
        rightH = this->calculateMaxLevel(node->_rightChild) + 1;
    }

    if (leftH >= rightH)
    {
        return leftH;
    }

    return rightH;
}

/**
 * Restituisce true se node e' la  radice dell'albero, altrimenti false
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node : Nodo da controllare
 * @return true se node e' la  radice dell'albero, altrimenti false
 */
template <class T>
bool BinaryTree<T>::isRoot(Iterator node)
{
    return this->_isNodeEmpty(node->_parent);
}

/**
 * Restituisce true se node e' vuoto, altrimenti false
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param node : Nodo da controllare
 * @return true se node e' vuoto, altrimenti false
 */
template <class T>
bool BinaryTree<T>::_isNodeEmpty(Iterator node)
{
    return (node == nullptr);
}

/**
 * Aggiorna l'altezza dell'albero
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 */
template <class T>
void BinaryTree<T>::_updateHeight()
{
    uint32_t h = this->calculateMaxLevel(this->_root);

    if (h > this->_height)
    {
        this->_height++;
    }
}

/**
 * Aggiorna l'altezza di un sottoalbero 
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param subTreeHeight : Altezza del sottoalbero
 * @param parentH : Livello del genitore del sottoalbero
 */
template <class T>
void BinaryTree<T>::_updateHeight(uint32_t subTreeHeight, uint32_t parentH)
{
    this->_height = (subTreeHeight + parentH) - 1;
}

/**
 * Aggiorna i livelli dei nodi figli di startingNode, partendo dal suo livello
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param startingNode : Radice
 * @param initLevel ; Livello di partenza
 */
template <class T>
void BinaryTree<T>::_updateLevels(Iterator startingNode, uint32_t initLevel)
{
    if (!this->_isNodeEmpty(startingNode))
    {
        startingNode->_level = initLevel + 1;
        this->_updateLevels(startingNode->_leftChild, startingNode->_level);
        this->_updateLevels(startingNode->_rightChild, startingNode->_level);
    }
}

/**
 * Diminuisce i livelli dei nodi dell'albero  con radice root di un fattore pari  a
 * decrementFactor
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param root : Radice albero
 * @param decrementFactor : Di quanto diminuire i livelli dei nodi
 */
template <class T>
void BinaryTree<T>::_decreaseLevel(Iterator root, uint32_t decrementFactor)
{
    if (!this->_isNodeEmpty(root))
    {
        if (root->_level > 0)
        {
            root->_level -= decrementFactor;
        }

        this->_decreaseLevel(root->_leftChild, decrementFactor);
        this->_decreaseLevel(root->_rightChild, decrementFactor);
    }
}


/**
 * Cancella l'albero o sottoalbero di radice root
 * 
 * @tparam T : Tipo di dato contenuto nell'albero
 * @param root : Radice albero o sottoalbero
 */
template <class T>
void BinaryTree<T>::_erase(Iterator root)
{
    if (this->isLeaf(root))
    {
        if (root != this->_root)
        {
            if (root == root->_parent->_leftChild)
            {
                root->_parent->_leftChild = nullptr;
            }

            else if (root == root->_parent->_rightChild)
            {
                root->_parent->_rightChild = nullptr;
            }

            delete root;
        }

        else
        {
            delete root;
            this->_root = nullptr;
        }
    }

    else
    {
        if (!this->isLeftEmpty(root))
        {
            this->_erase(root->_leftChild);
        }

        if (!this->isRightEmpty(root))
        {
            this->_erase(root->_rightChild);
        }

        this->_erase(root);
    }
}



#endif // _BINARYTREE_H
