#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "ILinkedList.h"
#include "../PriorityQueue/PriorityQueue.h"

#include <iostream>

// TODO: Mettere delle eccezioni nella classe
// nei metodi in cui ho gli indici circolari, se index sfora la grandezza della lista allora vai di
// IndexOutOfBound

template <class T>
class LinkedList;

/**
 * Classe del nodo della lista contatenata doppia
 * @tparam T: Tipo di dato contenuto nel nodo
 */
template <class T>
class LinkedNode
{
    friend class LinkedList<T>;

    private:
        T _value; // Valore del nodo
        LinkedNode<T>* _next; // Puntatore al nodo successivo
        LinkedNode<T>* _prev; // Puntatore al nodo precedente

    public:
        LinkedNode();
        LinkedNode(const T& value);
        LinkedNode(const T& value, LinkedNode<T>* next);
        LinkedNode(const T& value, LinkedNode<T>* next, LinkedNode<T>* prev);
        LinkedNode(const LinkedNode<T>& source);

        T getNodeValue();
        LinkedNode<T>* getNext();
        LinkedNode<T>* getPrev();

        void setNodeValue(const T& value);
        void setNext(LinkedNode<T>* next);
        void setPrev(LinkedNode<T>* prev);

        template <class V>
        friend std::ostream& operator<<(std::ostream& out, const LinkedNode<V>* node);
};

/**
 * Costruisce un nodo vuoto
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 */
template <class T>
LinkedNode<T>::LinkedNode()
{
    this->_next = nullptr;
    this->_prev = nullptr;
}

/**
 * Costruisce un nodo con valore value
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @param value : Valore del nodo
 */
template <class T>
LinkedNode<T>::LinkedNode(const T& value)
{
    this->_value = value;
    this->_next = nullptr;
    this->_prev = nullptr;
}

/**
 * Costruisce un nodo con un valore value e un puntatore al nodo successivo
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @param value : Valore del nodo
 * @param next : Puntatore al nodo successivo
 */
template <class T>
LinkedNode<T>::LinkedNode(const T& value, LinkedNode<T>* next)
{
    this->_value = value;
    this->_next = next;
    this->_prev = nullptr;
}

/**
 * Costruisce un nodo con un valore value, un puntatore al nodo successivo
 * e un puntatore al nodo precedente
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @param value : Valore del nodo
 * @param next : Puntatore al nodo successivo
 * @param prev : Puntatore al nodo precedente
 */
template <class T>
LinkedNode<T>::LinkedNode(const T& value, LinkedNode<T>* next, LinkedNode<T>* prev)
{
    this->_value = value;
    this->_next = next;
    this->_prev = prev;
}

/**
 * Costruttore di copia
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @param source : Nodo da copiare
 */
template <class T>
LinkedNode<T>::LinkedNode(const LinkedNode<T>& source)
{
    this->_value = source._value;
    this->_prev = source._prev;
    this->_next = source._next;
}

/**
 * Restituisce il valore contenuto nel nodo
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @return Valore del nodo
 */
template <class T>
T LinkedNode<T>::getNodeValue()
{
    return this->_value;
}

/**
 * Restituisce il puntatore al nodo successivo
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @return Puntatore al nodo sucessivo
 */
template <class T>
LinkedNode<T>* LinkedNode<T>::getNext()
{
    return this->_next;
}

/**
 * Restituisce il puntatore al nodo precedente.
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @return Puntatore al nodo precedente
 */
template <class T>
LinkedNode<T>* LinkedNode<T>::getPrev()
{
    return this->_prev;
}

/**
 * Imposta il valore del nodo
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @param value: Valore del nodo
 */
template <class T>
void LinkedNode<T>::setNodeValue(const T& value)
{
    this->_value = value;
}

/**
 * Imposta il nodo successivo del nodo corrente
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @param next: Puntatore al nodo successivo di questo nodo
 */
template <class T>
void LinkedNode<T>::setNext(LinkedNode<T>* next)
{
    this->_next = next;
}

/**
 * Imposta il nodo precedente del nodo corrente
 *
 * @tparam T: Tipo di dato contenuto nel nodo
 * @param prev: Puntatore al nodo precedente di questo nodo
 */
template <class T>
void LinkedNode<T>::setPrev(LinkedNode<T>* prev)
{
    this->_prev = prev;
}


template <class T>
std::ostream& operator<<(std::ostream& out, const LinkedNode<T>* node)
{
    out << "{ " << node->_value << " }" << std::endl;

    return out;
}


/**
 * Classe che realizza con puntatori la struttura dati della Lista Doppia Concatenata.
 *
 * @tparam T: Tipo di dato memorizzato nella lista
 */
