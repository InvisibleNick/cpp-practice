#include <iostream>
#include "UniquePtr.h"

class Test {
public:
    Test() { std::cout << "Test object created\n"; }
    ~Test() { std::cout << "Test object destroyed\n"; }
    void sayHello() { std::cout << "Hello from Test!\n"; }
};

int main() {
    UniquePtr<Test> ptr(new Test());
    ptr->sayHello();  // Access using operator->

    UniquePtr<Test> movedPtr = std::move(ptr);  // Ownership transferred
    if (!ptr.get()) {
        std::cout << "Pointer has been moved!\n";
    }

    return 0;
}
