#ifndef _ARRAY_STACK_H
#define _ARRAY_STACK_H

#include "IStack.h"


/**
 * Classe che implementa la struttura dati dello Stack attraverso un array
 *
 * @tparam T: Tipo di dato memorizzato all'interno della struttura
 */
template <class T>
class ArrayStack : public IStack<T, std::size_t>
{
    public:
        typedef typename IStack<T, std::size_t>::Type Type; 
        typedef typename IStack<T, std::size_t>::Iterator Iterator; 

    private:
        static const Iterator _DEFAULT_SIZE = 16ULL; // Dimensioni di default dell'array

        Type* _array; // Array che simula uno stack
        Iterator _size; // Dimensioni dell'array
        Iterator _headIndex; // Posizione dove si puo' inserire un nuovo elemento

    public:
        ArrayStack();
        ArrayStack(Iterator size);
        ArrayStack(const ArrayStack<T>& source);
        ~ArrayStack();

        void push(const T& item) override;
        void pop() override;
        bool isEmpty() const override;

        Iterator end() const override;
        Iterator begin() const override;
        Iterator next(Iterator pos) const override;

        bool isEnd(const Iterator pos) const;
        Type read(const Iterator pos) const override;
        void write(const Type& item, const Iterator pos) const;

        Type peek() const override;
        Iterator getSize() const;
        Iterator getLength() const;

        ArrayStack<T>& operator=(const ArrayStack<T>& arrayStack);
        bool operator==(const ArrayStack<T>& arrayStack) const;
        bool operator!=(const ArrayStack<T>& arrayStack) const;
        Type& operator[](Iterator pos);
};

/**
 * Crea un'istanza della classe ArrayStack con dimensioni massime di default pari a 16
 * 
  * @tparam T : Tipo di dato da contenere
 */
template <class T>
ArrayStack<T>::ArrayStack()
{
    this->_array = new Type[this->_DEFAULT_SIZE];
    this->_size = this->_DEFAULT_SIZE;
    this->_headIndex = 0;
}

/**
 * Crea un'stanza della classe ArrayStack con dimensioni massime pari a size
 * 
  * @tparam T : Tipo di dato da contenere
 * @param size: Dimensioni massime dell'array
 */
template <class T>
ArrayStack<T>::ArrayStack(Iterator size)
{
    this->_array = new T[size];
    this->_size = size;
    this->_headIndex = 0;
}

/**
 * Costruttore di copia della classe ArrayStack
 * 
  * @tparam T : Tipo di dato da contenere
 * @param source Istanza della classe ArrayStack da copiare all'interno di una nuova istanza
 */
template <class T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& source)
{
    this->_size = source._size;
    this->_headIndex = source._headIndex;
    this->_array = new Type[source._size];

    for (Iterator it = source.begin(); it < source.getLength(); it++)
    {
        this->_array[it] = source._array[it];
    }
}

/**
 * Distruttore della classe ArrayStack
 * 
  * @tparam T : Tipo di dato da contenere
 */
template <class T>
ArrayStack<T>::~ArrayStack()
{
    delete[] this->_array;
    this->_size = 0;
    this->_headIndex = 0;
}

/**
 * Inserisce un nuovo elemento alla fine dell'array
 * 
  * @tparam T : Tipo di dato da contenere
 * @param item: Elemento da inserire
 */
template <class T>
void ArrayStack<T>::push(const T& item)
{
    if (this->_headIndex < this->_size)
    {
        uint32_t index = (this->_size - 1) - this->_headIndex;

        this->_array[index] = item;
        this->_headIndex++;
    }

}

/**
 * Elimina l'ultimo elemento inserito nello stack
 * 
 * @tparam T : Tipo di dato da contenere
 */
template <class T>
void ArrayStack<T>::pop()
{
    if (!this->isEmpty())
    {
        this->_headIndex--;
    }
}

/**
 * Verifica se la struttura dati è vuota, restituendo true se è
 * vuota, altrimenti false.
 * 
  * @tparam T : Tipo di dato da contenere
 * @return true se è vuota, altrimenti false.
 */
