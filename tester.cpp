#include "Dictionary/Dictionary.h"

#include <string>

int main(int argc, char const *argv[])
{
    Dictionary<std::string, int> dictionary(1);
    Dictionary<std::string, int> d(5);

    dictionary.insert("One", 1);
    dictionary.insert("Two", 2);
    dictionary.insert("Three", 3);

    d.insert("A", 1);
    d.insert("V", 2);
    d.insert("E", 3);


    std::cout << dictionary.isSubset(d);


    return 0;
}
