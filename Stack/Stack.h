#ifndef _STACK_H
#define _STACK_H


#include "IStack.h"
#include <exception>

#include "../LinkedList/LinkedList.h"

template <class T>
class Stack;

// TODO: Aggiungere eccezioni custom


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
    private:
        StackNode<T>* _top;
        uint32_t _size;

    public:
        Stack();
        explicit Stack(const StackNode<T>& top);
        Stack(const Stack<T>& source);
        ~Stack();
        
        bool isEmpty() const override;
        T peek() const override;
        void push(const T& item) override;
        StackNode<T>* pop() override;
        
        void write(const T& value, uint32_t index);
        T read(uint32_t index) const;

        StackNode<T>* getTopNode() const;
        int indexOf(const T& value) const;

        Stack<T>& operator=(const Stack<T>& stack);
        bool operator==(const Stack<T>& stack) const;

};

template <class T>
Stack<T>::Stack()
{
    this->_top = nullptr;
    this->_size = 0;
}


template <class T>
Stack<T>::Stack(const StackNode<T>& top)
{
    this->_top = &top;
    this->_size = 1;
}

template <class T>
Stack<T>::Stack(const Stack<T>& source)
{
    LinkedList<T> list;
    StackNode<T>* it = source._top;
    this->_size = 0;
    this->_top = nullptr;

    while (it)
    {
        list.unshift(it->_value);
        it = it->_next;
    }

    delete it;

    Node<T>* itList = list.begin();

    while (itList)
    {
        this->push(itList->getNodeValue());
        itList = itList->getNext();
    }

    delete itList;
}


template <class T>
Stack<T>::~Stack()
{
    while (!this->isEmpty())
    {
        delete this->pop();
    }
}


template <class T>
T Stack<T>::peek() const
{
    return this->_top->_value;
}


template <class T>
StackNode<T>* Stack<T>::getTopNode() const
{
    return this->_top;
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return (this->_top == nullptr);
}


template <class T>
StackNode<T>* Stack<T>::pop()
{
    if (!this->isEmpty())
    {
        StackNode<T>* oldTop = this->_top;
        this->_top = oldTop->_next;

        this->_size--;

        return oldTop;        
    }

    return nullptr;
}


template <class T>
void Stack<T>::push(const T& item)
{
    StackNode<T>* newTop = new StackNode<T>;
    newTop->_value = item;

    newTop->_next = this->_top;
    this->_top = newTop;

    this->_size++;
}

template <class T>
int Stack<T>::indexOf(const T& value) const
{
    StackNode<T>* it = this->_top;
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
void Stack<T>::write(const T& value, uint32_t index) 
{
    if (index > 0 && index < this->_size)
    {   
        StackNode<T>* it = this->_top;
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
T Stack<T>::read(uint32_t index) const
{
    if (index > 0 && index < this->_size)
    {   
        StackNode<T>* it = this->_top;
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

    StackNode<T>* itCurrent = this->_top;
    StackNode<T>* itSource = stack._top;

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


#endif // _STACK_H