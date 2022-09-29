#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "ILinkedList.h"
#include "../Node.h"

// TODO: Sistemarla con gli unique_ptr

template <class T>
class LinkedList: public ILinkedList <T, std::unique_ptr<Node<T>>>
{

    private:
        std::unique_ptr<Node<T>> head;
        std::unique_ptr<Node<T>> tail;
        unsigned int len;
 
    public:
        LinkedList();
        LinkedList(std::unique_ptr<Node<T>>& head);
        LinkedList(LinkedList<T>& otherList);
        ~LinkedList();

        unsigned int getSize() const override;
        bool isEmpty() const override;

        Node<T>& find(unsigned int index) const override;

        void replace(const T& value, unsigned int index) override;
        void insert(const T& value, unsigned int index) override;
        void remove(unsigned int index);

        void unshift(const T& value) override;
        void append(const T& value) override;
        void shift() override;
        void deleteLast() override;

        Node<T>& begin() const;
        Node<T>& end() const;
};

template <class T>
LinkedList<T>::LinkedList()
{
    this->len = 0;
}

template <class T>
LinkedList<T>::LinkedList(std::unique_ptr<Node<T>>& head)
{
    this->head = head;
    this->len = 1;
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& otherList)
{
    if (!this->head.get())
    {
        std::unique_ptr<Node<T>> it = otherList.begin();

        for (unsigned int i = 0; i < otherList.getSize(); i++)
        {
            T value = it->getNodeValue();
            this->append(value);

            it = it->getNext();
        }
    } 
}

template <class T>
LinkedList<T>::~LinkedList()
{
    while (this->head.get())
    {
        this->head = this->head->getNext();
    }
}


template <class T>
unsigned int LinkedList<T>::getSize() const
{
    return this->len;
}


template <class T>
bool LinkedList<T>::isEmpty() const
{
    return == 0&
}

template <class T>
Node<T>& LinkedList<T>::find(unsigned int index) const
{
    if (index >= this->len || index < 0)
    {
        return std::unique_ptr<Node<T>>(new Node<T>());
    }

    if (index == this->len - 1)
    {
        return this->tail;
    }

    if (this->len >= 0 && index > 0)
    {
        unsigned int i = 0;
        std::unique_ptr<Node<T>> it = this->head;   

        while (i != index)
        {
            it = it->getNext();
            i++;
        }
        
        return it;
    }

    return this->head;
}


template <class T>
void LinkedList<T>::replace(const T& value, unsigned int index)
{
    if (!this->isEmpty() && index >= 0 && index < this->len)
    {
        if (index == 0)
        {
            this->head->setNodeValue(value);
            return;
        }

        if (index == this->len - 1)
        {
            this->tail->setNodeValue(value);
            return;
        }

        std::unique_ptr<Node<T>> node = this->find(index);
        node->setNodeValue(value);
    }
}


template <class T>
void LinkedList<T>::insert(const T& value, unsigned int index)
{
    if (this->isEmpty() || index == 0)
    {
        this->unshift(value);
        return;
    }

    if (index == this->len - 1)
    {
        this->append(value);
        return;
    }

    std::unique_ptr<Node<T>> it = this->find(index);
    std::unique_ptr<Node<T>> prev = it->getPrev();
    std::unique_ptr<Node<T>> newNode(new Node<T>(value, it, prev));
    
    prev->setNext(newNode);
    it->setPrev(newNode);
    this->len += 1;
}

template <class T>
void LinkedList<T>::remove(unsigned int index)
{
    if (this->isEmpty() || index == 0)
    {
        this->shift();
        return;
    }

    if (index == this->len - 1)
    {
        this->deleteLast();
        return;
    }

    std::unique_ptr<Node<T>> it = this->find(index);
    std::unique_ptr<Node<T>> prev = it->getPrev();
    std::unique_ptr<Node<T>> next = it->getNext();

    prev->setNext(next);
    next->setPrev(prev);

    it.reset();
    this->len -= 1;

}

template <class T>
void LinkedList<T>::unshift(const T& value)
{
    std::unique_ptr<Node<T>> newNode(new Node<T>(value));

    if (this->isEmpty())
    {
        this->head = newNode;
        this->tail = newNode;
    }

    else
    {
        std::unique_ptr<Node<T>> oldHead = this->head;
        this->head = newNode;
        this->head->setNext(oldHead);
        oldHead.reset();
    }

    this->len += 1;
}

template <class T>
void LinkedList<T>::append(const T& value)
{
    std::unique_ptr<Node<T>> newNode(new Node<T>(value));

    if (this->isEmpty())
    {
        this->head = newNode;
        this->tail = newNode;
    }

    else
    {
        std::unique_ptr<Node<T>> oldTail = this->tail;
        this->tail = newNode;
        
        oldTail->setNext(this->tail);
        this->tail->setPrev(oldTail);

        oldTail.reset();
    }

    this->len += 1;
}


template <class T>
void LinkedList<T>::shift()
{
    if (this->head.get())
    {
        std::unique_ptr<Node<T>> newHead = this->head->getNext();
        this->head.reset();

        this->head = newHead;
        this->len -= 1;
    }
}

template <class T>
void LinkedList<T>::deleteLast()
{
    if (this->head.get())
    {   
        std::unique_ptr<Node<T>> newTail = this->tail.get()->getPrev();
        newTail->resetNodeNext();

        this->tail.reset();
        this->tail = newTail;
        this->len -= 1;
    }
}


template <class T>
Node<T>& LinkedList<T>::begin() const
{
    return *(this->head.get());
}


template <class T>
Node<T>& LinkedList<T>::end() const
{
    return *(this->tail.get());
}



#endif // LINKED_LIST_H
