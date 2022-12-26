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
        virtual uint32_t getSize() const = 0;
        virtual bool isEmpty() const = 0;

        virtual I find(uint32_t index) const = 0;
        virtual void insert(const T& value, uint32_t index) = 0;

        virtual void unshift(const T& value) = 0;
        virtual void append(const T& value) = 0;
        virtual void shift() = 0;
        virtual void deleteLast() = 0;
        virtual void remove(uint32_t index) = 0;

        virtual I begin() const = 0;
        virtual I last() const = 0;
        virtual bool isEnd(I it) const = 0;

        template <typename V, typename U>
        friend std::ostream& operator<<(std::ostream& out, const ILinkedList<V, U>& list);
};


template <class V, class U>
std::ostream& operator<<(std::ostream& out, const ILinkedList<V, U>& list)
{
    U it = list.begin();

    while (!list.isEnd(it))
    {
        if  (it == list.last())
        {
            out << "[ " << it->getNodeValue() << " ]" << std::endl;
        }

        else
        {
            out << "[ " <<it->getNodeValue() << " ] -> ";
        }

        it = it->getNext();
    }

    return out;
}


#endif // _ILINKED_LIST_H