#ifndef _TREE_H
#define _TREE_H

#include "ITree.h"
#include "../Queue/Queue.h"



template <class T>
class Tree;

/**
 * Classe che implementa un nodo di un albero
 *
 * @tparam T : Tipo del nodo
 */
template <class T>
class TreeNode
{
    friend class Tree<T>;

    private:
        TreeNode<T>* _parent; // Puntatore al nodo padre del nodo figlio
        TreeNode<T>* _firstChild; // Puntatore al primo figlio del nodo genitore
        TreeNode<T>* _sibling; // Puntatore al fratello successivo di _firstChild

        T _value; // Valore del nodo
        uint32_t _level; // Livello del nodo

    public:
        TreeNode();
        TreeNode(const T& value);
        TreeNode(const T& value, TreeNode<T>* parent, uint32_t level);
        TreeNode(const T& value, TreeNode<T>* parent, TreeNode<T>* firstChild, uint32_t level);

        TreeNode(const TreeNode<T>& source);

        T getValue();
        uint32_t getLevel();
};

/**
 * Crea un
 *
 * @tparam T : Tipo del nodo
 */
template <class T>
TreeNode<T>::TreeNode()
{
    this->_parent = nullptr;
    this->_firstChild = nullptr;
    this->_sibling = nullptr;

    this->_level = 0;
}

/**
 * Crea un nodo di un albero
 *
 * @tparam T : Tipo del nodo
 * @param value : Valore nodo
 */
template <class T>
TreeNode<T>::TreeNode(const T& value)
{
    this->_parent = nullptr;
    this->_firstChild = nullptr;
    this->_sibling = nullptr;

    this->_value = value;
    this->_level = 0;
}

/**
 * Crea un nodo di un albero
 *
 * @tparam T : Tipo del nodo
 * @param value : Valore nodo
 * @param parent : Puntatore al padre
 * @param level : Livello nodo
 */
template <class T>
TreeNode<T>::TreeNode(const T& value, TreeNode<T>* parent, uint32_t level)
{
    this->_parent = parent;
    this->_firstChild = nullptr;
    this->_sibling = nullptr;

    this->_value = value;
    this->_level = level;
}

/**
 * Crea un nodo di un albero
 *
 * @tparam T : Tipo del nodo
 * @param value : Valore nodo
 * @param parent : Puntatore al padre
 * @param firstChild : Puntatore al primo figlio
 * @param level : Livello nodo
 */
template <class T>
TreeNode<T>::TreeNode(const T& value, TreeNode<T>* parent, TreeNode<T>* firstChild, uint32_t level)
{
    this->_parent = parent;
    this->_firstChild = firstChild;
    this->_sibling = nullptr;

    this->_value = value;
    this->_level = level;
}

/**
 * Costruttore di copia
 *
 * @tparam T : Tipo del nodo
 * @param source : Nodo da copiare
 */
template <class T>
TreeNode<T>::TreeNode(const TreeNode<T>& source)
{
    this->_parent = source._parent;
    this->_firstChild = source._firstChild;
    this->_sibling = source._sibling;

    this->_value = source._value;
    this->_level = source._level;
}


/**
 * Restituisce il valore contenuto in un nodo dell'albero
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @return Valore contenuto nel nodo
 */
template <class T>
T TreeNode<T>::getValue()
{
    return this->_value;
}

/**
 * Resituisce il livello del nodo, 0 se e' la radice, altimenti
 * dei valori maggiori di 0
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @return Livello del nodo
 */
template <class T>
uint32_t TreeNode<T>::getLevel()
{
    return this->_level;
}


/**
 * Implementazione della struttura dati degli alberi n-ari attraverso
 * puntatori
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 */
template <class T>
class Tree : public ITree<T, TreeNode<T>*>
{
    public:
        typedef typename ITree<T, TreeNode<T>*>::Type Type;
        typedef typename ITree<T, TreeNode<T>*>::Iterator Iterator;

    private:
        Iterator _root; // Puntatore alla radice dell'albero

