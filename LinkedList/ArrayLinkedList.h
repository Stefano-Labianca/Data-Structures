#ifndef _ARRAYLINKEDLIST_H
#define _ARRAYLINKEDLIST_H

#include "ILinkedList.h"

/**
 * Rappresentazione della lista con gli array
 *
 * @tparam T: Tipo della lista
 */
template <class T>
class ArrayLinkedList : public ILinkedList<T, std::size_t>
{
    public:
        typedef typename ILinkedList<T, std::size_t>::Type Type;
        typedef typename ILinkedList<T, std::size_t>::Iterator Iterator;

    public:
        std::size_t _DEFAULT_ARR_SIZE = 16ULL; // Lunghezza massima di default della lista

        std::size_t _length; // Lunghezza massima della lista
        std::size_t _currentSize; // Indica il numero di elementi presenti nella lista
        Type* _arrayList; // Array che simula la lista

    private:
        void _increaseMaxLen();

    public:
        ArrayLinkedList();
        ArrayLinkedList(Iterator size);
        ArrayLinkedList(const ArrayLinkedList<T>& source);
        ~ArrayLinkedList();

        Iterator getSize() const;
        Iterator getMaxSize() const;
        bool isEmpty() const;

        int find(const Type& needle) const;

        void insert(const Type& value, Iterator index);
        void remove(Iterator index);

        void unshift(const Type& value);
        void append(const Type& value);

        void shift();
        void deleteLast();

        Iterator begin() const;
        Iterator last() const;
        bool isEnd(Iterator it) const;


        template <class V>
        friend std::ostream& operator<<(std::ostream& out, const ArrayLinkedList<V>& set);

        ArrayLinkedList<T>& operator=(const ArrayLinkedList<Type>& arrayList);
        bool operator==(const ArrayLinkedList<Type>& arrayList) const;
        bool operator!=(const ArrayLinkedList<Type>& arrayList) const;
        Type& operator[](Iterator pos);
};

/**
 * Crea una lista vuota con dimensioni pari a quelle di default (16)
 *
 * @tparam T: Tipo della lista
 */
template <class T>
ArrayLinkedList<T>::ArrayLinkedList()
{
    this->_arrayList = new Type[this->_DEFAULT_ARR_SIZE];
    this->_length = this->_DEFAULT_ARR_SIZE;
    this->_currentSize = 0;
}

/**
 * Crea una lista vuota con dimensioni custom pari a size.
 * Se size e' uguale a zero, allora la lista avra' dimensioni di default (16)
 *
 * @tparam T: Tipo della lista
 * @param size : Dimensioni della lista
 */
template <class T>
ArrayLinkedList<T>::ArrayLinkedList(Iterator size)
{
    if (size == 0)
    {
        this->_arrayList = new Type[this->_DEFAULT_ARR_SIZE];
        this->_length = this->_DEFAULT_ARR_SIZE;
    }

    else
    {
        this->_arrayList = new Type[size];
        this->_length = size;
    }

    this->_currentSize = 0;
}

/**
 * Costuttore di copia
 *
 * @tparam T: Tipo della lista
 * @param otherList : Lista da copiare
 */
template <class T>
ArrayLinkedList<T>::ArrayLinkedList(const ArrayLinkedList<T>& source)
{
    this->_length = source._length;
    this->_currentSize = source._currentSize;
    this->_arrayList = new Type[source._length];

    for (std::size_t i = 0; i < this->_currentSize; i++)
    {
        this->_arrayList[i] = source._arrayList[i];
    }
}

/**
 * Distruttore
 *
 * @tparam T: Tipo della lista
 */
template <class T>
ArrayLinkedList<T>::~ArrayLinkedList()
{
    delete[] this->_arrayList;
    this->_arrayList = nullptr;

    this->_length = 0;
    this->_currentSize = 0;
}

/**
 * Restituisce true se la lista e' vuota, altrimenti false
 *
 * @tparam T: Tipo di dato della lista
 * @return True se la lista e' vuota, altrimenti false
 */
template <class T>
bool ArrayLinkedList<T>::isEmpty() const
{
    return (this->_currentSize == 0);
}