template <class T>
bool ArrayStack<T>::isEmpty() const
{
    return this->_headIndex == 0;
}

/**
 * Restituisce il valore contenuto nel nodo in cima allo stack
 *
 * @tparam T : Tipo di dato da contenere
 * @return Valore del nodo in cima
 */
template <class T>
typename ArrayStack<T>::Type ArrayStack<T>::peek() const
{
    return this->_array[this->_headIndex - 1];
}

/**
 * Restituisce la prima posizione dello stack
 * 
 * @tparam T : Tipo di dato da contenere
 * @return Prima posizione dello stack
 */
template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::begin() const
{
    return this->_size - this->_headIndex;
}

/**
 * Ultimo indice dello stack
 * @tparam T : Tipo di dato da contenere
 * @return Ultimo indice dello stack
 */
template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::end() const
{
    return this->_size;
}

/**
* Restituisce true se ho raggiunto la fine dello stack, altrimenti false
* @tparam T : Tipo di dato da contenere
* @return True se ho raggiunto la fine dello stack, altrimenti false
*/
template <class T>
bool ArrayStack<T>::isEnd(const Iterator pos) const
{
    return pos == this->_size;
}

/**
 * Restituisce la lunghezza massima dell'array
 *
 * @tparam T: Tipo di dato contenuto nell'array
 * @return lunghezza massima
 */
template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::getSize() const
{
    return this->_size;
}


/**
 *  Restituisce la lunghezza corrente dell'array
 *
 * @tparam T: Tipo di dato contenuto nell'array
 * @return lunghezza corrente
 */
template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::getLength() const
{
    return this->_headIndex;
}

/**
 * Restituisce l'indice successivo a pos
 *
 * @tparam T : Tipo di dato da contenere
 * @param pos : indice
 * @return Indice successivo di pos
 */
template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::next(Iterator pos) const
{
    return ++pos;
}

/**
 * Legge il valore contenuto  in pos
  * @tparam T : Tipo di dato da contenere
 * @param pos : Indice
 * @return Valore all'indice pos
 */
template <class T>
typename ArrayStack<T>::Type ArrayStack<T>::read(const Iterator pos) const
{
    if (!this->isEnd(pos) && !this->isEmpty())
    {
        return this->_array[pos];
    }
}

/**
 * Scrive un valore contenuto  in pos
  * @tparam T : Tipo di dato da contenere
 * @param pos : Indice
 */
template <class T>
void ArrayStack<T>::write(const Type& item, const Iterator pos) const
{
    if (!this->isEnd(pos) && !this->isEmpty())
    {
        this->_array[pos] = item;
    }
}



template <class T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& arrayStack)
{
    if (this != &arrayStack)
    {
        this->~ArrayStack();
        ArrayStack<T>(arrayStack);
    }

    return *this;
}

template <class T>
bool ArrayStack<T>::operator==(const ArrayStack<T>& arrayStack) const
{
    if (arrayStack._headIndex != this->_headIndex)
    {
        return false;
    }

    for (Iterator it = arrayStack.begin(); it < arrayStack.getLength(); it++)
    {
        if (this->_array[it] != arrayStack._array[it])
        {
            return false;
        }
    }
    
    return true;
}


template <class T>
bool ArrayStack<T>::operator!=(const ArrayStack<T>& arrayStack) const
{
    if (arrayStack._headIndex == this->_headIndex)
    {
        for (Iterator it = arrayStack.begin(); it < arrayStack.getLength(); it++)
        {
            if (this->_array[it] == arrayStack._array[it])
            {
                return false;
            }
        }
    }
    
    return true;
} 

template <class T>
typename ArrayStack<T>::Type& ArrayStack<T>::operator[](Iterator pos)
{
    if (pos >= 0 && pos < this->getLength())
    {
        return this->_array[pos];
    }
}


#endif // _ARRAY_STACK_H
