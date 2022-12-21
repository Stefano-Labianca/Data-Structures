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

    protected:
        T _value;
        BinaryTreeNode<T>* _parent;
        BinaryTreeNode<T>* _leftChild;
        BinaryTreeNode<T>* _rightChild;

        uint32_t _level;

    public:
        BinaryTreeNode();
        BinaryTreeNode(T value);
        BinaryTreeNode(T value, uint32_t level, BinaryTreeNode<T>* parent);
        BinaryTreeNode(const BinaryTreeNode<T>& source);

        void setNodeValue(T value);
        void setNodeParent(BinaryTreeNode<T>* parent);
        void setNodeLeftChild(BinaryTreeNode<T>* left);
        void setNodeRightChild(BinaryTreeNode<T>* right);

        T getNodeValue();
        BinaryTreeNode<T>* getNodeParent();
        BinaryTreeNode<T>* getNodeLeftChild();
        BinaryTreeNode<T>* getNodeRightChild();

        uint32_t getNodeLevel();
};

template <class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
    this->_level = 0;
    this->_parent = nullptr;
    this->_leftChild = nullptr;
    this->_rightChild = nullptr;
}

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(T value)
{
    this->_value = value;
    this->_level = 0;
    this->_parent = nullptr;
    this->_leftChild = nullptr;
    this->_rightChild = nullptr;
}

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(T value, uint32_t level, BinaryTreeNode<T>* parent)
{
    this->_level = level;
    this->_value = value;
    this->_parent = parent;
    this->_leftChild = nullptr;
    this->_rightChild = nullptr;
}


template <class T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& source)
{
    this->_value = source._value;
    this->_parent = source._parent;
    this->_rightChild = source._rightChild;
    this->_leftChild = source._leftChild;
    this->_level = source._level;
}

template <class T>
T BinaryTreeNode<T>::getNodeValue()
{
    return this->_value;
}

template <class T>
void BinaryTreeNode<T>::setNodeValue(T value)
{
    this->_value = value;
}

template <class T>
void BinaryTreeNode<T>::setNodeParent(BinaryTreeNode<T>* parent)
{
    this->_parent = parent;
}

template <class T>
void BinaryTreeNode<T>::setNodeLeftChild(BinaryTreeNode<T>* left)
{
    this->_leftChild = left;
}

template <class T>
void BinaryTreeNode<T>::setNodeRightChild(BinaryTreeNode<T>* right)
{
    this->_rightChild = right;
}


template <class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getNodeParent()
{
    return this->_parent;
}

template <class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getNodeLeftChild()
{
    return this->_leftChild;
}

template <class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getNodeRightChild()
{
    return this->_rightChild;
}

template <class T>
uint32_t BinaryTreeNode<T>::getNodeLevel()
{
    return this->_level;
}


// ---------------------------------------------




template <class T>
class BinaryTree : public IBinaryTree<T, BinaryTreeNode<T>*>
{
    public:
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Type Type;
        typedef typename IBinaryTree<T, BinaryTreeNode<T>*>::Iterator Iterator;

    protected:
        Iterator _root;
        uint32_t _height;


    protected:
        bool _isNodeEmpty(Iterator node);
        void _updateHeight();
        void _updateHeight(uint32_t subTreeHeight, uint32_t parentH);
        void _updateLevels(Iterator startingNode, uint32_t initLevel);
        void _erase(Iterator root);

    public:
        BinaryTree();
        BinaryTree(Type rootValue);
        ~BinaryTree();

        void addLeftChild(Type value);
        void addRightChild(Type value);

        void addLeftChild(Iterator node, Type value);
        void addRightChild(Iterator node, Type value);

        void addLeftChild(Iterator child, Iterator parent);
        void addRightChild(Iterator child, Iterator parent);

        void addLeftChild(BinaryTree<Type>* child, Iterator parent);
        void addRightChild(BinaryTree<Type>* child, Iterator parent);

        void deleteLeft(Iterator node);
        void deleteRight(Iterator node);

        Iterator getRoot();
        Iterator getLeftChild(Iterator node);
        Iterator getRightChild(Iterator node);
        Iterator getParent(Iterator node);

        void setRoot(Iterator newRoot);

        void preorderTraversal(Iterator root);
        void postorderTraversal(Iterator root);
        void inorderTraversal(Iterator root);
        void levelOrderTraversal(Iterator root);

