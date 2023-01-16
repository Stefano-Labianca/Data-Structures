#ifndef _SORTEDLINKEDLIST_H
#define _SORTEDLINKEDLIST_H

#include "../LinkedList/LinkedList.h"
#include "ISortedLinkedList.h"

/**
 * Struttura dati che realizza le liste concatenate ordinate in ordine crescente.
 *
 * @tparam T: Tipo della lista
 */
template <class T>
class SortedLinkedList : public ISortedLinkedList<T, LinkedNode<T>*>
{
    public:
        typedef typename ISortedLinkedList<T, LinkedNode<T>*>::Iterator Iterator;
        typedef typename ISortedLinkedList<T, LinkedNode<T>*>::Type Type;

    private:
        LinkedList<T>* _sortedList; // Puntatore alla testa della lista ordinata

    public:
        SortedLinkedList();
        SortedLinkedList(const T& value);
        SortedLinkedList(const SortedLinkedList<T>& otherList);
        ~SortedLinkedList();

        uint32_t getSize() const;
        bool isEmpty() const;
        bool isEnd(Iterator it) const;

        void add(const T& value);

        void remove(uint32_t index);
        void remove(Iterator pos);

        Iterator getMin();
        Iterator getMax();

        Iterator find(uint32_t index);
        Iterator find(const T& needle);

        Iterator begin() const;
        Iterator last() const;


        template <class V>
        friend std::ostream& operator<<(std::ostream& out, const SortedLinkedList<V>& sList);

        SortedLinkedList<T>& operator=(const SortedLinkedList<T>& sList);
        bool operator==(const SortedLinkedList<T>& sList) const;
        bool operator!=(const SortedLinkedList<T>& sList) const;
};


/**
 * Crea una lista ordinata vuota
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
SortedLinkedList<T>::SortedLinkedList()
{
    this->_sortedList = new LinkedList<T>();
}

/**
 * Crea una lista ordinata con un valore value in testa
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param value: Valore iniziale
 */
template <class T>
SortedLinkedList<T>::SortedLinkedList(const T& value)
{
    this->_sortedList = new LinkedList<T>(value);
}

/**
 * Costruttore di copia
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param otherList: Lista ordinata da copiare
 */
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

/**
 * Distruttore
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
SortedLinkedList<T>::~SortedLinkedList()
{
    this->_sortedList->~LinkedList();
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
 * Rimuove un nodo pos dalla lista
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param pos: Puntatore del nodo da rimuovere
 */
template <class T>
void SortedLinkedList<T>::remove(Iterator pos)
{
    this->_sortedList->remove(pos);
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
 * Restituisce il puntatore del nodo contenente il valore needle. Se non viene trovato viene restituito
 * nullptr.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param needle: Valore del nodo da cercare
 * @return Puntatore al nodo con valore needle o nullptr
 */
template <class T>
typename SortedLinkedList<T>::Iterator SortedLinkedList<T>::find(const T& needle)
{
    Iterator it = this->_sortedList->begin();

    while (!this->_sortedList->isEnd(it))
    {
       if (it->getNodeValue() == needle)
       {
           return it;
       }

       it = it->getNext();
    }

    return nullptr;
}



/**
 * Restituisce true se ho raggiunto la fine della lista, altrimenti false
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param it: Posizione da verificare
 * @return Valore booleano pari a true se ho raggiunto la fine della lista, altrimenti false.
 */
template <class T>
bool SortedLinkedList<T>::isEnd(Iterator it) const
{
    return this->_sortedList->isEnd(it);
}

/**
* Restituisce la testa della lista, cioe' il primo elemento
*
* @tparam T: Tipo della lista e dei nodi
* @return Puntatore al primo nodo della lista
*/
template <class T>
typename SortedLinkedList<T>::Iterator SortedLinkedList<T>::begin() const
{
    return this->_sortedList->begin();
}

/**
 * Restituisce la coda della lista, cioe' l'ultimo elemento
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Puntatore all'ultimo nodo della lista
 */
template <class T>
typename SortedLinkedList<T>::Iterator SortedLinkedList<T>::last() const
{
    this->_sortedList->begin();
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
