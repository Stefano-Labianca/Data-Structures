#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <memory>

template <class T>
class Node
{
    private:
        T value;
        std::unique_ptr<Node<T>> next;
        std::unique_ptr<Node<T>> prev; 

    public:
        Node();
        Node(const T& value);
        Node(const T& value, std::unique_ptr<Node<T>>& next);
        Node(const T& value, std::unique_ptr<Node<T>>& next, std::unique_ptr<Node<T>>& prev);

        T getNodeValue();
        Node<T>& getNext();
        Node<T>& getPrev();
        Node<T>& copy();

        void setNodeValue(const T& value);
        void setNext(std::unique_ptr<Node<T>>& next);
        void setPrev(std::unique_ptr<Node<T>>& prev);
        void resetNodePointers();
        void resetNodeNext();
        void resetNodePrev();

        template <class V>
        friend std::ostream& operator<<(std::ostream& out, const Node<V>& node);
};

template <class T>
Node<T>::Node() = default;

template <class T>
Node<T>::Node(const T& value): value(value) { }

template <class T>
Node<T>::Node(const T& value, std::unique_ptr<Node<T>>& next)
{
    this->value = std::move(value);
    this->next = std::move(next);
}

template <class T>
Node<T>::Node(const T& value, std::unique_ptr<Node<T>>& next, std::unique_ptr<Node<T>>& prev)
{
    this->value = value;
    this->next = std::move(next);
    this->prev = std::move(prev);
}


template <class T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node)
{
    out << "{ " << node.value << " }" << std::endl;

    return out;
}


template <class T>
T Node<T>::getNodeValue()
{
    return this->value;
}

template <class T>
Node<T>& Node<T>::getNext()
{
    return *(this->next.get());
}

template <class T>
Node<T>& Node<T>::getPrev()
{
    return *(this->prev.get());
}

template <class T>
Node<T>& Node<T>::copy()
{
    return *this;
}

template <class T>
void Node<T>::setNodeValue(const T& value)
{
    this->value = value;
}

template <class T>
void Node<T>::setNext(std::unique_ptr<Node<T>>& next)
{
    this->next = std::move(next);
}

template <class T>
void Node<T>::setPrev(std::unique_ptr<Node<T>>& prev)
{
    this->prev = std::move(prev);
}

template <class T>
void Node<T>::resetNodePointers()
{
    this->prev.reset();
    this->next.reset();
}


template <class T>
void Node<T>::resetNodeNext()
{
    this->next.reset();
}

template <class T>
void Node<T>::resetNodePrev()
{
    this->prev.reset();
}

#endif