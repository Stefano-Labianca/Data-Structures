#ifndef _ARRAY_STACK_H
#define _ARRAY_STACK_H

#include "IStack.h"
#include "../color.hpp"


class IndexOutOfBoundException : public std::exception
{   
    private:
        std::string _msg;

    public:
        IndexOutOfBoundException(std::size_t userIndex, std::size_t maxIndex, uint32_t codeLine, const char* fileName)
        {
            std::cout << dye::red("IndexOutOfBound: Accesso con indice negativo o con indice superiore al massimo.") << std::endl;
            // this->_msg = "IndexOutOfBound: Accesso con indice negativo o con indice superiore al massimo.\n";
            // this->_msg = "Riga: " + std::to_string(codeLine) + "\n";
            this->_msg = "Riga: " + std::to_string(codeLine) + "\n";
            this->_msg += "File: " + std::string(fileName) + "\n";
            this->_msg += "Il tuo indice: " + std::to_string(userIndex) + "\n";
            this->_msg += "L'indice minimo: 0\n";
            this->_msg += "L'indice massimo: " + std::to_string(maxIndex) + "\n";
        }

        const char* what() 
        {
            return this->_msg.c_str();
        }
};



template <class T>
class ArrayStack : public IStack<T, std::size_t>
{
    public:
        typedef typename IStack<T, std::size_t>::Type Type;
        typedef typename IStack<T, std::size_t>::Iterator Iterator;

    private:
        static const Iterator _DEFAULT_SIZE = 16ULL;

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

        Type peek() const override;
        Iterator getSize() const;
        Iterator getLength() const;

        ArrayStack<T>& operator=(const ArrayStack<T>& arrayStack);
        bool operator==(const ArrayStack<T>& arrayStack) const;
        bool operator!=(const ArrayStack<T>& arrayStack) const;
        Type& operator[](Iterator pos);
};


template <class T>
ArrayStack<T>::ArrayStack()
{
    this->_array = new T[this->_DEFAULT_SIZE];
    this->_size = this->_DEFAULT_SIZE;
    this->_headIndex = 0;
}


template <class T>
ArrayStack<T>::ArrayStack(Iterator size)
{
    this->_array = new T[size];
    this->_size = size;
    this->_headIndex = 0;
}


template <class T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& source)
{
    this->_size = source._size;
    this->_headIndex = source._headIndex;
    this->_array = new T[source._size];

    for (Iterator it = source.begin(); it < source.getLength(); it++)
    {
        this->_array[it] = source._array[it];
    }
}


template <class T>
ArrayStack<T>::~ArrayStack()
{
    delete[] this->_array;
    this->_size = 0;
    this->_headIndex = 0;
}


template <class T>
void ArrayStack<T>::push(const T& item)
{
    if (this->_headIndex < this->_size)
    {
        this->_array[this->_headIndex] = item;
        this->_headIndex++;
    }

}


template <class T>
void ArrayStack<T>::pop()
{
    if (!this->isEmpty())
    {
        this->_headIndex--;
    }
}


template <class T>
bool ArrayStack<T>::isEmpty() const
{
    return this->_headIndex == 0;
}


template <class T>
typename ArrayStack<T>::Type ArrayStack<T>::peek() const
{
    return this->_array[this->_headIndex - 1];
}


template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::begin() const
{
    return 0;
}


template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::end() const
{
    return this->_headIndex - 1;
}


template <class T>
bool ArrayStack<T>::isEnd(const Iterator pos) const
{
    return pos == this->_headIndex;
}

/**
 * @brief Restituisce la lunghezza massima dell'array
 *
 * @tparam T Tipo di dato contenuto nell'array
 * @return Iterator
 */
template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::getSize() const
{
    return this->_size;
}


/**
 * @brief Restituisce la lunghezza corrente dell'array
 *
 * @tparam T Tipo di dato contenuto nell'array
 * @return Iterator
 */
template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::getLength() const
{
    return this->_headIndex;
}

template <class T>
typename ArrayStack<T>::Iterator ArrayStack<T>::next(Iterator pos) const
{
    return ++pos;
}

template <class T>
typename ArrayStack<T>::Type ArrayStack<T>::read(const Iterator pos) const
{
    if (!this->isEnd(pos) && !this->isEmpty())
    {
        return this->_array[pos];
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
        return false;
    }

    for (Iterator it = arrayStack.begin(); it < arrayStack.getLength(); it++)
    {
        if (this->_array[it] == arrayStack._array[it])
        {
            return true;
        }
    }
    
    
    return false;
}

template <class T>
typename ArrayStack<T>::Type& ArrayStack<T>::operator[](Iterator pos)
{
    try
    {
        if (pos >= 0 && pos < this->getLength())
        {
            return this->_array[pos];
        }

        throw IndexOutOfBoundException(pos, this->_headIndex, __LINE__, __FILE__);
    }

    catch (IndexOutOfBoundException e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}



#endif // _ARRAY_STACK_H