/**
 * Restituisce le dimensioni effettive della lista, ovvero il numero di elementi
 * contenuti in essa.
 *
 * @tparam T: Tipo di dato della lista
 * @return Numero di elementi della lista
 */
template <class T>
typename ArrayLinkedList<T>::Iterator ArrayLinkedList<T>::getSize() const
{
    return this->_currentSize;
}

/**
 * Restituisce la capacita' massima della lista, ovvero il numero massimo di elementi che
 * puo' contenere
 *
 * @tparam T: Tipo di dato della lista
 * @return Capacita' della lista
 */
template <class T>
typename ArrayLinkedList<T>::Iterator ArrayLinkedList<T>::getMaxSize() const
{
    return this->_length;
}

/**
 * Cerca e restituisce la posizione dell'elemento needle all'interno della lista.
 * Se non e' presente viene restituito -1.
 *
 * @tparam T: Tipo di dato della lista
 * @param needle: Elemento da cercare nella lista
 * @return Posizione dell'elemento se trovato, altrimenti -1
 */
template <class T>
int ArrayLinkedList<T>::find(const Type& needle) const
{
    for (int i = 0; i < this->_currentSize; i++)
    {
        if (this->_arrayList[i] == needle)
        {
            return i;
        }
    }

    return -1;
}

/**
 * Aggiunge un elemento dalla lista che si trova in posizione index.
 *
 * @tparam T: Tipo di dato della lista
 * @param index: Indice dell'elemento da inserire
 */
template <class T>
void ArrayLinkedList<T>::insert(const Type& value, Iterator index)
{
    if (this->isEmpty())
    {
        this->_arrayList[index] = value;
        this->_currentSize++;

        return;
    }

    if (index == 0)
    {
        this->unshift(value);
        return;
    }

    if ((index == this->_currentSize) || (index >= this->_currentSize))
    {
        this->append(value);
        return;
    }

    if (this->_currentSize < this->_length)
    {
        for (int i = this->_currentSize; i >= (int)index; i--)
        {
            this->_arrayList[i + 1] = this->_arrayList[i];
        }

        this->_arrayList[index] = value;
        this->_currentSize++;
    }
}

/**
 * Rimuove un elemento dalla lista che si trova in posizione index.
 *
 * @tparam T: Tipo di dato della lista
 * @param index: Indice dell'elemento da eliminare
 */
template <class T>
void ArrayLinkedList<T>::remove(Iterator index)
{
    if (this->isEmpty())
    {
        return;
    }

    if (index == 0)
    {
        this->shift();
        return;
    }

    if ((index == this->_currentSize - 1) || (index >= this->_currentSize))
    {
        this->deleteLast();
        return;
    }

    if (this->_currentSize < this->_length && !this->isEmpty())
    {
        for (int i = index; i < (int) this->_currentSize; i++)
        {
            this->_arrayList[i] = this->_arrayList[i + 1];
        }

        this->_currentSize--;
    }
}

/**
 * Aggiunge un elemento all'inizio della lista. In caso non ci sia spazio, viene aumentata la
 * lunghezza della lista
 *
 * @tparam T: Tipo di dato della lista
 * @param value: Elemento da inserire
 */
template <class T>
void ArrayLinkedList<T>::unshift(const Type& value)
{
    if (this->_currentSize + 1 > this->_length)
    {
        this->_increaseMaxLen();
    }

    for (int i = this->_currentSize; i >= 0; i--)
    {
        this->_arrayList[i + 1] = this->_arrayList[i];
    }

    this->_arrayList[0] = value;
    this->_currentSize++;
}

/**
 * Aggiunge un elemento alla fine della lista. In caso non ci sia spazio, viene aumentata la
 * lunghezza della lista
 *
 * @tparam T: Tipo di dato della lista
 * @param value: Elemento da inserire
 */
template <class T>
void ArrayLinkedList<T>::append(const Type& value)
{
    if (this->_currentSize + 1 > this->_length)
    {
        this->_increaseMaxLen();
    }

    this->_arrayList[this->_currentSize] = value;
    this->_currentSize++;
}

/**
 * Elimina il primo elemento della lista
 *
 * @tparam T: Tipo di dato della lista
 */
