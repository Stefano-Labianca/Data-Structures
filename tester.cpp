#include "./Stack/Stack.h"
#include "./Stack/ArrayStack.h"

#include <iostream>


int main(int argc, char const *argv[])
{
    ArrayStack<int> arrayStack;
    Stack<int> stack;

    arrayStack.push(10);
    arrayStack.push(20);
    arrayStack.push(30);
    arrayStack.push(40);

    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);

    std::cout << std::endl << arrayStack << std::endl;
    std::cout << std::endl << stack << std::endl;



    return 0;
}
    