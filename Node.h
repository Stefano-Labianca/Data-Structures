#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <memory>

template <class T>
class Node
{
    private:
        T value;
        std::shared_ptr<Node<T>> next;
        std::shared_ptr<Node<T>> prev;

    public:
        Node();
        Node(const T& value);
        Node(const T& value, std::shared_ptr<Node<T>>& next);
        Node(const T& value, std::shared_ptr<Node<T>>& next, std::shared_ptr<Node<T>>& prev);
        Node(const std::shared_ptr<Node<T>>& node);

        T getNodeValue();
        std::shared_ptr<Node<T>> getNext();
        std::shared_ptr<Node<T>> getPrev();


        void setNodeValue(const T& value);
        void setNext(std::shared_ptr<Node<T>>& next);
        void setPrev(std::shared_ptr<Node<T>>& prev);
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
Node<T>::Node(const T& value, std::shared_ptr<Node<T>>& next)
{
    this->value = value;
    this->next = next;
}

template <class T>
Node<T>::Node(const T& value, std::shared_ptr<Node<T>>& next, std::shared_ptr<Node<T>>& prev)
{
    this->value = value;
    this->next = next;
    this->prev = prev;
}


template <class T>
Node<T>::Node(const std::shared_ptr<Node<T>>& node)
{
    this->next = node.next;
    this->prev = node.prev;
    this->value = node.value;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node)
{
    out << "{ Node's Value: " << node.value << " }" << std::endl;

    return out;
}


template <class T>
T Node<T>::getNodeValue()
{
    return this->value;
}

template <class T>
std::shared_ptr<Node<T>> Node<T>::getNext()
{
    return this->next;
}

template <class T>
std::shared_ptr<Node<T>> Node<T>::getPrev()
{
    return this->prev;
}

template <class T>
void Node<T>::setNodeValue(const T& value)
{
    this->value = value;
}

template <class T>
void Node<T>::setNext(std::shared_ptr<Node<T>>& next)
{
    this->next = next;
}

template <class T>
void Node<T>::setPrev(std::shared_ptr<Node<T>>& prev)
{
    this->prev = prev;
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