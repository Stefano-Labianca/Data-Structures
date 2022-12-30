
#include <iostream>

#include "LinkedList/ArrayLinkedList.h"
#include "Set/Set.h"

int main(int argc, char const *argv[])
{
    ArrayLinkedList<int> a1(2);
    ArrayLinkedList<int> a2(2);

    a1.append(1);
    a1.append(2);

    a2.append(1);

    std::cout << a1;
    std::cout << a2;


    return 0;
}
