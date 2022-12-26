#ifndef _ISET_H
#define _ISET_H

#include <iostream>

template <class T, class I>
class ISet {
    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual bool isEmpty() = 0;
        virtual bool contains(Type needle) = 0;
        virtual void add(Type needle) = 0;
        virtual void remove(Type needle) = 0;

        virtual void unions(ISet<Type, Iterator> set) = 0;
        virtual void intersection(ISet<Type, Iterator> set) = 0;
        virtual void difference(ISet<Type, Iterator> set) = 0;

        virtual bool isSubset(ISet<Type, Iterator> set) = 0;
        virtual uint32_t size() = 0;
};


#endif // _ISET_H