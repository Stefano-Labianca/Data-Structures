#ifndef ISET_H
#define ISET_H

#include "ISet.h"
#include "../SortedLinkedList/SortedLinkedList.h"

/**
 * Classe che implementa gli insiemi tramite liste ordinate
 *
 * @tparam T: Tipo di dato da contenere nell'insieme
 */
template <class T>
class Set : public ISet<T, LinkedNode<T>*>
{
    public:
        typedef typename ISet<T, LinkedNode<T>*>::Iterator Iterator;
        typedef typename ISet<T, LinkedNode<T>*>::Type Type;

    private:
        SortedLinkedList<T>* _set;

    public:
        Set();
        Set(const Set<T>& set);
        ~Set();

        bool isEmpty() const;
        bool contains(const Type& needle) const;
        void add(const Type& needle);
        void remove(const Type& needle);

        Set<Type> unions(const Set<Type>& set);
        Set<Type> intersection(const Set<Type>& set);
        Set<Type> difference(const Set<Type>& set);

        bool isSubset(const Set<Type>& subSet);
        uint32_t size() const;

        template <class V>
        friend std::ostream& operator<<(std::ostream& out, const Set<V>& set);

        Set<T>& operator=(const Set<T>& set);
        bool operator==(const Set<T>& set) const;
        bool operator!=(const Set<T>& set) const;

};


/**
 * Costrutisce un insieme vuoto
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
Set<T>::Set()
{
    this->_set = new SortedLinkedList<T>();
}

/**
 * Costrutisce di copia
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
Set<T>::Set(const Set<T>& set)
{
    this->_set = new SortedLinkedList<T>( *(set._set) );
}

/**
 * Distruttore
 *
 * @tparam T: Tipo della lista e dei nodi
 */
template <class T>
Set<T>::~Set()
{
    this->_set->~SortedLinkedList();
}

/**
 * Verifica se un insieme e' vuoto, restituendo true, altrimenti false
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Restituisce true se e' vuoto, altrimenti false
 */
template <class T>
bool Set<T>::isEmpty() const
{
    return this->_set->isEmpty();
}


/**
 * Restituisce la cardinalita' dell'insieme.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @return Cardinalita' dell'insieme
 */
template <class T>
uint32_t Set<T>::size() const
{
    return this->_set->getSize();
}


/**
 * Cerca un elemento all'interno dell'insieme, restituendo true se e' contenuto, altrimenti false
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param needle: Valore da cercare
 * @return True se l'elemento e' contenuto, altrimenti false.
 */
template <class T>
bool Set<T>::contains(const Type& needle) const
{
    return (this->_set->find(needle));
}


/**
 * Aggiunge un elemento all'interno dell'insieme, se e' gia' presente non viene inserito.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param needle: Elemento da aggiungere
 */
template <class T>
void Set<T>::add(const Type& needle)
{
    if (!this->contains(needle))
    {
        this->_set->add(needle);
    }
}


/**
 * Rimuove un elemento dall'insieme se presente.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param needle: Elemento da eliminare
 */
template <class T>
void Set<T>::remove(const Type& needle)
{
    Iterator obj = this->_set->find(needle);

    if (obj)
    {
        this->_set->remove(obj);
    }
}


/**
 * Attua l'operazione insiemistica dell'unione fra l'insieme A (this) e l'insieme B (set), restituendoci
 * l'insieme contentente gli elementi contenuti in A o in B
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param set: Insieme B
 * @return Insieme unione A, B
 */
template <class T>
Set<typename Set<T>::Type> Set<T>::unions(const Set<Type>& set)
{
    Set<T> uSet = Set<T>();

    Iterator thisIt = this->_set->getMin();
    Iterator setIt = set._set->getMin();

    while (!this->_set->isEnd(thisIt) && !set._set->isEnd(setIt))
    {
        if (thisIt->getNodeValue() == setIt->getNodeValue())
        {
            uSet._set->add(thisIt->getNodeValue());

            thisIt = thisIt->getNext();
            setIt = setIt->getNext();
        }

        else if (thisIt->getNodeValue() < setIt->getNodeValue())
        {
            uSet._set->add(thisIt->getNodeValue());
            thisIt = thisIt->getNext();
        }

        else
        {
            uSet._set->add(setIt->getNodeValue());
            setIt = setIt->getNext();
        }
    }

    while (!this->_set->isEnd(thisIt))
    {
        uSet._set->add(thisIt->getNodeValue());
        thisIt = thisIt->getNext();
    }

    while(!set._set->isEnd(setIt))
    {
        uSet._set->add(setIt->getNodeValue());
        setIt = setIt->getNext();
    }

    return uSet;
}