template <class T>
class LinkedList: public ILinkedList<T, LinkedNode<T>*>
{
    public:
        typedef typename ILinkedList<T, LinkedNode<T>*>::Type Type;
        typedef typename ILinkedList<T, LinkedNode<T>*>::Iterator Iterator;

    private:
        Iterator _headPtr; // Nodo sentinella che punta al primo elemento della lista
        Iterator _tail; // Puntatore all'ultimo elemento della lista
        std::size_t _len; // Lunghezza della lista

    private:
        void _createLookout();
        void _createLookout(const T& value);

    public:
        LinkedList();
        LinkedList(const T& value);
        LinkedList(const LinkedList<T>& otherList);
        ~LinkedList();

        std::size_t getSize() const override;
        bool isEmpty() const override;

        Iterator find(std::size_t index) const;

        void insert(const T& value, std::size_t index) override;
        void insert(Iterator pos, const T& value);

        void remove(std::size_t index);
        void remove(const T& value);
        void remove(Iterator pos);

        void unshift(const T& value) override;
        void append(const T& value) override;
        void shift() override;
        void deleteLast() override;
        void removeDuplicate();

        Iterator begin() const;
        Iterator last() const;

        void heapSort();
        void insertionSort();

        bool isEnd(Iterator it) const;

        LinkedList<T>& operator=(const LinkedList<T>& list);
        bool operator==(const LinkedList<T>& list) const;
        bool operator!=(const LinkedList<T>& list) const;

};

/**
 * Crea una lista vuota
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
LinkedList<T>::LinkedList()
{
    this->_len = 0;
    this->_createLookout();
}

/**
 * Costrutisce una lista con un valore value in testa
 * @tparam T: Tipo della lista e dei nodi
 * @param value : Valore da mettere in testa
 */
template <class T>
LinkedList<T>::LinkedList(const T& value)
{
    this->_len = 1;
    this->_createLookout(value);
}

/**
 * Costuttore di copia
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param otherList : Lista da copiare
 */
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherList)
{
    this->_len = 0;
    this->_createLookout();

    if (!otherList.isEmpty())
    {
        Iterator it = otherList.begin();

        for (uint32_t i = 0; i < otherList._len; i++)
        {
            this->append(it->_value);
            it = it->_next;
        }
    }
}

/**
 * Distruttore
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
LinkedList<T>::~LinkedList()
{
    while (!this->isEmpty())
    {
        this->shift();
    }

    delete this->_headPtr;
}

/**
 * Resituisce la lunghezza della lista.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Lunghezza della lista
 */
template <class T>
std::size_t LinkedList<T>::getSize() const
{
    return this->_len;
}

/**
 * Restituisce true se la lista contiene degli elementi, altrimenti false
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return True se la lista e' vuota, altrimenti false
 */
template <class T>
bool LinkedList<T>::isEmpty() const
{
    return (this->_headPtr->_next == this->_headPtr);
}

/**
 * Cerca e restituisce un nodo in posizione index, dove index e' compreso fra 0 e n - 1, estremi inclusi, con
 * n lunghezza della lista.
 *
 * Se index >= n, allora la nuova posizione e' pari a:
 *
 *      newIndex = index % n.
 *
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param index: Posizione del nodo da prendere
 * @return Nodo in posizione index
 */
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::find(std::size_t index) const
{
    if (index >= this->_len)
    {
        index %= this->_len;
    }

    if (index == this->_len - 1)
    {
        return this->_tail;
    }

    if (index == 0)
    {
        return this->begin();
    }

    if (this->_len >= 0)
    {
        uint32_t i = 0;
        Iterator it = this->begin();

        while (i != index)
        {
            it = it->getNext();
            i++;
        }
        
        return it;
    }
}


/**
 * Inserisce un nodo con valore value, in posizione index della lista
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param value: Valore del nodo
 * @param index: Indice in cui inserire il nodo
 */
template <class T>
void LinkedList<T>::insert(const T& value, std::size_t index)
{
    if (this->isEmpty() || index == 0)
    {
        this->unshift(value);
        return;
    }

    if (index == this->_len - 1)
    {
        this->append(value);
        return;
    }

    if (index >= this->_len)
    {
        index %= this->_len;
    }

    Iterator it = this->find(index);
    Iterator prev = it->_prev;

    Iterator newNode = new LinkedNode<T>(value);

    prev->_next = newNode;
    newNode->_prev = prev;

    newNode->_next = it;
    it->_prev = newNode;

    this->_len += 1;
}

/**
 * Inserisce un nodo con valore value, in posizione precedente a pos.
 * pos avra' posizione i + 1, con i la sua posizione precedente all'inserimento
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param pos: Puntatore del nodo in cui inserire il nodo
 * @param value: Valore del nodo
 */