    private:
        void _remove(Iterator root);
        void _getLeafAmount(Iterator start, uint32_t& counterSupport);

    public:
        Tree();
        Tree(const Type& value);
        ~Tree();

        bool isEmpty() const;
        bool isLeaf(Iterator node) const;
        Iterator getRoot() const;

        void insertFirstChild(Iterator parent, const Type& value);
        void insertSibling(Iterator child, const Type& value);

        void insertFirstChild(Iterator parent, TreeNode<Type>& node);
        void insertSibling(Iterator child, TreeNode<Type>& node);

        void insertFirstChild(Iterator parent, const Tree<Type>& subTree);
        void insertSibling(Iterator child, const Tree<Type>& subTree);

        bool isLastSibling(Iterator node) const;
        Iterator getNextSibling(Iterator node) const;
        Iterator getFirstChild(Iterator node) const;
        Iterator getParent(Iterator node) const;

        void preorderTraversal(Iterator root);
        void postorderTraversal(Iterator root);
        void inorderTraversal(Iterator root, uint32_t i);
        void levelOrderTraversal(Iterator root);

        void deleteFirstChild(Iterator root);
        void deleteSibling(Iterator child);

        uint32_t getNodesAmount();
        uint32_t calculateWidth(Iterator root);
        uint32_t getDepth(Iterator root);

        uint32_t getLeafAmount(Iterator root);
        uint32_t nodesPerLevel(uint32_t level);
};

/**
 * Costruttore di default della struttura
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 */
template <class T>
Tree<T>::Tree()
{
    this->_root = nullptr;
};

/**
 * Costruttore che permette di creare una radice dell'albero con
 * valore value.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param value: Valore della radice
 */
template <class T>
Tree<T>::Tree(const Type& value)
{
    this->_root = new TreeNode<T>(value);
}

/**
 * Distruttore della struttura dati
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 */
template<class T>
Tree<T>::~Tree()
{
    if (this->_root)
    {
        this->_remove(this->_root);
        this->_root = nullptr;
    }
}

/**
 * Restituisce true se l'albero e' vuoto, altrimenti false.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @return True se e' vuoto, altrimenti false
 */
template <class T>
bool Tree<T>::isEmpty() const
{
    return (this->_root == nullptr);
}

/**
 * Restituisce true se il nodo node e' una foglia, altrimenti false.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 *
 * @param node: Nodo da controllare
 * @return True se node e' foglia, altrimenti false
 */
template <class T>
bool Tree<T>::isLeaf(Iterator node) const
{
    return (node->_firstChild == nullptr);
}

/**
 * Restituisce il puntatore alla radice dell'albero
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @return Puntatore della radice dell'albero
 */
template <class T>
typename Tree<T>::Iterator Tree<T>::getRoot() const
{
    return this->_root;
}

/**
 * Inserisce un nodo con valore value, come primo figlio di un sottoalbero con
 * radice parent.
 * Il nuovo primo figlio, viene inserito prima dell'attuale primo figlio.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param parent: Radice sottoalbero in cui inserire il primo figlio
 * @param value: Valore del primo figlio
 */
template <class T>
void Tree<T>::insertFirstChild(Iterator parent, const Type& value)
{
    if (parent == nullptr)
    {
        return;
    }

    if (parent->_firstChild == nullptr)
    {
        // Se parent non ha il primo figlio, allora ne creo uno nuovo
        parent->_firstChild = new TreeNode<Type>(value, parent, parent->_level + 1);
        return;
    }

    /**
     * Se parent (p) ha un primo figlio (s), allora creo il nuovo primo figlio (f) e, il
     * precedente primo figlio (s), diventa il fratello successivo del nuovo primo figlio.
     * Quindi:
     *  - Prima dell'inserimento:
     *     p = {
     *          _parent: {GenericParent}
     *          _firstChild: {s},
     *          _sibling: null
     *      }
     *
     *      s = {
     *          _parent: {p}
     *          _firstChild: null,
     *          _sibling: null
     *      }
     *
     *  - Dopo l'inserimento:
     *     p = {
     *          _parent: {GenericParent}
     *          _firstChild: {f},
     *          _sibling: null
     *      }
     *
     *      f = {
     *          _parent: {p}
     *          _firstChild: null,
     *          _sibling: [{s}]
     *      }
     *
     *      s = {
     *          _parent: {p}
     *          _firstChild: null,
     *          _sibling: null
     *      }
     */

    Iterator newFirstChild = new TreeNode<Type>(value, parent, parent->_level + 1);
    Iterator oldFirstChild = parent->_firstChild;

    parent->_firstChild = newFirstChild;
    newFirstChild->_sibling = oldFirstChild;
}

