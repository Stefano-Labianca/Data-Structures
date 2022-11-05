#ifndef _ISTACK_H
#define _ISTACK_H

#include <iostream>
#include <ostream>

template <class T, class I>
class IStack
{
    public:
        virtual bool isEmpty() const = 0;
        virtual T peek() const = 0;
        virtual void push(const T& item) = 0;
        virtual I pop() = 0;    
        virtual I getTopNode() const = 0;

        template <class V, class U>
        friend std::ostream& operator<<(std::ostream& out, const IStack<V, U>& stack);

};

template <class V, class U>
std::ostream& operator<<(std::ostream& out, const IStack<V, U>& stack)
{
    U it = stack.getTopNode();

    while (it)
    {
        if  (it->getNodeNext() == nullptr)
        {
            out << "[ " << it->getNodeValue() << " ]" << std::endl;
        }

        else
        {
            out << "[ " <<it->getNodeValue() << " ] -> ";
        }

        it = it->getNodeNext();
    }


    return out;
}

#endif // _ISTACK_H