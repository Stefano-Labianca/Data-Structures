
#include <iostream>
#include "./Queue/Queue.h"
#include "./Queue/ArrayQueue.h"

int main(int argc, char const *argv[])
{
    Queue<int> queue;
    ArrayQueue<int> arrQueue;

    arrQueue.enqueue(9);
    arrQueue.enqueue(3);
    arrQueue.enqueue(39);
    arrQueue.enqueue(19);

    ArrayQueue<int> arrQ;
    arrQ.enqueue(10);
    arrQ.enqueue(20);

    std::cout << (arrQueue != arrQ) << std::endl;


    return 0;
}