/**
 * Inserisco un nuovo fratello, con valore value, al nodo child.
 * Il nuovo fratello viene inserito prima dell'attuale fratello successivo.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param child: Figlio a cui assegnare un nuovo nodo fratello
 * @param value: Valore del nodo fratello
 */
template<class T>
void Tree<T>::insertSibling(Iterator child, const Type& value)
{
    if (child == nullptr)
    {
        return;
    }

    if (child->_firstChild == nullptr)
    {
        if (child->_parent == nullptr) // Il padre e' la radice
        {
            child->_firstChild = new TreeNode<Type>(value, this->_root, this->_root->_level + 1);
            return;
        }

        // Child non ha un primo figlio, quindi vado a crearne uno
        child->_firstChild = new TreeNode<Type>(value, child->_parent, child->_parent->_level + 1);
        return;
    }

    if (child->_sibling == nullptr)
    {
        if (child->_parent == nullptr) // Il padre e' la radice
        {
            child = child->_firstChild;
            child->_sibling = new TreeNode<Type>(value, this->_root, this->_root->_level + 1);

            return;
        }

        // Child non ha fratelli, quindi vado a crearne uno
        child->_sibling = new TreeNode<Type>(value, child->_parent, child->_level);
        return;
    }

    /**
     * Child (c) possiede un fratello (f), quindi il nuovo fratello (s), verra'
     * inserito prima di f, quindi:
     *  - Prima dell'inserimento: c -> f
     *  - Dopo l'inserimento: c -> s -> f
     */

    Iterator newNextSibling = new TreeNode<Type>(value, child->_parent, child->_level);
    Iterator oldSibling = child->_sibling;

    child->_sibling = newNextSibling;
    newNextSibling->_sibling = oldSibling;
}


/**
 * Inserisce un nodo node, come primo figlio di un sottoalbero con
 * radice parent.
 * Il nuovo primo figlio, viene inserito prima dell'attuale primo figlio.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param parent: Radice sottoalbero in cui inserire il primo figlio
 * @param node: Nodo da inserire
 */
template <class T>
void Tree<T>::insertFirstChild(Iterator parent, TreeNode<Type>& node)
{
    if (parent == nullptr)
    {
        return;
    }

    node._level = parent->_level + 1;
    node._parent = parent;

    if (parent->_firstChild == nullptr)
    {
        parent->_firstChild = &node;
        return;
    }

    Iterator oldFirstChild = parent->_firstChild;
    parent->_firstChild = &node;

    node._sibling = oldFirstChild;
}

/**
 * Inserisco un nuovo nodo come fratello del nodo child.
 * Il nuovo fratello viene inserito prima dell'attuale fratello successivo.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param child: Figlio a cui assegnare un nuovo nodo fratello
 * @param node: Nodo da inserire
 */
template <class T>
void Tree<T>::insertSibling(Iterator child, TreeNode<Type>& node)
{
    if (child == nullptr)
    {
        return;
    }

    node._level = child->_level;
    node._parent = child->_parent;

    if (child->_sibling == nullptr)
    {
        child->_sibling = &node;
        return;
    }

    Iterator oldSibling = child->_sibling;
    child->_sibling = &node;
    node._sibling = oldSibling;
}


