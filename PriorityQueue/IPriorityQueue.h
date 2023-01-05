#ifndef _IPRIORITYQUEUE_H
#define _IPRIORITYQUEUE_H

#include <iostream>

template <class T, class I>
class IPriorityQueue
{
    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual bool isEmpty() const = 0;
        virtual Type min() const = 0;

        virtual void insert(const Type& value) = 0;
        virtual void deleteMin() = 0;
        virtual void clear() = 0;
};


#endif // _IPRIORITYQUEUE_H
