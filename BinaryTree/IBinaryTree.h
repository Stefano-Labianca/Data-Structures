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

        virtual void addLeftChild(Iterator child, Iterator parent) = 0;
        virtual void addRightChild(Iterator child, Iterator parent) = 0;

        virtual void deleteLeft(Iterator node) = 0;
        virtual void deleteRight(Iterator node) = 0;

        virtual bool isLeftEmpty(Iterator leftChild) = 0;
        virtual bool isRightEmpty(Iterator rightChild) = 0;
        virtual bool isBinaryTreeEmpty() = 0;
        virtual bool isLeaf(Iterator node) = 0;
        virtual bool isRoot(Iterator node) = 0;

        virtual void preorderTraversal(Iterator root) = 0;
        virtual void postorderTraversal(Iterator root) = 0;
        virtual void inorderTraversal(Iterator root) = 0;
        virtual void levelOrderTraversal(Iterator root) = 0;

        virtual uint32_t calculateNodesAmount() = 0;
        virtual uint32_t getHeight() = 0;
        virtual uint32_t calculateMaxLevel(Iterator node, uint32_t nodeLvl) = 0;

        virtual Iterator getRoot() = 0;
        virtual Iterator getLeftChild(Iterator node) = 0;
        virtual Iterator getRightChild(Iterator node) = 0;
        virtual Iterator getParent(Iterator node) = 0;

};



#endif // _STRUCTURES_IBINARYTREE_H
