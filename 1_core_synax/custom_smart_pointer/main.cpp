#include <iostream>
#include "UniquePtr.h"
#include <cassert>

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

    UniquePtr<int> uptr(new int(42));
    assert(*uptr == 42);

    UniquePtr<int> uptr1(new int(5));
    UniquePtr<int> uptr2 = std::move(uptr1);
    assert(uptr1.get() == nullptr);
    assert(*uptr2 == 5);

    UniquePtr<int> uptr3(new int(10));
    int* rawPtr = uptr3.release();
    assert(uptr3.get() == nullptr);
    delete rawPtr;

    UniquePtr<int> uptr4(new int(20));
    uptr4.reset(uptr4.get()); // Should not delete and reassign itself

    return 0;
}
