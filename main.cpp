#include <iostream>
#include <add.hpp>

int main() {
    std::cout << "Hello, World!\n2 + 2 is "
        << add(2, 2)
        << "\nAnd this is a Travis Test!"
        << std::endl;
    return 0;
}
