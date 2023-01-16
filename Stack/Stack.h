#ifndef _STACK_H
#define _STACK_H


#include "IStack.h"

#include "../LinkedList/LinkedList.h"

template <class T>
class Stack;


template <class T>
class StackNode
{
    friend class Stack<T>;

    private:
        T _value;
        StackNode<T>* _next;

    public:
        StackNode();
        explicit StackNode(const T& value);

        T& getNodeValue();
        StackNode<T>* getNodeNext();
};

template <class T>
StackNode<T>::StackNode()
{
    this->_next = nullptr;
}

template <class T>
StackNode<T>::StackNode(const T& value)
{
    this->_next = nullptr;
    this->_value = value;
}

template <class T>
T& StackNode<T>::getNodeValue()
{
    return this->_value;
}

template <class T>
StackNode<T>* StackNode<T>::getNodeNext()
{
    return this->_next;
}


// ----------------------------------

template <class T>
class Stack : public IStack<T, StackNode<T>*>
{
    public:
        typedef typename IStack<T, StackNode<T>*>::Type Type;
        typedef typename IStack<T, StackNode<T>*>::Iterator Iterator;

    private:
        Iterator _top;
        uint32_t _size;

    public:
        Stack();
        explicit Stack(const Iterator & top);
        Stack(const Stack<T>& source);
        ~Stack();
        
        bool isEmpty() const override;
        Type peek() const override;
        void push(const Type& item) override;
        void pop() override;
        
        void write(const Type& value, uint32_t index);
        Type at(uint32_t index) const;

        Iterator end() const;
        Iterator begin() const;
        Iterator next(Iterator pos) const override;

        Type read(const Iterator pos) const;
        bool isEnd(const Iterator pos) const;

        int indexOf(const Type& value) const;

        Stack<T>& operator=(const Stack<T>& stack);
        bool operator==(const Stack<T>& stack) const;
        bool operator!=(const Stack<T>& stack) const;
};

template <class T>
Stack<T>::Stack()
{
    this->_top = nullptr;
    this->_size = 0;
}


template <class T>
Stack<T>::Stack(const Iterator& top)
{
    this->_top = &top;
    this->_size = 1;
}

template <class T>
Stack<T>::Stack(const Stack<T>& source)
{
    LinkedList<T> list;
    Iterator it = source._top;
    this->_size = 0;
    this->_top = nullptr;

    while (it)
    {
        list.unshift(it->_value);
        it = it->_next;
    }

    delete it;
    it = nullptr;

    Iterator itList = list.begin();

    while (itList)
    {
        this->push(itList->getNodeValue());
        itList = itList->getNext();
    }

    delete itList;
    itList = nullptr;
}


template <class T>
Stack<T>::~Stack()
{
    while (!this->isEmpty())
    {
        this->pop();
    }

    delete this->_top;
}


template <class T>
typename Stack<T>::Type Stack<T>::peek() const
{
    return this->_top->_value;
}


template <class T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    return this->_top;
}

template <class T>
typename Stack<T>::Type Stack<T>::read(const Iterator pos) const
{
    if (!this->isEnd(pos) && !this->isEmpty())
    {
        return pos->_value;
    }
}


template <class T>
bool Stack<T>::isEnd(const Iterator pos) const
{
    return pos == nullptr;
}


template <class T>
typename Stack<T>::Iterator Stack<T>::next(Iterator pos) const
{
    return pos->_next;
}

template <class T>
typename Stack<T>::Iterator Stack<T>::end() const
{
    Iterator it = this->begin();

    while (!this->isEnd(it))
    {
        it = this->next(it);
    }

    return it;
}


template <class T>
bool Stack<T>::isEmpty() const
{
    return (this->_top == nullptr);
}


template <class T>
void Stack<T>::pop()
{
    if (!this->isEmpty())
    {
        Iterator oldTop = this->_top;
        this->_top = oldTop->_next;
        this->_size--;

        delete oldTop;
        oldTop = nullptr;
    }
}


template <class T>
void Stack<T>::push(const Type& item)
{
    Iterator newTop = new StackNode<T>;
    newTop->_value = item;

    newTop->_next = this->_top;
    this->_top = newTop;
    this->_size++;
}

template <class T>
int Stack<T>::indexOf(const Type& value) const
{
    Iterator it = this->_top;
    int index = 0;

    while (it)
    {
        if (it->_value == value)
        {
            return index;
        }

        it = it->_next;
        index++;
    }

    return -1;
}


template <class T>
void Stack<T>::write(const Type& value, uint32_t index)
{
    if (index > 0 && index < this->_size)
    {   
        Iterator it = this->_top;
        uint32_t i = 0;

        while (it)
        {   
            if (i == index)
            {
                it->_value = value;
                return;
            }

            it = it->_next;
            i++;
        }   
    }
}


template <class T>
typename Stack<T>::Type Stack<T>::at(uint32_t index) const
{
    if (index > 0 && index < this->_size)
    {   
        Iterator it = this->_top;
        uint32_t i = 0;

        while (it)
        {   
            if (i == index)
            {
                return it->_value;
            }

            it = it->_next;
            i++;
        }   
    }
}



template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
    if (this != &stack)
    {
        this->~Stack();
        Stack<T>(stack);
    }

    return *this;
}

template <class T>
bool Stack<T>::operator==(const Stack<T>& stack) const
{
    if (stack._size != this->_size)
    {
        return false;
    }

    Iterator itCurrent = this->_top;
    Iterator itSource = stack._top;

    while (itCurrent)
    {
        if (itCurrent->_value != itSource->_value)
        {
            return false;
        }

        itCurrent = itCurrent->_next;
        itSource = itSource->_next;
    }
    
    return true;
}


template <class T>
bool Stack<T>::operator!=(const Stack<T>& stack) const
{
    if (stack._size != this->_size)
    {
        return true;
    }

    Iterator itCurrent = this->_top;
    Iterator itSource = stack._top;

    while (itCurrent)
    {
        if (itCurrent->_value == itSource->_value)
        {
            return false;
        }

        itCurrent = itCurrent->_next;
        itSource = itSource->_next;
    }
    
    return true;
}


#endif // _STACK_H