        bool isLeftEmpty(Iterator leftChild);
        bool isRightEmpty(Iterator rightChild);
        bool isBinaryTreeEmpty();
        bool isLeaf(Iterator node);
        bool isRoot(Iterator node);

        uint32_t getHeight();
        uint32_t calculateNodesAmount();
        uint32_t calculateMaxLevel(Iterator node);
};


template <class T>
BinaryTree<T>::BinaryTree()
{
    this->_root = nullptr;
    this->_height = 0;
}


template <class T>
BinaryTree<T>::BinaryTree(Type rootValue)
{
    this->_root = new BinaryTreeNode<T>(rootValue);
    this->_height = 0;
}


template <class T>
BinaryTree<T>::~BinaryTree()
{
    this->_erase(this->_root);
}



/**
 * Inserisce un nodo sinistra alla foglia piu' a sinistra dell'albero
 *
 * @tparam T - Tipo di dato del nodo
 * @param value - Valore della foglia
 */
template <class T>
void BinaryTree<T>::addLeftChild(Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator it = this->_root;

    while (it)
    {
        if (this->isLeftEmpty(it))
        {
            Iterator newLeftChild = new BinaryTreeNode<T>(value, it->_level + 1, it);
            it->_leftChild = newLeftChild;
            this->_updateHeight();

            return;
        }

        it = it->_leftChild;
    }

}


template <class T>
void BinaryTree<T>::addLeftChild(Iterator node, Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator leftNode = node->_leftChild;

    if (this->isLeftEmpty(leftNode))
    {
        Iterator newLeftChild = new BinaryTreeNode<T>(value, node->_level + 1, node);
        node->_leftChild = newLeftChild;
        this->_updateHeight();

        return;
    }
}


template <class T>
void BinaryTree<T>::addRightChild(Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator it = this->_root;

    while (it)
    {
        if (this->isRightEmpty(it))
        {
            Iterator newRightChild = new BinaryTreeNode<T>(value, it->_level + 1, it);
            it->_rightChild = newRightChild;

            this->_updateHeight();

            return;
        }

        it = it->_rightChild;
    }


}

template <class T>
void BinaryTree<T>::addRightChild(Iterator node, Type value)
{
    if (this->isBinaryTreeEmpty())
    {
        this->_root = new BinaryTreeNode<T>(value);
        return;
    }

    Iterator rightNode = node->_rightChild;

    if (this->isRightEmpty(rightNode))
    {
        Iterator newRightChild = new BinaryTreeNode<T>(value, node->_level + 1, node);
        node->_rightChild = newRightChild;
        this->_updateHeight();

        return;
    }

    node->_rightChild->_value = value;
}


template <class T>
void BinaryTree<T>::addLeftChild(Iterator child, Iterator parent)
{
    if (this->isLeftEmpty(parent))
    {
        parent->_leftChild = child;
        child->_parent = parent;
        this->_updateLevels(child, parent->_level);
        uint32_t childH = this->calculateMaxLevel(child);

        this->_updateHeight(childH, parent->_level);
    }
}


template <class T>
void BinaryTree<T>::addRightChild(Iterator child, Iterator parent)
{
    if (this->isRightEmpty(parent))
    {
        parent->_rightChild = child;
        child->_parent = parent;
        this->_updateLevels(child, parent->_level);
        uint32_t childH = this->calculateMaxLevel(child);

        this->_updateHeight(childH, parent->_level);
    }
}


template <class T>
void BinaryTree<T>::addLeftChild(BinaryTree<Type>* child, Iterator parent)
{
    this->addLeftChild(child->_root, parent);
}

template <class T>
void BinaryTree<T>::addRightChild(BinaryTree<Type>* child, Iterator parent)
{
    this->addRightChild(child->_root, parent);
}

template <class T>
void BinaryTree<T>::deleteLeft(Iterator node)
{
    this->_erase(node);

    if (!this->_isNodeEmpty(this->_root))
    {
        node = nullptr;

        uint32_t newH = this->calculateMaxLevel(this->_root);
        this->_height = newH;
    }
}

