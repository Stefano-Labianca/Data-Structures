#ifndef ILINKED_LIST_H
#define ILINKED_LIST_H

#include <iostream>
#include <ostream>

template <class T, class I>
class ILinkedList
{
    public:
        virtual unsigned int getSize() const = 0;
        virtual bool isEmpty() const = 0;

        virtual I find(unsigned int index) const = 0;
        virtual void replace(const T& value, unsigned int index) = 0;
        virtual void insert(const T& value, unsigned int index) = 0;

        virtual void unshift(const T& value) = 0;
        virtual void append(const T& value) = 0;
        virtual void shift() = 0;
        virtual void deleteLast() = 0;
        virtual void remove(unsigned int index) = 0;

        virtual I begin() const = 0;
        virtual I end() const = 0;

        template <typename V, typename U>
        friend std::ostream& operator<<(std::ostream& out, const ILinkedList<V, U>& list);

};


template <class V, class U>
std::ostream& operator<<(std::ostream& out, const ILinkedList<V, U>& list)
{
    out << "{";

    U it = list.begin();

    while (it.get())
    {
        if  (it == list.end())
        {
            out << it->getNodeValue();
        }

        else
        {
            out << it->getNodeValue() << " -> ";
        }

        it = it->getNext();
    }
    
     out << "}" << std::endl;

    return out;
}


#endif // ILINKED_LIST_H