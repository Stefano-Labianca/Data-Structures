#ifndef _IQUEUE_H
#define _IQUEUE_H

#include <iostream>
#include <ostream>


template <class T, class I>
class IQueue
{
    public:
        typedef T Type;
        typedef I Iterator;

        virtual bool isEmpty() const = 0;
        virtual std::size_t getLength() const = 0;

        virtual Type read(const Iterator pos) const = 0;
        virtual void write(const Type& item, Iterator pos) = 0;

        virtual void enqueue(const Type& item) = 0;
        virtual void dequeue() = 0;
        virtual Type top() const = 0;        
        
        virtual Iterator begin() const = 0;
        virtual Iterator end() const = 0;
        virtual bool isEnd(const Iterator& pos) const = 0;
        virtual Iterator next(Iterator& pos) const = 0;


        template <class V, class U>
        friend std::ostream& operator<<(std::ostream& out, const IQueue<V, U>& queue);
};


template <class V, class U>
std::ostream& operator<<(std::ostream& out, const IQueue<V, U>& queue)
{
    U it = queue.begin();
    bool isFirst = false;

    while (!queue.isEnd(it))
    {
        out << "[ " << queue.read(it) << " ]";
        it = queue.next(it);
    }

    return out;
}




#endif // _IQUEUE_H