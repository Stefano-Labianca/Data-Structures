
#include <iostream>
#include "./Queue/Queue.h"


int main(int argc, char const *argv[])
{
    Queue<int> queue;

    queue.enqueue(9);
    queue.enqueue(3);
    queue.enqueue(39);  

    Queue<int> q(queue);

    std::cout << (q == queue) << std::endl;
    std::cout << (q != queue) << std::endl;
    std::cout << q << std::endl;

    q.dequeue();
    std::cout << q << std::endl;

    return 0;
}
    