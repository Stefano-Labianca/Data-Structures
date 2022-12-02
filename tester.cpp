
#include <iostream>
#include "./Queue/Queue.h"
#include "./Queue/ArrayQueue.h"

int main(int argc, char const *argv[])
{
    Queue<int> queue;
    ArrayQueue<int> arrQueue;

    // queue.enqueue(9);
    // queue.enqueue(3);
    // queue.enqueue(39);  

    arrQueue.enqueue(9);
    arrQueue.enqueue(3);
    arrQueue.enqueue(39);  

    ArrayQueue<int> arrQ = arrQueue;

    std::cout << (arrQueue == arrQ) << std::endl;


    return 0;
}
