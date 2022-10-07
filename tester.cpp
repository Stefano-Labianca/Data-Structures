#include "./LinkedList/LinkedList.h"

#include <iostream>

#include "Node.h"

int main(int argc, char const *argv[])
{

    Node<int> al(10);
    Node<int> am(20, &al);
    Node<int> at(am);


    LinkedList<int> list;

    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    list.insert(8, 1);

    std::cout << list;

    list.remove(1);

    std::cout << list;


    return 0;
}
    