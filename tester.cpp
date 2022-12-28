
#include <iostream>

#include "Set/Set.h"

int main(int argc, char const *argv[])
{
    Set<int> a;
    Set<int> b;


    b.add(1);
    b.add(2);
    b.add(4);
    b.add(8);

    Set<int> u = a.unions(b);
    Set<int> i = a.intersection(b);
    Set<int> d = a.difference(b);

//    std::cout << a.isSubset(i);

    a = b;

    std::cout << a << std::endl << b;

    return 0;
}
