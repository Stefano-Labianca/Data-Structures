#ifndef STRUCTURES_BINARYTREE_H
#define STRUCTURES_BINARYTREE_H

#include <iostream>
#include "./IBinaryTree.h"
#include "../Queue/Queue.h"

template <class T>
class BinaryTree;


template <class T>
class BinaryTreeNode
{
    friend class BinaryTree<T>;

    public:
        T _value;
        BinaryTreeNode<T>* _parent;
        BinaryTreeNode<T>* _leftChild;
        BinaryTreeNode<T>* _rightChild;

        uint32_t _level;
};


template <class T>
class BinaryTree : public IBinaryTree<T, BinaryTreeNode<T>*>
{
    public:
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Type Type;
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Iterator Iterator;

    public:
        Iterator _root;

    private:
        void _createRoot(Type rootValue);

    public:
        BinaryTree();
        BinaryTree(Type rootValue);


        void addLeftChild(Type value);
        void addRightChild(Type value);
        void addLeftChild(Iterator node, Type value);
        void addRightChild(Iterator node, Type value);

        void preorderTraversal(Iterator root);
        void postorderTraversal(Iterator root);
        void inorderTraversal(Iterator root);
        void leverOrderTraversal(Iterator root);

};



template <class T>
BinaryTree<T>::BinaryTree()
{
    this->_root = nullptr;
}


template <class T>
BinaryTree<T>::BinaryTree(Type rootValue)
{
   this->_createRoot(rootValue);
}


template <class T>
void BinaryTree<T>::addLeftChild(Type value)
{
    if (!this->_root)
    {
        this->_createRoot(value);
        return;
    }

    Iterator it = this->_root;

    while (it)
    {
        if (!it->_leftChild)
        {
            Iterator newLeftChild = new BinaryTreeNode<T>;
            newLeftChild->_value = value;
            newLeftChild->_leftChild = nullptr;
            newLeftChild->_rightChild = nullptr;
            newLeftChild->_parent = it;

            newLeftChild->_level = it->_level + 1;
            it->_leftChild = newLeftChild;

            return;
        }

        it = it->_leftChild;
    }
}


template <class T>
void BinaryTree<T>::addLeftChild(Iterator node, Type value)
{
    if (!this->_root)
    {
        this->_createRoot(value);
        return;
    }

    Iterator leftNode = node->_leftChild;

    if (!leftNode)
    {
        Iterator newLeftChild = new BinaryTreeNode<T>;
        newLeftChild->_value = value;
        newLeftChild->_leftChild = nullptr;
        newLeftChild->_rightChild = nullptr;

        newLeftChild->_level = node->_level + 1;
        newLeftChild->_parent = node;
        node->_leftChild = newLeftChild;

        return;
    }

    node->_leftChild->_value = value;
}


template <class T>
void BinaryTree<T>::addRightChild(Type value)
{
    if (!this->_root)
    {
        this->_createRoot(value);
        return;
    }

    Iterator it = this->_root;

    while (it)
    {
        if (!it->_rightChild)
        {
            Iterator newRightChild = new BinaryTreeNode<T>;
            newRightChild->_value = value;
            newRightChild->_leftChild = nullptr;
            newRightChild->_rightChild = nullptr;
            newRightChild->_parent = it;

            newRightChild->_level = it->_level + 1;
            it->_rightChild = newRightChild;

            return;
        }

        it = it->_rightChild;
    }
}

template <class T>
void BinaryTree<T>::addRightChild(Iterator node, Type value)
{
    if (!this->_root)
    {
        this->_createRoot(value);
        return;
    }

    Iterator rightNode = node->_rightChild;

    if (!rightNode)
    {
        Iterator newRightChild = new BinaryTreeNode<T>;
        newRightChild->_value = value;
        newRightChild->_leftChild = nullptr;
        newRightChild->_rightChild = nullptr;

        newRightChild->_level = node->_level + 1;
        newRightChild->_parent = node;
        node->_rightChild = newRightChild;

        return;
    }

    node->_rightChild->_value = value;
}



template <class T>
void BinaryTree<T>::preorderTraversal(Iterator root)
{
    if (root)
    {
        std::cout << root->_value << " ";
        this->preorderTraversal(root->_leftChild);
        this->preorderTraversal(root->_rightChild);
    }
}

template <class T>
void BinaryTree<T>::postorderTraversal(Iterator root)
{
    if (root)
    {
        this->postorderTraversal(root->_leftChild);
        this->postorderTraversal(root->_rightChild);
        std::cout << root->_value << " ";
    }
}

template <class T>
void BinaryTree<T>::inorderTraversal(Iterator root)
{
    if (root)
    {
        this->inorderTraversal(root->_leftChild);
        std::cout << root->_value << " ";
        this->inorderTraversal(root->_rightChild);
    }
}


template <class T>
void BinaryTree<T>::leverOrderTraversal(Iterator root)
{
    Queue<Iterator> queue;
    queue.enqueue(root);

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();

        std::cout << iter->_value << " ";

        if (iter->_leftChild)
        {
            queue.enqueue(iter->_leftChild);
        }

        if (iter->_rightChild)
        {
            queue.enqueue(iter->_rightChild);
        }
    }
}





template <class T>
void BinaryTree<T>::_createRoot(Type rootValue)
{
    this->_root = new BinaryTreeNode<T>;
    this->_root->_value = rootValue;

    this->_root->_parent = nullptr;
    this->_root->_leftChild = nullptr;
    this->_root->_rightChild = nullptr;

    this->_root->_level = 0;
}



#endif //STRUCTURES_BINARYTREE_H
