
#include <iostream>

#include "SortedLinkedList/SortedLinkedList.h"

int main(int argc, char const *argv[])
{
    SortedLinkedList<int> sList(10);

    sList.add(49);
    sList.add(6);
    sList.add(12);
    sList.add(88);
    sList.add(49);

    SortedLinkedList<int> sortedLinkedList;
    sortedLinkedList = sList;

    std::cout << sList << std::endl;
    std::cout << sortedLinkedList << std::endl;

    std::cout << (sortedLinkedList == sList) << std::endl;
    std::cout << (sortedLinkedList != sList) << std::endl;

    sortedLinkedList.remove(2);

    std::cout << (sortedLinkedList == sList) << std::endl;
    std::cout << (sortedLinkedList != sList) << std::endl;


    return 0;
}
