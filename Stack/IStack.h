#ifndef _ISTACK_H
#define _ISTACK_H

#include <iostream>
#include <ostream>
#include <exception>
#include <string>

template <class T, class I>
class IStack
{
    public:
        typedef T Type;
        typedef I Iterator;

        virtual bool isEmpty() const = 0;
        virtual Type peek() const = 0;
        virtual void push(const Type& item) = 0;
        virtual void pop() = 0;    

        virtual Iterator end() const = 0;
        virtual Iterator begin() const = 0;
        virtual Iterator next(Iterator pos) const = 0;

        virtual Type read(const Iterator pos) const = 0;
        virtual bool isEnd(const Iterator pos) const = 0;

        template <class V, class U>
        friend std::ostream& operator<<(std::ostream& out, const IStack<V, U>& stack);
};

template <class V, class U>
std::ostream& operator<<(std::ostream& out, const IStack<V, U>& stack)
{
    U it = stack.begin();

    while (!stack.isEnd(it))
    {
        if (stack.isEnd(stack.next(it)))
        {
            out << "[ " << stack.read(it) << " ]";
        }

        else
        {
            out << "[ " << stack.read(it) << " ] -> ";
        }

        it = stack.next(it);
    }

    return out;
}



#endif // _ISTACK_H