#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "ILinkedList.h"
#include "../Node.h"


template <class T>
class LinkedList: public ILinkedList<T, Node<T>*>
{
    private:
        Node<T>* _head;
        Node<T>* _tail;
        uint32_t _len;

    public:
        LinkedList();
        LinkedList(const T& value);
        LinkedList(LinkedList<T>& otherList);
        ~LinkedList();

        uint32_t getSize() const override;
        bool isEmpty() const override;

        Node<T>* find(uint32_t index) const override;
        void insert(const T& value, uint32_t index) override;
        void remove(uint32_t index);

        void unshift(const T& value) override;
        void append(const T& value) override;
        void shift() override;
        void deleteLast() override;

        Node<T>* begin() const;
        Node<T>* end() const;
};

template <class T>
LinkedList<T>::LinkedList()
{
    this->_len = 0;
    this->_head = nullptr;
    this->_tail = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(const T& value)
{
    Node<T> newHead(value);

    this->_head = &newHead;
    this->_len = 1;
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& otherList)
{
    if (!otherList.isEmpty())
    {
        this->_len = 0;
        this->_head = nullptr;
        this->_tail = nullptr;

        Node<T>* it = otherList.begin();

        for (uint32_t i = 0; i < otherList.getSize(); i++)
        {
            T value = it->getNodeValue();
            this->append(value);
            it = it->getNext();
        }

        delete it;
        it = nullptr;
    } 
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* it = this->_head->getNext();
    Node<T>* head = this->_head;

    while (it)
    {
        Node<T>* tempIt = it->getNext();
        delete it;

        it = tempIt;
        this->_len--;
    }

    delete head;
    this->_len--;
}


template <class T>
uint32_t LinkedList<T>::getSize() const
{
    return this->_len;
}


template <class T>
bool LinkedList<T>::isEmpty() const
{
    return this->_len == 0;
}

template <class T>
Node<T>* LinkedList<T>::find(uint32_t index) const
{
    if (index >= this->_len)
    {
        index %= this->_len; 
    }

    if (index == this->_len - 1)
    {
        return this->_tail;
    }

    if (index == 0)
    {
        return this->_head;
    }

    if (this->_len >= 0 && index > 0)
    {
        uint32_t i = 0;
        Node<T>* it = this->_head;   

        while (i != index)
        {
            it = it->getNext();
            i++;
        }
        
        return it;
    }

    return nullptr;
}



template <class T>
void LinkedList<T>::insert(const T& value, uint32_t index)
{
    if (this->isEmpty() || index == 0)
    {
        this->unshift(value);
        return;
    }

    if (index == this->_len - 1)
    {
        this->append(value);
        return;
    }

    Node<T>* it = this->find(index);
    Node<T>* prev = it->getPrev();
    
    Node<T>* newNode = new Node<T>;
    newNode->setNodeValue(value);

    prev->setNext(newNode);
    newNode->setPrev(prev);
    
    newNode->setNext(it);
    it->setPrev(newNode);

    this->_len += 1;
}

template <class T>
void LinkedList<T>::remove(uint32_t index)
{

    if (!this->isEmpty())
    {
        if (index == 0)
        {
            this->shift();
            return;
        }

        if (index == this->_len - 1)
        {
            this->deleteLast();
            return;
        }
    }


    Node<T>* it = this->find(index);
    Node<T>* prev = it->getPrev();
    Node<T>* next = it->getNext();

    prev->setNext(next);
    next->setPrev(prev);

    delete it;
    it = nullptr;

    this->_len -= 1;

}

template <class T>
void LinkedList<T>::unshift(const T& value)
{
    Node<T>* newNode = new Node<T>;
    newNode->setNodeValue(value);

    if (this->isEmpty())
    {
        this->_head = newNode;
        this->_tail = newNode;
    }

    else
    {
        Node<T>* oldHead = this->_head;
        this->_head = newNode;

        this->_head->setNext(oldHead);
        oldHead->setPrev(this->_head);
    }

    this->_len += 1;
}

template <class T>
void LinkedList<T>::append(const T& value)
{
    Node<T>* newNode = new Node<T>;
    newNode->setNodeValue(value);

    if (this->isEmpty())
    {
        this->_head = newNode;
        this->_tail = newNode;
    }

    else
    {
        this->_tail->setNext(newNode);
        newNode->setPrev(this->_tail);
        this->_tail = newNode;
    }

    this->_len += 1;
}


template <class T>
void LinkedList<T>::shift()
{
    if (this->_head)
    {
        Node<T>* newHead = this->_head->getNext();
        Node<T>* oldHead = this->_head;

        this->_head = newHead;

        delete oldHead;
        oldHead = nullptr;
        this->_head->setPrev(nullptr);

        this->_len -= 1;
    }
}

template <class T>
void LinkedList<T>::deleteLast()
{
    if (this->_head)
    {   
        Node<T>* newTail = this->_tail->getPrev();

        delete this->_tail;
        this->_tail = nullptr;

        newTail->setNext(nullptr);
        
        this->_tail = newTail;
        this->_len -= 1;

    }
}


template <class T>
Node<T>* LinkedList<T>::begin() const
{
    return this->_head;
}


template <class T>
Node<T>* LinkedList<T>::end() const
{
    return this->_tail;
}



#endif // LINKED_LIST_H
