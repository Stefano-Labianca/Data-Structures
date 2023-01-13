#ifndef _ISORTEDLINKEDLIST_H
#define _ISORTEDLINKEDLIST_H

#include <iostream>
#include <ostream>

template <class T, class I>
class ISortedLinkedList
{
    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual uint32_t getSize() const = 0;
        virtual bool isEmpty() const = 0;
        virtual bool isEnd(Iterator it) const = 0;

        virtual void add(const T& value) = 0;
        virtual void remove(uint32_t index) = 0;

        virtual Iterator getMin() = 0;
        virtual Iterator getMax() = 0;

        virtual Iterator find(uint32_t index) = 0;
        virtual Iterator begin() const = 0;
        virtual Iterator last() const = 0;
};



#endif // _ISORTEDLINKEDLIST_H
