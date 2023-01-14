#ifndef _IBINARYSEARCHTREE_H
#define _IBINARYSEARCHTREE_H

#include <iostream>
#include <ostream>

template <class T, class I>
class IBinarySearchTree
{
    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual void insert(Type nodeValue) = 0;
        virtual void remove(Type needle) = 0;
        virtual Iterator lookup(Type needle) = 0;

        virtual Iterator successor(Iterator node) = 0;
        virtual Iterator predecessor(Iterator node) = 0;

        virtual Iterator min(Iterator start) = 0;
        virtual Iterator max(Iterator start) = 0;

        virtual Iterator getRoot() = 0;

        virtual bool isLeftEmpty(Iterator leftChild) = 0;
        virtual bool isRightEmpty(Iterator rightChild) = 0;

        virtual bool isEmpty() = 0;
        virtual void travers() = 0;
};


#endif // _IBINARYSEARCHTREE_H
