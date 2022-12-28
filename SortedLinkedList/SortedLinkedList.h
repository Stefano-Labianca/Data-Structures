#ifndef _SORTEDLINKEDLIST_H
#define _SORTEDLINKEDLIST_H

#include "../LinkedList/LinkedList.h"
#include "ISortedLinkedList.h"


template <class T>
class SortedLinkedList : public ISortedLinkedList<T, LinkedNode<T>*>
{
    public:
        typedef typename ISortedLinkedList<T, LinkedNode<T>*>::Iterator Iterator;
        typedef typename ISortedLinkedList<T, LinkedNode<T>*>::Type Type;

    private:
        LinkedList<T>* _sortedList;

    public:
        SortedLinkedList();
        SortedLinkedList(const T& value);
        SortedLinkedList(const SortedLinkedList<T>& otherList);
        ~SortedLinkedList();

        uint32_t getSize() const;
        bool isEmpty() const;

        void add(const T& value);
        void remove(uint32_t index);

        Iterator getMin();
        Iterator getMax();

        Iterator find(uint32_t index);

        template <class V>
        friend std::ostream& operator<<(std::ostream& out, const SortedLinkedList<V>& sList);

        SortedLinkedList<T>& operator=(const SortedLinkedList<T>& sList);
        bool operator==(const SortedLinkedList<T>& sList) const;
        bool operator!=(const SortedLinkedList<T>& sList) const;
};


template <class T>
SortedLinkedList<T>::SortedLinkedList()
{
    this->_sortedList = new LinkedList<T>();
}


template <class T>
SortedLinkedList<T>::SortedLinkedList(const T& value)
{
    this->_sortedList = new LinkedList<T>(value);
}

template <class T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T>& otherList)
{
    this->_sortedList = new LinkedList<T>();

    if (!otherList._sortedList->isEmpty())
    {
        Iterator it = otherList._sortedList->begin();

        for (uint32_t i = 0; i < otherList._sortedList->getSize(); i++)
        {
            this->_sortedList->append(it->getNodeValue());
            it = it->getNext();
        }
    }
}

template <class T>
SortedLinkedList<T>::~SortedLinkedList()
{
    while (!this->_sortedList->isEmpty())
    {
        this->_sortedList->shift();
    }

    delete this->_sortedList;
}

/**
 * Resituisce la lunghezza della lista.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Lunghezza della lista
 */
template <class T>
uint32_t SortedLinkedList<T>::getSize() const
{
    return this->_sortedList->getSize();
}

/**
 * Restituisce true se la lista contiene degli elementi, altrimenti false
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return True se la lista e' vuota, altrimenti false
 */
template <class T>
bool SortedLinkedList<T>::isEmpty() const
{
    return this->_sortedList->isEmpty();
}


/**
 * Aggiunge un nodo con valore value nella lista
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param value: Valore del nodo
 */
template <class T>
void SortedLinkedList<T>::add(const T &value)
{
    if (this->_sortedList->isEmpty())
    {
        this->_sortedList->unshift(value);
        return;
    }

    if (value >= this->_sortedList->last()->getNodeValue()) // "value" e' il massimo
    {
        this->_sortedList->append(value);
        return;
    }

    if (value <= this->_sortedList->begin()->getNodeValue()) // "value" e' il minimo
    {
        this->_sortedList->unshift(value);
        return;
    }

    Iterator it = this->_sortedList->begin()->getNext();

    while (!this->_sortedList->isEnd(it))
    {
        if (value <= it->getNodeValue())
        {
            this->_sortedList->insert(it, value);
            return;
        }

        it = it->getNext();
    }
}

/**
 * Rimuove un nodo in posizione index
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param index: Posizione del nodo da eliminare
 */
template <class T>
void SortedLinkedList<T>::remove(uint32_t index)
{
    if (this->_sortedList->isEmpty())
    {
        return;
    }

    if (index == 0)
    {
        this->_sortedList->shift();
        return;
    }

    if (index == this->_sortedList->getSize() - 1)
    {
        this->_sortedList->deleteLast();
        return;
    }

    Iterator it = this->_sortedList->begin()->getNext();
    uint32_t pos = 1;

    while (it != this->_sortedList->last())
    {
        if (pos == index)
        {
            this->_sortedList->remove(it);
            return;
        }

        it = it->getNext();
        pos++;
    }
}

/**
 * Restituisce il nodo situato in posizione index, dove index e' compreso fra 0 e n - 1 estremi inclusi
 * con n lunghezza della lista, all'interno della lista
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param index: Indice dell'elemento da cercare
 * @return Puntatore al nodo in posizione index
 */
template <class T>
typename SortedLinkedList<T>::Iterator SortedLinkedList<T>::find(uint32_t index)
{
    return this->_sortedList->find(index);
}

/**
 * Restituisce il puntatore del nodo con il valore piu' piccolo nella lista
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Puntatore al nodo con valore minore
 */
template <class T>
typename SortedLinkedList<T>::Iterator SortedLinkedList<T>::getMin()
{
    return this->_sortedList->begin();
}

/**
 * Restituisce il puntatore del nodo con il valore piu' grande nella lista
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Puntatore al nodo con valore massimo
 */
template <class T>
typename SortedLinkedList<T>::Iterator SortedLinkedList<T>::getMax()
{
    return this->_sortedList->last();
}

template <class V>
std::ostream& operator<<(std::ostream& out, const SortedLinkedList<V>& sList)
{
    out << *(sList._sortedList);

    return out;
}


template <class T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T>& sList)
{
    if (this != &sList)
    {
        *(this->_sortedList) = *(sList._sortedList);
    }

    return *this;
}

template <class T>
bool SortedLinkedList<T>::operator==(const SortedLinkedList<T>& sList) const
{
    return ( *(this->_sortedList) == *(sList._sortedList) );
}

template <class T>
bool SortedLinkedList<T>::operator!=(const SortedLinkedList<T>& sList) const
{
    return ( *(this->_sortedList) != *(sList._sortedList) );
}




#endif // _SORTEDLINKEDLIST_H