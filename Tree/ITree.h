#ifndef _ITREE_H
#define _ITREE_H

#include <iostream>
#include <string>

template <class T, class I>
class ITree {
    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual bool isEmpty() const = 0;
        virtual bool isLeaf(Iterator node) const = 0;
        virtual Iterator getRoot() const = 0;

        virtual void insertFirstChild(Iterator parent, const Type& value) = 0;
        virtual void insertSibling(Iterator child, const Type& value) = 0;

        virtual bool isLastSibling(Iterator node) const = 0;
        virtual Iterator getNextSibling(Iterator node) const = 0;
        virtual Iterator getFirstChild(Iterator node) const = 0;
        virtual Iterator getParent(Iterator node) const = 0;

        virtual void preorderTraversal(Iterator root) = 0;
        virtual void postorderTraversal(Iterator root) = 0;
        virtual void inorderTraversal(Iterator root, uint32_t i) = 0;
        virtual void levelOrderTraversal(Iterator root) = 0;

        virtual void deleteFirstChild(Iterator root) = 0;
        virtual void deleteSibling(Iterator child) = 0;

        virtual uint32_t calculateWidth(Iterator root) = 0;
        virtual uint32_t getDepth(Iterator root) = 0;
};


#endif // _ITREE_H
