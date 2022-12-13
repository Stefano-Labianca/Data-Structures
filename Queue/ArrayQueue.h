#ifndef _ARRAY_QUEUE_H
#define _ARRAY_QUEUE_H

#include "./IQueue.h"

template <class T>
class ArrayQueue : public IQueue<T, std::size_t>
{
    public: 
        typedef typename IQueue<T, std::size_t>::Type Type;
        typedef typename IQueue<T, std::size_t>::Iterator Iterator;

    private:    
        std::size_t _DEFAULT_SIZE = 16ULL; // Lunghezza massima di default della coda
        std::size_t _length; // Lunghezza massima della coda
        std::size_t _currentSize; // Indica il numero di elementi presenti nella coda
        Type* _circularArray; // Array che simula la coda
        std::size_t _headIndex; // Indice dell'elemento in testa alla coda


    public:
        ArrayQueue();
        ArrayQueue(Iterator size);
        ArrayQueue(Iterator size, Iterator start);
        ArrayQueue(const ArrayQueue<T>& source);
        ~ArrayQueue();

        bool isEmpty() const;
        std::size_t getLength() const;

        Type read(const Iterator pos) const;
        void write(const Type& item, Iterator pos);

        void enqueue(const Type& item);
        void dequeue();
        Type top() const;

        Iterator begin() const;
        Iterator end() const;
        bool isEnd(const Iterator& pos) const;
        Iterator next(Iterator& pos) const;

        ArrayQueue<T>& operator=(const ArrayQueue<T>& arrayQueue);
        bool operator==(const ArrayQueue<T>& arrayQueue) const;
        bool operator!=(const ArrayQueue<T>& arrayQueue) const;
};

template <class T>
ArrayQueue<T>::ArrayQueue()
{
    this->_circularArray = new Type[this->_DEFAULT_SIZE];
    this->_length = this->_DEFAULT_SIZE;
    this->_headIndex = 0;
    this->_currentSize = 0;
}


template <class T>
ArrayQueue<T>::ArrayQueue(Iterator size)
{
    if (size == 0)
    {
        this->_circularArray = new Type[this->_DEFAULT_SIZE];
        this->_length = this->_DEFAULT_SIZE;
    }

    else
    {
        this->_circularArray = new Type[size];
        this->_length = size;
    }

    this->_headIndex = 0;
    this->_currentSize = 0;
}

template <class T>
ArrayQueue<T>::ArrayQueue(Iterator size, Iterator start)
{
    if (start > size)
    {
        this->_circularArray = new Type[this->_DEFAULT_SIZE];
        this->_length = this->_DEFAULT_SIZE;
        this->_headIndex = 0;
    }


    else
    {
        this->_circularArray = new Type[size];
        this->_length = size;
        this->_headIndex = start;
    }

    this->_currentSize = 0;
}



template <class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& source)
{
    this->_length = source._length;
    this->_headIndex = source._headIndex;
    this->_circularArray = new Type[source._length];
    this->_currentSize = source._currentSize;

    for (std::size_t i = (this->_headIndex % this->_length); i < this->_currentSize; i++)
    {
        this->_circularArray[i] = source._circularArray[i];
    }
}


template <class T>
ArrayQueue<T>::~ArrayQueue()
{
    delete[] this->_circularArray;
    this->_circularArray = nullptr;
    this->_length = 0;
    this->_headIndex = 0;
}

template <class T>
bool ArrayQueue<T>::isEmpty() const
{
    return (this->_length == 0);
}


template <class T>
std::size_t ArrayQueue<T>::getLength() const
{
    return this->_length;
}


template <class T>
typename ArrayQueue<T>::Type ArrayQueue<T>::read(const Iterator pos) const
{
    if (pos >= 0 && pos <= this->_length - 1)
    {
        return this->_circularArray[pos];
    }
}


template <class T>
void ArrayQueue<T>::write(const Type& item, Iterator pos)
{
    if (pos >= 0 && pos <= this->_length - 1)
    {
        this->_circularArray[pos] = item;
    }
}


template <class T>
void ArrayQueue<T>::enqueue(const Type& item)
{
    std::size_t index = (this->_headIndex + this->_currentSize) % this->_length;
    this->_circularArray[index] = item;
    this->_currentSize++;
}


template <class T>
void ArrayQueue<T>::dequeue()
{
    if (!this->isEmpty())
    {
        this->_headIndex = (this->_headIndex + 1) % this->_length;
        this->_currentSize--;
    }
}


template <class T>
typename ArrayQueue<T>::Type ArrayQueue<T>::top() const
{
    return this->_circularArray[this->_headIndex];
}


template <class T>
typename ArrayQueue<T>::Iterator ArrayQueue<T>::begin() const
{
    return this->_headIndex;
}


template <class T>
typename ArrayQueue<T>::Iterator ArrayQueue<T>::end() const
{
    return (this->_headIndex + this->_currentSize - 1) % this->_length;
}


template <class T>
bool ArrayQueue<T>::isEnd(const Iterator& pos) const
{
    return pos == (this->_headIndex + this->_currentSize) % this->_length;
}


template <class T>
typename ArrayQueue<T>::Iterator ArrayQueue<T>::next(Iterator& pos) const
{
    return (++pos % this->_length);
}



template <class T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& arrayQueue)
{
    if (this != &arrayQueue)
    {
        this->~ArrayQueue();    
        ArrayQueue<T>(arrayQueue);
    }

    return *this;
}

template <class T>
bool ArrayQueue<T>::operator==(const ArrayQueue<T>& arrayQueue) const
{   
    if (arrayQueue._headIndex != this->_headIndex)
    {
        return false;
    }

    for (Iterator it = arrayQueue.begin(); it < arrayQueue._currentSize; it++)
    {
        if (this->_circularArray[it] != arrayQueue._circularArray[it])
        {
            return false;
        }
    }

    return true;
}

template <class T>
bool ArrayQueue<T>::operator!=(const ArrayQueue<T>& arrayQueue) const
{
    if (arrayQueue._headIndex == this->_headIndex)
    {
        for (Iterator it = arrayQueue.begin(); it < arrayQueue._currentSize; it++)
        {
            if (this->_circularArray[it] == arrayQueue._circularArray[it])
            {
                return false;
            }
        }
    }

    return true;
}



#endif // _ARRAT_QUEUE_H