template <class T>
void BinaryTree<T>::deleteRight(Iterator node)
{
    this->_erase(node);

    if (!this->_isNodeEmpty(this->_root))
    {
        node = nullptr;

        uint32_t newH = this->calculateMaxLevel(this->_root);
        this->_height = newH;
    }
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
void BinaryTree<T>::levelOrderTraversal(Iterator root)
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
bool BinaryTree<T>::isLeftEmpty(Iterator leftChild)
{
    if (this->_isNodeEmpty(leftChild))
    {
        return true;
    }

    return this->_isNodeEmpty(leftChild->_leftChild);
}

template <class T>
bool BinaryTree<T>::isRightEmpty(Iterator rightChild)
{
    if (this->_isNodeEmpty(rightChild))
    {
        return true;
    }

    return this->_isNodeEmpty(rightChild->_rightChild);
}

template <class T>
bool BinaryTree<T>::isBinaryTreeEmpty()
{
    return this->_isNodeEmpty(this->_root);
}

template <class T>
uint32_t BinaryTree<T>::getHeight()
{
    return this->_height;
}

template <class T>
uint32_t BinaryTree<T>::calculateNodesAmount()
{
    Queue<Iterator> queue;
    queue.enqueue(this->_root);
    uint32_t amount = 0;

    while (!queue.isEmpty())
    {
        Iterator iter = queue.top();
        queue.dequeue();
        amount++;

        if (iter->_leftChild)
        {
            queue.enqueue(iter->_leftChild);
        }

        if (iter->_rightChild)
        {
            queue.enqueue(iter->_rightChild);
        }
    }

    return amount;
}


template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getRoot()
{
    return this->_root;
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getLeftChild(Iterator node)
{
    return node->_leftChild;
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getRightChild(Iterator node)
{
    return node->_rightChild;
}

template <class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getParent(Iterator node)
{
    return node->_parent;
}

template <class T>
bool BinaryTree<T>::isLeaf(Iterator node)
{
    return (this->isLeftEmpty(node)) && (this->isRightEmpty(node));
}


template <class T>
void BinaryTree<T>::setRoot(Iterator newRoot)
{
    this->_root = newRoot;
}


template <class T>
uint32_t BinaryTree<T>::calculateMaxLevel(Iterator node)
{
    uint32_t leftH = 0;
    uint32_t rightH = 0;

    if (this->isLeaf(node))
    {
        return 0;
    }

    if (this->isLeftEmpty(node))
    {
        leftH = 0;
    }

    else
    {
        leftH = this->calculateMaxLevel(node->_leftChild) + 1;
    }

    if (this->isRightEmpty(node))
    {
        rightH = 0;
    }

    else
    {
        rightH = this->calculateMaxLevel(node->_rightChild) + 1;
    }

    if (leftH >= rightH)
    {
        return leftH;
    }

    return rightH;
}

template <class T>
bool BinaryTree<T>::isRoot(Iterator node)
{
    return this->_isNodeEmpty(node->_parent);
}


template <class T>
bool BinaryTree<T>::_isNodeEmpty(Iterator node)
{
    return (node == nullptr);
}


template <class T>
void BinaryTree<T>::_updateHeight()
{
    uint32_t h = this->calculateMaxLevel(this->_root);

    if (h > this->_height)
    {
        this->_height++;
    }

}


template <class T>
void BinaryTree<T>::_updateHeight(uint32_t subTreeHeight, uint32_t parentH)
{
    this->_height = (subTreeHeight + parentH) - 1;
}


template <class T>
void BinaryTree<T>::_updateLevels(Iterator startingNode, uint32_t initLevel)
{
    if (!this->_isNodeEmpty(startingNode))
    {
        startingNode->_level = initLevel + 1;
        this->_updateLevels(startingNode->_leftChild, startingNode->_level);
        this->_updateLevels(startingNode->_rightChild, startingNode->_level);
    }
}

template <class T>
void BinaryTree<T>::_erase(Iterator root)
{
    if (this->isLeaf(root))
    {
        if (root != this->_root)
        {
            if (root == root->_parent->_leftChild)
            {
                root->_parent->_leftChild = nullptr;
            }

            else if (root == root->_parent->_rightChild)
            {
                root->_parent->_rightChild = nullptr;
            }

            delete root;
        }

        else
        {
            delete root;
            this->_root = nullptr;
        }
    }

    else
    {
        if (!this->isLeftEmpty(root))
        {
            this->_erase(root->_leftChild);
        }

        if (!this->isRightEmpty(root))
        {
            this->_erase(root->_rightChild);
        }

        this->_erase(root);
    }
}



#endif //STRUCTURES_BINARYTREE_H
