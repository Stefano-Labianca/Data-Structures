#ifndef _TRUCTURES_BINARYSEARCHTREE_H
#define _STRUCTURES_BINARYSEARCHTREE_H

#include "../BinaryTree/BinaryTree.h"

// TODO: Verificare l'uso con le chiavi
// TODO: Aggiornamento livelli e altezza

template <class T>
class BinarySearchTree : public BinaryTree<T>
{
    public:
        typedef typename BinaryTree<T>::Iterator Iterator;
        typedef typename BinaryTree<T>::Type Type;

    private:
        void _link(BinaryTreeNode<Type>* parent, BinaryTreeNode<Type>* child, Type childValue);

    private:
        BinaryTree<T>* _bTree;

    public:
        BinarySearchTree();
        BinarySearchTree(Type rootValue);

        void insert(Type nodeValue);
        void remove(Type needle);
        Iterator lookup(Type needle);

        Iterator successor(Iterator node);
        Iterator predecessor(Iterator node);

        Iterator min(Iterator start);
        Iterator max(Iterator start);

        Iterator getRoot();
        BinarySearchTree<T>* subTree(Iterator root);

        bool isEmpty();
        void travers();
};


template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    this->_bTree = new BinaryTree<T>;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree(Type rootValue)
{
    this->_bTree = new BinaryTree<T>(rootValue);
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::getRoot()
{
    return this->_bTree->getRoot();
}


template <class T>
void BinarySearchTree<T>::insert(Type nodeValue)
{
    Iterator parent = nullptr;
    Iterator iter = this->_bTree->getRoot();

    if (this->_bTree->getRoot() == nullptr)
    {
        this->_bTree = new BinaryTree<T>(nodeValue);
        return;
    }

    while (iter)
    {
        parent = iter;

        if (iter->getNodeValue() == nodeValue)
        {
            return;
        }

        if (nodeValue < iter->getNodeValue())
        {
            iter = iter->getNodeLeftChild();
        }

        else if (nodeValue > iter->getNodeValue())
        {
            iter = iter->getNodeRightChild();
        }
    }


    Iterator child = new BinaryTreeNode<T>(nodeValue);
    this->_link(parent, child, nodeValue);

}


template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::lookup(Type needle)
{
    Iterator it = this->_bTree->getRoot();

    while (it && it->getNodeValue() != needle)
    {
        if (needle < it->getNodeValue())
        {
            it = it->getNodeLeftChild();
        }

        else if (needle > it->getNodeValue())
        {
            it = it->getNodeRightChild();
        }
    }

    return it;
}



template <class T>
void BinarySearchTree<T>::remove(Type needle)
{
    Iterator node = this->lookup(needle);

    if (node)
    {
        if (!this->isLeftEmpty(node) && !this->isRightEmpty(node))
        {
            Iterator it = node->getNodeRightChild();

            while (!this->isLeftEmpty(it))
            {
                it = it->getNodeLeftChild();
            }

            node->setNodeValue(it->getNodeValue());
            node = it;
            Iterator newChild;

            if (!this->isLeftEmpty(node) && this->isRightEmpty(node))
            {
                newChild = node->getNodeLeftChild();
            }

            else
            {
                newChild = node->getNodeRightChild();
            }

            this->_link(node->getNodeParent(), newChild, needle);

            delete node;
            node = nullptr;
        }
    }
}




template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::min(Iterator start)
{
    Iterator it = start;

    while (!this->isLeftEmpty(it))
    {
        it = it->getNodeLeftChild();
    }

    return it;
}


template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::max(Iterator start)
{
    Iterator it = start;

    while (!this->isRightEmpty(it))
    {
        it = it->getNodeRightChild();
    }

    return it;
}



template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::successor(Iterator node)
{
    if (!node)
    {
        return node;
    }

    if (!this->isRightEmpty(node))
    {
        return this->min(node->getNodeRightChild());
    }

    Iterator it = node->getNodeParent();

    while (it && node == it->getNodeRightChild())
    {
        node = it;
        it = it->getNodeParent();
    }

    return it;
}

template <class T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::predecessor(Iterator node)
{
    if (!node)
    {
        return node;
    }

    if (!this->isLeftEmpty(node))
    {
        return this->max(node->getNodeLeftChild());
    }

    Iterator it = node->getNodeParent();

    while (it && node == it->getNodeLeftChild())
    {
        node = it;
        it = it->getNodeParent();
    }

    return it;
}


template <class T>
bool BinarySearchTree<T>::isEmpty()
{
    return this->_bTree->getRoot();
}


template <class T>
void BinarySearchTree<T>::travers()
{
    Iterator u = this->min(this->_bTree->getRoot());

    while (u)
    {
        std::cout << u->getNodeValue() << " ";
        u = this->successor(u);
    }

}


template <class T>
BinarySearchTree<T>* BinarySearchTree<T>::subTree(Iterator root)
{
    if (root == this->_bTree->getRoot())
    {
        return this;
    }

    BinarySearchTree<T>* subT = new BinarySearchTree<T>;
    BinaryTreeNode<T>* subRoot = new BinaryTreeNode<T>(root->getNodeValue());

    subRoot->setNodeRightChild(root->getNodeRightChild());
    subRoot->setNodeLeftChild(root->getNodeLeftChild());

    subT->_bTree->setRoot(subRoot);

    return subT;
}



template <class T>
void BinarySearchTree<T>::_link(BinaryTreeNode<Type>* parent, BinaryTreeNode<Type>* child, Type childValue)
{
    if (child)
    {
        child->setNodeParent(parent);
    }

    if (parent)
    {
        if (childValue < parent->getNodeValue())
        {
            parent->setNodeLeftChild(child);
        }

        else
        {
            parent->setNodeRightChild(child);
        }
    }

}



#endif // _STRUCTURES_BINARYSEARCHTREE_H