template <class T>
void ArrayLinkedList<T>::shift()
{
    if (this->isEmpty())
    {
        return;
    }

    for (int i = 0; i < (int) this->_currentSize; i++)
    {
        this->_arrayList[i] = this->_arrayList[i + 1];
    }

    this->_currentSize--;
}

/**
 * Rimuove l'ultimo elemento inserito nella lista.
 *
 * @tparam T: Tipo di dato della lista
 */
template <class T>
void ArrayLinkedList<T>::deleteLast()
{
    if (this->isEmpty())
    {
        return;
    }

    this->_currentSize--;
}


/**
 * Restituisce la posizione del primo elemento
 *
 * @tparam T: : Tipo di dato della lista
 * @return Posizione del primo elemento
 */
template <class T>
typename ArrayLinkedList<T>::Iterator ArrayLinkedList<T>::begin() const
{
    return 0;
}

/**
 * Restituisce la posizione dell'ultimo elemento inserito
 *
 * @tparam T: Tipo di dato della lista
 * @return Posizione dell'ultimo elemento inserito
 */
template <class T>
typename ArrayLinkedList<T>::Iterator ArrayLinkedList<T>::last() const
{
    return this->_currentSize - 1;
}

/**
 * Restituisce true se ho raggiunto una posizione maggiore o uguale alla lunghezza della lista, altrimenti
 * restituisce false.
 *
 * @tparam T: Tipo di dato contenuto
 * @param it: Indice da controllare
 * @return True se ho superato la lunghezza massima della lista, altrimenti false
 */
template <class T>
bool ArrayLinkedList<T>::isEnd(Iterator it) const
{
    return (it >= this->_length);
}

/**
 * Aumenta la lunghezza della lista di un fattore doppio rispetto alla lunghezza precedente.
 *
 *      newLen = currentLen * 2
 *
 * @tparam T: Tipo contenuto nella lista
 */
template <class T>
void ArrayLinkedList<T>::_increaseMaxLen()
{
    Type* newArray = new Type[this->_length * 2];

    for (int i = 0; i < this->_currentSize; i++)
    {
        newArray[i] = this->_arrayList[i];
    }

    delete[] this->_arrayList;
    this->_arrayList = nullptr;

    this->_arrayList = newArray;
    this->_length *= 2;
}

template <class V>
std::ostream& operator<<(std::ostream& out, const ArrayLinkedList<V>& aList)
{
    out << "[ ";

    for (int i = 0; i < aList.getSize(); i++)
    {
        if (i == aList.last())
        {
            out << aList._arrayList[i];
        }

        else
        {
            out << aList._arrayList[i] << ", ";
        }
    }

    out << " ]" << std::endl;

    return out;
}

template <class T>
ArrayLinkedList<T>& ArrayLinkedList<T>::operator=(const ArrayLinkedList<Type>& arrayList)
{
    if (this != &arrayList)
    {
        this->~ArrayLinkedList();
        ArrayLinkedList<T>(arrayList);
    }

    return *this;
}

template <class T>
bool ArrayLinkedList<T>::operator==(const ArrayLinkedList<Type>& arrayList) const
{
    if (this->_currentSize != arrayList._currentSize)
    {
        return false;
    }

    if (this->_length != arrayList._length)
    {
        return false;
    }


    for (std::size_t i = 0; i < this->_currentSize; i++)
    {
        if (this->_arrayList[i] != arrayList._arrayList[i])
        {
            return false;
        }
    }

    return true;
}

template <class T>
bool ArrayLinkedList<T>::operator!=(const ArrayLinkedList<Type>& arrayList) const
{
    if (this->_currentSize != arrayList._currentSize)
    {
        return true;
    }

    if (this->_length != arrayList._length)
    {
        return true;
    }


    for (std::size_t i = 0; i < this->_currentSize; i++)
    {
        if (this->_arrayList[i] != arrayList._arrayList[i])
        {
            return true;
        }
    }

    return false;
}

template <class T>
typename ArrayLinkedList<T>::Type& ArrayLinkedList<T>::operator[](Iterator pos)
{
    if (pos >= 0 && pos < this->getSize())
    {
        return this->_arrayList[pos];
    }
}



#endif // _ARRAYLINKEDLIST_H
