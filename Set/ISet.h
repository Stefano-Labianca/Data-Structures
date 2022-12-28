#ifndef _ISET_H
#define _ISET_H

#include <iostream>

template <class T, class I>
class ISet {
    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual bool isEmpty() const = 0;
        virtual bool contains(const Type& needle) const = 0;
        virtual void add(const Type& needle) = 0;
        virtual void remove(const Type& needle) = 0;

        virtual uint32_t size() const = 0;
};


#endif // _ISET_H