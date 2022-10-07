#ifndef _NODE_H
#define _NODE_H

#include <iostream>

template <class T>
class Node
{
    private:
        T value;
        Node<T>* next;
        Node<T>* prev; 

    public:
        Node();
        Node(const T& value);
        Node(const T& value, Node<T>* next);
        Node(const T& value, Node<T>* next, Node<T>* prev);
        Node(const Node<T>& source);

        T getNodeValue();
        Node<T>* getNext();
        Node<T>* getPrev();

        void setNodeValue(const T& value);
        void setNext(Node<T>* next);
        void setPrev(Node<T>* prev);
 
        template <class V>
        friend std::ostream& operator<<(std::ostream& out, const Node<V>* node);
};

template <class T>
Node<T>::Node()
{
    this->next = nullptr;
    this->prev = nullptr;
}


template <class T>
Node<T>::Node(const T& value)
{ 
    this->value = value;
    this->next = nullptr;
    this->prev = nullptr;
}

template <class T>
Node<T>::Node(const T& value, Node<T>* next)
{
    this->value = value;
    this->next = next;
    this->prev = nullptr;
}

template <class T>
Node<T>::Node(const T& value, Node<T>* next, Node<T>* prev)
{
    this->value = value;
    this->next = &next;
    this->prev = &prev;
}

template <class T>
Node<T>::Node(const Node<T>& source)
{
    this->value = source.value;
    this->prev = source.prev;
    this->next = source.next;
}


template <class T>
T Node<T>::getNodeValue()
{
    return this->value;
}

template <class T>
Node<T>* Node<T>::getNext()
{
    return this->next;
}

template <class T>
Node<T>* Node<T>::getPrev()
{
    return this->prev;
}



template <class T>
void Node<T>::setNodeValue(const T& value)
{
    this->value = value;
}

template <class T>
void Node<T>::setNext(Node<T>* next)
{
    this->next = next;
}

template <class T>
void Node<T>::setPrev(Node<T>* prev)
{
    this->prev = prev;
}


template <class T>
std::ostream& operator<<(std::ostream& out, const Node<T>* node)
{
    out << "{ " << node->value << " }" << std::endl;

    return out;
}


#endif