template <class T>
void LinkedList<T>::insert(Iterator pos, const T& value)
{
    Iterator prev = pos->_prev;

    Iterator newNode = new LinkedNode<T>(value);

    prev->_next = newNode;
    newNode->_prev = prev;

    newNode->_next = pos;
    pos->_prev = newNode;

    this->_len += 1;
}

/**
 * Rimuove il nodo pos dalla lista.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param pos: Puntatore del nodo da eliminare
 */
template <class T>
void LinkedList<T>::remove(Iterator pos)
{
    if (this->isEmpty() || this->isEnd(pos))
    {
        return;
    }

    Iterator prev = pos->_prev;
    Iterator next = pos->_next;

    prev->_next = next;
    next->_prev = prev;

    if (pos == this->last())
    {
        this->_tail = prev;
    }

    delete pos;
    pos = nullptr;

    this->_len -= 1;
}

/**
 * Rimuove un nodo con valore value dalla lista.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param value: Valore da eliminare dalla lista
 */
template <class T>
void LinkedList<T>::remove(const T& value)
{
    if (this->isEmpty())
    {
        return;
    }

    Iterator it = this->begin();

    while (!this->isEnd(it))
    {
        if (it->_value == value)
        {
            this->remove(it);
            return;
        }

        it = it->_next;
    }
}




/**
 * Elimina un nodo in posizione index della lista
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param index: Indice del nodo da eliminare
 */
template <class T>
void LinkedList<T>::remove(std::size_t index)
{
    if (!this->isEmpty())
    {
        if (index == 0)
        {
            this->shift();
            return;
        }

        if (index == this->_len - 1)
        {
            this->deleteLast();
            return;
        }

        if (index >= this->_len)
        {
            index %= this->_len;
        }

        Iterator it = this->find(index);
        Iterator prev = it->getPrev();
        Iterator next = it->getNext();

        prev->_next = next;
        next->_prev = prev;

        delete it;
        it = nullptr;

        this->_len -= 1;
    }
}

/**
 * Aggiunge un nodo, con valore "value", all'inizio della lista.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param value: Valore del nodo
 */
template <class T>
void LinkedList<T>::unshift(const T& value)
{
    Iterator newNode = new LinkedNode<T>;
    newNode->_value = value;

    if (this->isEmpty())
    {
       this->_createLookout(value);
    }

    else
    {
        Iterator oldHead = this->_headPtr->_next;
        this->_headPtr->_next = newNode;

        newNode->_prev = this->_headPtr;
        newNode->_next = oldHead;
        oldHead->_prev = newNode;
    }

    this->_len += 1;
}


/**
 * Aggiunge un nodo, con valore "value", alla fine della lista.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param value: Valore del nodo
 */
template <class T>
void LinkedList<T>::append(const T& value)
{
    Iterator newNode = new LinkedNode<T>;
    newNode->_value = value;

    if (this->isEmpty())
    {
       this->_createLookout(value);
    }

    else
    {
        Iterator oldTail = this->_tail;

        oldTail->_next = newNode;
        newNode->_prev = oldTail;

        newNode->_next = this->_headPtr;
        this->_headPtr->_prev = newNode;

        this->_tail = newNode;
    }

    this->_len += 1;
}


/**
 * Cancella il primo nodo dalla lista
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
void LinkedList<T>::shift()
{
    if (!this->isEmpty())
    {
        Iterator newHead;
        Iterator oldHead = this->_headPtr->_next;

        if (this->_len > 1)
        {
            newHead = oldHead->_next;

            this->_headPtr->_next = newHead;
            newHead->_prev = this->_headPtr;
        }

        delete oldHead;
        oldHead = nullptr;

        if (this->_len == 1)
        {
            this->_headPtr->_next = this->_headPtr;
            this->_headPtr->_prev = this->_headPtr;
        }

        this->_len -= 1;
    }
}


/**
 * Cancella l'ultimo nodo dalla lista
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
void LinkedList<T>::deleteLast()
{
    if (!this->isEmpty())
    {
        Iterator newTail;
        Iterator oldTail = this->_tail;

        if (this->_len > 1)
        {
            newTail = this->_tail->_prev;

            newTail->_next = this->_headPtr;
            this->_headPtr->_prev = newTail;

            this->_tail = newTail;
        }

        delete oldTail;
        oldTail = nullptr;

        if (this->_len == 1)
        {
            this->_headPtr->_next = this->_headPtr;
            this->_headPtr->_prev = this->_headPtr;

            this->_tail = nullptr;
        }

        this->_len -= 1;
    }
}

/**
 * Rimuove eventuali duplicati all'interno della lista
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
void LinkedList<T>::removeDuplicate()
{
    if (this->isEmpty())
    {
        return;
    }

    Iterator scan = this->begin();
    Iterator it = this->begin();
    Iterator prevScan;

    while (it != this->last())
    {
        while (!this->isEnd(scan))
        {
            if (it != scan)
            {
                if (it->_value == scan->_value)
                {
                    prevScan = scan->_prev;
                    this->remove(scan);
                    scan = prevScan;
                }
            }

            scan = scan->_next;
        }

        it = it->_next;
        scan = this->begin();
    }
}


/**
 * Restituisce la testa della lista, cioe' il primo elemento
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Puntatore al primo nodo della lista
 */
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const
{
    return this->_headPtr->_next;
}


