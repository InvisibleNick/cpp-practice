#include <iostream>
#include <utility>
#include <cassert>

template <typename T>
void swapPointers(T* a, T* b){
    if(a == b)
        throw std::invalid_argument("Same pointers");
    if (!std::is_same<decltype(*a), decltype(*b)>::value)
        throw std::invalid_argument("Different types");
    if (a == nullptr || b == nullptr){
        a = std::exchange(b, a);
        std::cout << a << " " << b << std::endl;
        return;
    }

    *a = std::exchange(*b, *a);
}

template <typename T>
void swapReferences(T& x, T& y){
    if (!std::is_same<decltype(x), decltype(y)>::value)
        throw std::invalid_argument("Different types");
    x = std::exchange(y, x);
}

int main(){
    int a = 10, b = 20;
    swapPointers(&a, &b);
    assert(a == 20 && b == 10);
    swapReferences(a, b);
    assert(a == 10 && b == 20);


    float x = 5.5, y = 9.9;
    swapReferences(x, y);
    assert(x > 9.8 && x < 10.0 && y > 5.4 && y < 5.6);
    swapPointers(&x, &y);
    assert(x > 5.4 && x < 5.6 && y > 9.8 && y < 10.0);

    double m = 3.3, n = 7.7;
    swapPointers(&m, &n);
    assert(m == 7.7 && n == 3.3);
    swapReferences(m, n);
    assert(m == 3.3 && n == 7.7);

    char c = 'a', d = 'b';
    swapReferences(c, d);
    assert(c == 'b' && d == 'a');
    swapPointers(&c, &d);
    assert(c == 'a' && d == 'b');

    int *ptr1 = &a, *ptr2 = nullptr;
    swapPointers(ptr1, ptr2);
    assert(ptr1 == nullptr);
    assert(*ptr2 == 10);

    std::cout << "Done" << std::endl;
}


