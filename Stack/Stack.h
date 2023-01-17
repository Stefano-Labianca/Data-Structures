#ifndef _STACK_H
#define _STACK_H


#include "IStack.h"

#include "../LinkedList/LinkedList.h"

template <class T>
class Stack;

/**
 * Descrive un nodo dello stack
 * @tparam T : Tipo di dato da contenere
 */
template <class T>
class StackNode
{
    friend class Stack<T>;

    private:
        T _value; // Valore del nodo
        StackNode<T>* _next; // Puntarore al nodo successivo

    public:
        StackNode();
        StackNode(const T& value);

        T& getNodeValue();
        StackNode<T>* getNodeNext();
};

/**
 * Costruisce un nodo vuoto
 * @tparam T : Tipo di dato da contenere
 */
template <class T>
StackNode<T>::StackNode()
{
    this->_next = nullptr;
}

/**
 * Costruisce un nodo con valore value
 * @tparam T : Tipo di dato da contenere
 * @param value : Valore del nodo
 */
template <class T>
StackNode<T>::StackNode(const T& value)
{
    this->_next = nullptr;
    this->_value = value;
}

/**
 * Restituisce il valore del nodo
 * @tparam T : Tipo di dato da contenere
 * @return Valore del nodo
 */
template <class T>
T& StackNode<T>::getNodeValue()
{
    return this->_value;
}

/**
 * Restituisce il puntatore al nodo successivo
 * @tparam T : Tipo di dato da contenere
 * @return Puntatore al nodo successivo
 */
template <class T>
StackNode<T>* StackNode<T>::getNodeNext()
{
    return this->_next;
}


// ----------------------------------

/**
 * Descrive lo stack implementato con i puntatori
 * @tparam T : Tipo di dato da contenere
 */
template <class T>
class Stack : public IStack<T, StackNode<T>*>
{
    public:
        typedef typename IStack<T, StackNode<T>*>::Type Type;
        typedef typename IStack<T, StackNode<T>*>::Iterator Iterator;

    private:
        Iterator _top; // Puntatore all'elemento in cima allo stack
        uint32_t _size; // Dimensioni dello stack

    public:
        Stack();
        Stack(const Iterator & top);
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

/**
 * Costruisce uno stack vuoto
 * @tparam T : Tipo di dato da contenere
 */
template <class T>
Stack<T>::Stack()
{
    this->_top = nullptr;
    this->_size = 0;
}

/**
 * Costruisce uno stack con un nodo top in cima ad esso
 * @tparam T : Tipo di dato da contenere
 * @param top : Nodo da mettere in cima
 */
template <class T>
Stack<T>::Stack(const Iterator& top)
{
    this->_top = &top;
    this->_size = 1;
}

/**
 * Costruttore di  copia
 *
 * @tparam T : Tipo di dato da contenere
 * @param source : Stack da copiare
 */
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

/**
 * Distruttore dello stack
 *
 * @tparam T : Tipo di dato da contenere
 */
template <class T>
Stack<T>::~Stack()
{
    while (!this->isEmpty())
    {
        this->pop();
    }

    delete this->_top;
}

/**
 * Restituisce il valore contenuto nel nodo in cima allo stack
 *
 * @tparam T : Tipo di dato da contenere
 * @return Valore del nodo in cima
 */
template <class T>
typename Stack<T>::Type Stack<T>::peek() const
{
    return this->_top->_value;
}

/**
 * Restituisce il puntatore all'elemento in cima allo stack
 *
 * * @tparam T : Tipo di dato da contenere
 * @return Puntatore del nodo in cima allo stack
 */
template <class T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    return this->_top;
}

/**
 * Leggo il valore contenuto in pos.
 *
* @tparam T : Tipo di dato da contenere
 * @param pos : Nodo a cui leggere il valore
 * @return Valore contenuto in pos
 */
template <class T>
typename Stack<T>::Type Stack<T>::read(const Iterator pos) const
{
    if (!this->isEnd(pos) && !this->isEmpty())
    {
        return pos->_value;
    }
}

/**
 * Restituisce true se ho raggiunto la fine dello stack, altrimenti false
 * @tparam T : Tipo di dato da contenere
 * @return True se ho raggiunto la fine dello stack, altrimenti false
 */
template <class T>
bool Stack<T>::isEnd(const Iterator pos) const
{
    return pos == nullptr;
}

/**
 * Restituisce il nodo successivo a pos
 *
 * @tparam T : Tipo di dato da contenere
 * @param pos : Puntarore di un nodo
 * @return Puntatore al successivo di pos
 */
template <class T>
typename Stack<T>::Iterator Stack<T>::next(Iterator pos) const
{
    return pos->_next;
}

/**
 * Puntatore all'ultimo elemento nello stack
 * @tparam T : Tipo di dato da contenere
 * @return Ultimo elemento in stack
 */
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

/**
 * Restituisce true se lo stack e' vuoto, altrimenti false
 *
 * @tparam T : Tipo di dato da contenere
 * @return true se lo stack e' vuoto, altrimenti false
 */
template <class T>
bool Stack<T>::isEmpty() const
{
    return (this->_top == nullptr);
}

/**
 * Elimina il nodo in cima allo stack
 *
 * @tparam T : Tipo di dato da contenere
 */
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

/**
 * Inserisce un nodo con valore item nello stack
 *
 * @tparam T : Tipo di dato da contenere
 * @param item : Valore del nodo
 */
template <class T>
void Stack<T>::push(const Type& item)
{
    Iterator newTop = new StackNode<T>;
    newTop->_value = item;

    newTop->_next = this->_top;
    this->_top = newTop;
    this->_size++;
}

/**
 * Restituiusce la posizione, all'internod dello stack, del nodo con
 * valore value. -1 se non esiste
 *
 * @tparam T : Tipo di dato da contenere
 * @param value : Valore da ricercare
 * @return Indice del nodo o -1
 */
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

/**
 * Scrive un valore in una posizione index
 *
 * @tparam T : Tipo di dato da contenere
 * @param value : Valore da scrivere
* @param index : Indice in cui scrivere il valore
 */
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

/**
 * Restituisce l'elemento che si trova in posizione index nello stack
 *
* @tparam T : Tipo di dato da contenere
 * @param index : Indice
 * @return Elemento in posizione indedx
 */
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