/**
 * Restituisce la coda della lista, cioe' l'ultimo elemento
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Puntatore all'ultimo nodo della lista
 */
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::last() const
{
    return this->_tail;
}


/**
 * Restituisce true se ho raggiunto la fine della lista, altrimenti false
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param it: Posizione da verificare
 * @return Valore booleano pari a true se ho raggiunto la fine della lista, altrimenti false.
 */
template <class T>
bool LinkedList<T>::isEnd(Iterator it) const
{
    return (it == this->_headPtr);
}

/**
 * Implementazione dell'algoritmo di ordinamento dell' Heap Sort
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
void LinkedList<T>::heapSort()
{
    if (this->isEmpty())
    {
        return;
    }

    PriorityQueue<T> pQueue;

    // Carico tutti gli elementi della lista disordinata nella coda con priorita'
    for (Iterator it = this->begin(); !this->isEnd(it); it = it->_next)
    {
        pQueue.insert(it->_value);
    }

    /**
     * Fin quando la coda con priorita' non è vuota, inserisco il minimo nella
     * lista, andando sovrascrivendo il vecchio valore
     */

    for (Iterator it = this->begin(); !this->isEnd(it); it = it->_next)
    {
        it->_value = pQueue.min();
        pQueue.deleteMin();
    }
}


/**
 * Implementazione dell'algoritmo di ordinamento Insertion Sort
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
void LinkedList<T>::insertionSort()
{
    Iterator q;
    Type type;

    for (Iterator it = this->begin(); !this->isEnd(it); it = it->getNext())
    {
        type = it->getNodeValue();

        if (it != this->begin())
        {
            q = this->begin();

            while (q->getNodeValue() < type)
            {
                q = q->getNext();
            }

            LinkedNode<T> pIt(*it);

            this->insert(q, type);
            this->remove(it);

            it = &pIt;
        }
    }
}


/**
 * Crea il nodo sentinella della lista vuota
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
void LinkedList<T>::_createLookout()
{
    this->_headPtr = new LinkedNode<T>;

    this->_headPtr->_next = this->_headPtr;
    this->_headPtr->_prev = this->_headPtr;

    this->_tail = nullptr;
}

/**
 * Crea il nodo sentinella della lista e li aggiunge un nodo con
 * valore "value"
 *
 * @tparam T: Tipo del nodo e della lista
 * @param value: Valore del nodo
 */
template <class T>
void LinkedList<T>::_createLookout(const T& value)
{
    Iterator newHead = new LinkedNode<T>(value);

    this->_headPtr = new LinkedNode<T>;
    this->_headPtr->_next = newHead;

    newHead->_next = this->_headPtr;
    newHead->_prev = this->_headPtr;

    this->_headPtr->_prev = newHead;
    this->_tail = newHead;
}


template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
    if (this != &list)
    {
        this->_createLookout();

        if (!list.isEmpty())
        {
            Iterator it = list.begin();

            while (!list.isEnd(it))
            {
                this->append(it->_value);
                it = it->_next;
            }
        }
    }

    return *this;
}


template <class T>
bool LinkedList<T>::operator==(const LinkedList<T>& list) const
{
    if (this->_len != list._len)
    {
        return false;
    }

    Iterator itF = this->begin();
    Iterator itS = list.begin();

    while (!list.isEnd(itS))
    {
       if (itF->_value != itS->_value)
       {
           return false;
       }

        itF = itF->_next;
        itS = itS->_next;
    }

    return true;
}


template <class T>
bool LinkedList<T>::operator!=(const LinkedList<T>& list) const
{
    if (this->_len != list._len)
    {
        return true;
    }

    Iterator itF = this->begin();
    Iterator itS = list.begin();

    while (!list.isEnd(itS))
    {
        if (itF->_value != itS->_value)
        {
            return true;
        }

        itF = itF->_next;
        itS = itS->_next;
    }

    return false;
}



#endif // _LINKED_LIST_H