/**
 * Attua l'operazione insiemistica dell'intersezione fra l'insieme A (this) e l'insieme B (set), restituendoci
 * l'insieme contentente gli elementi comuni fra A e B
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param set: Insieme B
 * @return Insieme intersezione A, B
 */
template <class T>
Set<typename Set<T>::Type> Set<T>::intersection(const Set<Type>& set)
{
    Set<T> iSet = Set<T>();
    Iterator thisIt = this->_set->getMin();
    Iterator setIt = set._set->getMin();

    while (!this->_set->isEnd(thisIt) && !set._set->isEnd(setIt))
    {
        if (thisIt->getNodeValue() == setIt->getNodeValue())
        {
            iSet._set->add(thisIt->getNodeValue());

            thisIt = thisIt->getNext();
            setIt = setIt->getNext();
        }

        else if (thisIt->getNodeValue() < setIt->getNodeValue())
        {
            thisIt = thisIt->getNext();
        }

        else
        {
            setIt = setIt->getNext();
        }
    }

    return iSet;
}


/**
 * Attua l'operazione di differenza insiemistica fra l'insieme A (this) e l'insieme B (set), restituendoci
 * un insieme contenente tutti gli elementi di A che non sono contenuti in B.
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param set: Insieme B
 * @return Insieme differenza A, B
 */
template <class T>
Set<typename Set<T>::Type> Set<T>::difference(const Set<Type>& set)
{
    Set<T> dSet = Set<T>();
    Iterator thisIt = this->_set->getMin();
    Iterator setIt = set._set->getMin();

    while (!this->_set->isEnd(thisIt) && !set._set->isEnd(setIt))
    {
        if (thisIt->getNodeValue() < setIt->getNodeValue())
        {
            dSet._set->add(thisIt->getNodeValue());
            thisIt = thisIt->getNext();
        }

        else
        {
            if (thisIt->getNodeValue() == setIt->getNodeValue())
            {
                thisIt = thisIt->getNext();
            }

            setIt = setIt->getNext();
        }
    }

    while (!this->_set->isEnd(thisIt))
    {
        dSet._set->add(thisIt->getNodeValue());
        thisIt = thisIt->getNext();
    }

    return dSet;
}


/**
 * Determina se un insime A (subSet) e' sottoinsieme di B (this), sfruttando la seguente proprieta':
 *
 * Un insieme A e' sottoinsieme di B se e solo se, la cardinalita' dell'insieme intersezione A, B e' uguale
 * alla cardinalita' dell'insieme A.
 *
 * Restituisce true se A e' sottoinsieme di B, altrimenti false
 *
 * @tparam T: Tipo della lista e dei nodi
 * @param subSet: Insieme da verificare se e' sottoinsieme di this
 * @return Restituisce true se A e' sottoinsieme di B, altrimenti false
 */
template <class T>
bool Set<T>::isSubset(const Set<Type>& subSet)
{
    Set<T> iSet = this->intersection(subSet);
    uint32_t cardinality = iSet.size();

    return (this->size() == cardinality);
}



template <class V>
std::ostream& operator<<(std::ostream& out, const Set<V>& set)
{
    out << *(set._set);

    return out;
}


template <class T>
Set<T>& Set<T>::operator=(const Set<T>& set)
{
    if (this != &set)
    {
        *(this->_set) = *(set._set);
    }

    return *this;
}


template <class T>
bool Set<T>::operator==(const Set<T>& set) const
{
    return ( *(this->_set) == *(set._set) );
}


template <class T>
bool Set<T>::operator!=(const Set<T>& set) const
{
    return ( *(this->_set) != *(set._set) );
}




#endif // ISET_H