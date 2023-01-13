#ifndef _ILINKED_LIST_H
#define _ILINKED_LIST_H

#include <iostream>
#include <ostream>

template <class T, class I>
class ILinkedList
{
    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual std::size_t getSize() const = 0;
        virtual bool isEmpty() const = 0;

        virtual void insert(const Type& value, std::size_t index) = 0;
        virtual void remove(std::size_t index) = 0;

        virtual void unshift(const Type& value) = 0;
        virtual void append(const Type& value) = 0;
        virtual void shift() = 0;
        virtual void deleteLast() = 0;

        virtual Iterator begin() const = 0;
        virtual Iterator last() const = 0;
        virtual bool isEnd(Iterator it) const = 0;

        template <typename V, typename U>
        friend std::ostream& operator<<(std::ostream& out, const ILinkedList<V, U>& list);
};


template <class V, class U>
std::ostream& operator<<(std::ostream& out, const ILinkedList<V, U>& list)
{
    typename ILinkedList<V, U>::Iterator it = list.begin();

    out << "[ ";

    if (list.getSize() == 0)
    {
        out << " ]" << std::endl;
        return out;
    }

    while (!list.isEnd(it))
    {
        if  (it == list.last())
        {
            out << it->getNodeValue() << " ]" << std::endl;
        }

        else
        {
            out << it->getNodeValue() << ", ";
        }

        it = it->getNext();
    }

    return out;
}


#endif // _ILINKED_LIST_H