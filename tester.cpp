// #include "./LinkedList/LinkedList.h"
#include "./Node.h"

#include <iostream>
#include <memory>

int main(int argc, char const *argv[])
{
    std::unique_ptr<Node<int>> first(new Node<int>(10));
    std::unique_ptr<Node<int>> third(new Node<int>(30, first));

    Node<int>& node = third->copy();
    std::cout << node;

    // LinkedList<int> list;
    
    // list.append(1);
    // list.append(2);
    // list.append(3);
    // list.append(4);
    // list.append(5);

    // std::shared_ptr<Node<int>> node = list.find(1);

    // // list.replace(6, 2);
    // // list.replace(9, list.getSize() - 1);
    // // list.replace(10, 0);

    // list.insert(7, 3);
    // list.remove(3);

    // LinkedList<int> list2(list);
    // std::cout << list << std::endl;

    // std::cout << list2;

    return 0;
}
    