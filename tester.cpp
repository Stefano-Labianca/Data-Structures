#include "./Stack/Stack.h"
#include "./Stack/ArrayStack.h"

#include <iostream>


int main(int argc, char const *argv[])
{
    ArrayStack<int> arrayStack;
    
    arrayStack.push(10);
    arrayStack.push(20);
    arrayStack.push(30);
    arrayStack.push(40);

    ArrayStack<int> arr(arrayStack);

    std::cout << std::endl << arr[2] << std::endl;
    std::cout << std::endl << (arr != arrayStack) << std::endl;



    return 0;
}
    