/**
 * Inserisce la radice del sottoalbero subTree, come primo figlio di un
 * sottoalbero con radice parent.
 * Il nuovo primo figlio, viene inserito prima dell'attuale primo figlio.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param parent: Radice sottoalbero in cui inserire il primo figlio
 * @param subTree: Sottoalbero da inserire
 */
template <class T>
void Tree<T>::insertFirstChild(Iterator parent, const Tree<Type>& subTree)
{
    Iterator root = subTree._root;
    this->insertFirstChild(parent, *root);

    Queue<Iterator> queue;
    queue.enqueue(root);
    Iterator currentParent = parent;

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();

        if (iter->_level <= currentParent->_level)
        {
            iter->_level = currentParent->_level + 1;
        }

        iter = iter->_firstChild;

        if (iter != nullptr)
        {
            currentParent = iter->_parent;
        }

        while (iter)
        {
            queue.enqueue(iter);
            iter = iter->_sibling;
        }
    }
}


/**
 * Inserisce la radice del sottoalbero subTree, come fratello del nodo child.
 * Il nuovo fratello viene inserito prima dell'attuale fratello successivo.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param child: Figlio a cui assegnare un nuovo nodo fratello
 * @param subTree: Sottoalbero da inserire
 */
template <class T>
void Tree<T>::insertSibling(Iterator child, const Tree<Type>& subTree)
{
    this->insertSibling(child, *(subTree._root));
}


/**
 * Restituisce true se node e' l'ultimo fratello, altrimenti false.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param node: Nodo da verificare
 * @return True se node e' l'ultimo fratello, false altrimenti
 */
template <class T>
bool  Tree<T>::isLastSibling(Iterator node) const
{
    return (node->_sibling == nullptr);
}

/**
 * Restituisce il puntatore del fratello di node.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param node: Nodo a cui prendere il prossimo fratello
 * @return Puntatore del fratello di node
 */
template <class T>
typename Tree<T>::Iterator Tree<T>::getNextSibling(Iterator node) const
{
    return node->_sibling;
}

/**
 * Restituisce il puntatore del primo figlio di node.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param node: Nodo a cui prendere il primo figlio
 * @return Puntatore del primo figlio di node
 */
template <class T>
typename Tree<T>::Iterator Tree<T>::getFirstChild(Iterator node) const
{
    return node->_firstChild;
}

/**
 * Restituisce il puntatore al padre di node.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param node: Nodo a cui prendere il padre
 * @return Puntatore del padre di node
 */
template <class T>
typename Tree<T>::Iterator Tree<T>::getParent(Iterator node) const
{
    return node->_parent;
}

/**
 * Attraversa l'albero in ordine anticipato, o in Depth-First Search
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice dell'albero o sottoalbero
 */
template <class T>
void Tree<T>::preorderTraversal(Iterator root)
{
    if (root == nullptr)
    {
        return;
    }

    std::cout << root->_value << " ";
    Iterator it = root->_firstChild;

    while (it)
    {
        this->preorderTraversal(it);
        it = it->_sibling;
    }
}

/**
 * Attraversa l'albero in ordine posticipato, o in Depth-First Search
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice dell'albero o sottoalbero
 */
template <class T>
void Tree<T>::postorderTraversal(Iterator root)
{
    if (root == nullptr)
    {
        return;
    }

    Iterator it = root->_firstChild;

    while (it)
    {
        this->postorderTraversal(it);
        it = it->_sibling;
    }

    std::cout << root->_value << " ";
}

/**
 * Attraversa l'albero in ordine simmetrico, o in Depth-First Search
 *
 * Supponiamo che root abbia k sottoalberi, con k > 0.
 * Il parametro i, dove i >= 1, serve per effetuare l'esame simmetrico dei primi
 * i sottoalberi di root e, una volta attuato, viene esaminata la
 * radice e successivamente i restanti i + 1 sottoalberi di root.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice dell'albero o sottoalbero
 * @param i: Numero di sottoalberi di root, da visitare prima di
 * esaminare la radice
 */
