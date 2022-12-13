#ifndef _STRUCTURES_IBINARYTREE_H
#define _STRUCTURES_IBINARYTREE_H

template <class T, class I>
class IBinaryTree
{

    public:
        typedef T Type;
        typedef I Iterator;

    public:
        virtual void addLeftChild(Type value) = 0;
        virtual void addRightChild(Type value) = 0;

        virtual void addLeftChild(Iterator node, Type value) = 0;
        virtual void addRightChild(Iterator node, Type value) = 0;

        virtual void preorderTraversal(Iterator root) = 0;
        virtual void postorderTraversal(Iterator root) = 0;
        virtual void inorderTraversal(Iterator root) = 0;
        virtual void leverOrderTraversal(Iterator root) = 0;
};



#endif // _STRUCTURES_IBINARYTREE_H
