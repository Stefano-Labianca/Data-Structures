#ifndef _QUEUE_H
#define _QUEUE_H

#include "./IQueue.h"


template <class T>
class Queue;


template <class T>
class QueueNode
{
    private:
        T _value;
        QueueNode<T>* _next;
    
    public:
        friend class Queue<T>;

        QueueNode();
        QueueNode(const T& value);
        
        T getValue() const;
        void setValue(const T& value);
};

template <class T>
QueueNode<T>::QueueNode()
{
    this->_next = nullptr;
}


template <class T>
QueueNode<T>::QueueNode(const T& value)
{
    this->_next = nullptr;
    this->_value = value;
}


template <class T>
T QueueNode<T>::getValue() const
{
    return this->_value;
}

template <class T>
void QueueNode<T>::setValue(const T& value)
{
    this->_value = value;
}


template <class T>
class Queue : public IQueue<T, QueueNode<T>*>
{   
    public:
        typedef typename IQueue<T, QueueNode<T>*>::Type Type;
        typedef typename IQueue<T, QueueNode<T>*>::Iterator Iterator;

    private:
        Iterator _front; // Puntatore elemento in testa alla coda
        Iterator _back; // Puntatore elemento in fondo alla coda 
        std::size_t _len; // Lunghezza della coda

    public:
        Queue();
        Queue(const Queue<T>& source);
        ~Queue();

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

        Queue<T>& operator=(const Queue<T>& queue);
        bool operator==(const Queue<T>& queue) const;
        bool operator!=(const Queue<T>& queue) const;
};

template <class T>
Queue<T>::Queue()
{
    this->_front = nullptr;
    this->_back = nullptr;
    this->_len = 0;
}

template <class T>
Queue<T>::~Queue()
{
    // Ciclo di cancellazione dei nodi
    while (!this->isEmpty())
    {
        this->dequeue();
    }

    delete this->_front;
    this->_front = nullptr;
}


template <class T>
Queue<T>::Queue(const Queue<T>& source)
{
    this->_front = nullptr;
    this->_back = nullptr;
    this->_len = 0;

    if (!source.isEmpty())
    {
        Iterator it = source._front;
        
        while (!this->isEnd(it))
        {
            this->enqueue(it->_value);
            it = it->_next;
        }
    }
}


template <class T>
bool Queue<T>::isEmpty() const
{
    return (this->_len == 0);
}


template <class T>
std::size_t Queue<T>::getLength() const
{
    return this->_len;
}


template <class T>
typename Queue<T>::Type Queue<T>::read(const Iterator pos) const
{
    if (pos)
    {
        return pos->getValue();
    }
}

template <class T>
void Queue<T>::write(const Type& item, Iterator pos)
{
    pos->setValue(item);
}

template <class T>
void Queue<T>::enqueue(const Type& item)
{
    Iterator node = new QueueNode<T>;
    node->setValue(item);
    node->_next = nullptr;

    if (this->isEmpty())
    {
        this->_front = node;
    }

    else
    {
        this->_back->_next = node;
    }

    this->_back = node;
    this->_len++;
}

template <class T>
void Queue<T>::dequeue()
{
    if (!this->isEmpty())
    {
        Iterator oldFront = this->_front;
        this->_front = oldFront->_next;

        delete oldFront;
        oldFront = nullptr;

        this->_len--;

        if (this->_len == 0)
        {
            this->_back = nullptr;
        }
    }
}

template <class T>
typename Queue<T>::Type Queue<T>::top() const
{
    return this->_front->_value;
}


template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return this->_front;
}


template <class T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return this->_back;
}


template <class T>
bool Queue<T>::isEnd(const Iterator& pos) const
{
    return (pos == nullptr);
}


template <class T>
typename Queue<T>::Iterator Queue<T>::next(Iterator& pos) const
{
    return pos->_next;
}


template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
    if (this == &queue)
    {
        this->~Queue();

        this->_front = nullptr;
        this->_back = nullptr;
        this->_len = 0;

        if (!queue.isEmpty())
        {
            Iterator it = queue._front;
            
            while (!this->isEnd(it))
            {
                this->enqueue(it->_value);
                it = it->_next;
            }
        }
    }

    return *this;
}


template <class T>
bool Queue<T>::operator==(const Queue<T>& queue) const
{
    if (this->_len != queue._len)
    {
        return false;
    }

    Iterator thisIt = this->begin();
    Iterator sourceIt = queue.begin();

    while (!this->isEnd(thisIt))
    {
        if (thisIt->_value != sourceIt->_value)
        {
            return false;
        }

        thisIt = thisIt->_next;
        sourceIt = sourceIt->_next;
    }
    

    return true;
}


template <class T>
bool Queue<T>::operator!=(const Queue<T>& queue) const
{
    if (this->_len == queue._len)
    {
        return false;
    }

    Iterator thisIt = this->begin();
    Iterator sourceIt = queue.begin();

    while (!this->isEnd(thisIt))
    {
        if (thisIt->_value == sourceIt->_value)
        {
            return false;
        }

        thisIt = thisIt->_next;
        sourceIt = sourceIt->_next;
    }
    

    return true;
}



#endif // _QUEUE_H