template <class T>
void Tree<T>::inorderTraversal(Iterator root, uint32_t i)
{
    if (root == nullptr)
    {
        return;
    }

    if (i == 0)
    {
        return;
    }

    uint32_t k = 0;
    Iterator it = root->_firstChild;

    // Attuo l'ordine simmetrico sui primi i figli di root
    while (it && k < i)
    {
        k++;
        this->inorderTraversal(it, i);
        it = it->_sibling;
    }

    std::cout << root->_value << " ";

    // Attuo l'ordine simmetrico sui successivi i + 1 figli di root
    while (it)
    {
        this->inorderTraversal(it, i);
        it = it->_sibling;
    }
}

/**
 * Attraverso l'albero per livelli, o in Breadth-First Search
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice dell'albero o sottoalbero
 */
template <class T>
void Tree<T>::levelOrderTraversal(Iterator root)
{
    if (root == nullptr)
    {
        return;
    }

    Queue<Iterator> queue;
    queue.enqueue(root);

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();

        std::cout << iter->_value << " " << iter->_level << "\n";
        iter = iter->_firstChild;

        while (iter)
        {
            queue.enqueue(iter);
            iter = iter->_sibling;
        }
    }
}



/**
 * Distrugge il sottoalbero che ha come radice il primo figlio di root.
 * Il nuovo primo figlio sara' il fratello successivo del primo figlio di root.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Padre a cui eliminare il sottoalbero che ha come radice il
 * suo primo figlio
 */
template <class T>
void Tree<T>::deleteFirstChild(Iterator root)
{
    Iterator newChild = root->_firstChild->_sibling;
    this->_remove(root->_firstChild);

    root->_firstChild = newChild;
}

/**
 * Distrugge il sottoalbero che ha come radice il prossimo fratello del nodo
 * child. Vado quindi a cancellare il primo fratello che ha il nodo child, ovvero
 * il fratello successivoo di child.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param child: Nodo a cui eliminare il suo fratello successivo
 */
template <class T>
void Tree<T>::deleteSibling(Iterator child)
{
    Iterator newBrother = child->_sibling->_sibling;
    this->_remove(child->_sibling);

    child->_sibling = newBrother;
}


/**
 * Restituisce la larghezza dell'albero con radice root.
 * Per larghezza di un albero si intende il numero massimo di nodi che si
 * trovano sullo stesso livello.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice dell'albero o sottoalbero
 * @return Larghezza dell'albero.
 */
template <class T>
uint32_t Tree<T>::calculateWidth(Iterator root)
{
    if (root == nullptr)
    {
        return 0;
    }

    uint32_t max = 0;
    Queue<Iterator> queue;
    queue.enqueue(root);

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();

        iter = iter->_firstChild;

        while (iter)
        {
            queue.enqueue(iter);
            iter = iter->_sibling;
        }

        if (max < queue.getLength())
        {
            max = queue.getLength();
        }
    }

    return max;
}

/**
 * Restituisce l'altezza dell'albero con radice root.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice dell'albero o sottoalbero
 * @return Altezza dell'albero
 */
template <class T>
uint32_t Tree<T>::getDepth(Iterator root)
{
    if (root == nullptr)
    {
        return 0;
    }

    uint32_t max = 0;
    Iterator it = root->_firstChild;

    while (it)
    {
        /**
         * Calcolo l'altezza di ogni sottoalbero, con radice it, per poi
         * confrontare l'altezza calcolata con l'altezza degli alberi radicati
         * nei figli di it
         */

        uint32_t tMax = this->getDepth(it) + 1;

        if (tMax > max)
        {
            max = tMax;
        }

        it = it->_sibling; // Vado al fratello successivo del primo figlio radicato in root
    }

    return max;
}


/**
 * Restituisce il numero di nodi totali contenuti nell'albero.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @return Numero totale di nodi nell'albero
 */
template <class T>
uint32_t Tree<T>::getNodesAmount()
{
    if (this->_root == nullptr)
    {
        return 0;
    }

    uint32_t nAmount = 1;

    Queue<Iterator> queue;
    queue.enqueue(this->_root);

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();

        iter = iter->_firstChild;
        nAmount++;

        while (iter)
        {
            queue.enqueue(iter);
            iter = iter->_sibling;

        }
    }

    return nAmount;
}

/**
 * Restituisce il numero di foglie contenute nell'albero o sottoalbero
 * con radice root.
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice di un albero o sottoalbero
 * @return Numero di foglie di root
 */
template <class T>
uint32_t Tree<T>::getLeafAmount(Iterator root)
{
    uint32_t leafCounter = 0;
    this->_getLeafAmount(root, leafCounter);

    return leafCounter;
}


/**
 * Restituisce il numero di nodi presenti nel livello level. Restituisce
 * zero se level e' maggiore dell'altezza dell'albero
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param level: Livello dell'albero
 * @return
 */
template <class T>
uint32_t Tree<T>::nodesPerLevel(uint32_t level)
{
    uint32_t maxH = this->getDepth(this->_root);

    if (level > maxH) // Livello non valido, quindi non ho nodi su quel livello
    {
        return 0;
    }

    if (level == 0) // Ho il livello della radice e quindi ho 1 solo nodo
    {
        return 1;
    }

    Queue<Iterator> queue;

    Iterator lvlIterator = this->_root;
    queue.enqueue(this->_root);

    while (!queue.isEmpty())
    {
        Iterator it = queue.top();

        /**
         * Se trovo il livello desiderato, allora la mia coda conterra' il numero
         * di nodi presenti nel livello level
         */
        if (it->_level == level)
        {
            return queue.getLength();
        }

        queue.dequeue();


        /**
         * Se non mi trovo al livello desiderato, allora scendo
         * al livello successivo e salvo nella coda, il primo figlio al livello
         * successivo, insieme ai suoi fratelli successivi
         */
        lvlIterator = it->_firstChild;
        Iterator siblingIt = lvlIterator->_sibling;

        queue.enqueue(lvlIterator);

        /**
         * Salvo in coda tutti i fratelli del nodo
         * al livello successivo, contenuto in lvlIterator
         */
        while (siblingIt)
        {
            queue.enqueue(siblingIt);
            siblingIt = siblingIt->_sibling;
        }
    }
}


/**
 * Permette la cancellazione dell'albero o del sottoalbero con
 * radice root.
 *
  * @tparam T: Tipo di dato contenuto nell'albero
 * @param root: Radice dell'albero o del sottoalbero da cancellare
 */
template <class T>
void Tree<T>::_remove(Iterator root)
{
    if (!root)
    {
        return;
    }

    Iterator it = root->_firstChild; // Parto dal primo figlio di root

    /**
     * Itero ricorsivamente sui sottoalberi di root andando a prendere prima
     * il primo figlio e poi i successivi fratelli di ogni primo figlio
     */
    while (it != nullptr)
    {
        Iterator next = it->_sibling; // Salvo il riferimento al fratello successivo di it
        this->_remove(it);

        it = next;
    }

    delete root;
    root = nullptr;
}




/**
 * Funzione di supporto per la getLeafAmount
 *
 * @tparam T: Tipo di dato contenuto nell'albero
 * @param start: Nodo di partenza
 * @param counterSupport: Reference del contatore delle foglie
 */
template <class T>
void Tree<T>::_getLeafAmount(Iterator start, uint32_t& counterSupport)
{
    if (this->isLeaf(start))
    {
        counterSupport++; // Ho trovato una foglia
    }

    else
    {
        /**
         * Se start non e' una foglia, allora esamino i suoi figli, per poi
         * fermarmi una volta esaminati tutti.
         */
        start = start->_firstChild;
        bool readAllSiblings = false;

        while (!readAllSiblings)
        {
            this->_getLeafAmount(start, counterSupport);

            if (this->isLastSibling(start))
            {
                readAllSiblings = true;
            }

            else
            {
                start = start->_sibling;
            }
        }
    }
}




#endif // _TREE_H
