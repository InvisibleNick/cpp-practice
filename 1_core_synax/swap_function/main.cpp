#include <iostream>
#include <utility>

template <typename T>
void swapPointers(T* a, T* b){
    *a = std::exchange(*b, *a);
}

template <typename T>
void swapReferences(T& x, T& y){
    x = std::exchange(y, x);
}

int main(){
    int a = 10, b = 20;
    swapPointers(&a, &b);
    std::cout << "a: " << a << ", b: " << b << std::endl;  // Output: a: 20, b: 10
    
    float x = 5.5, y = 9.9;
    swapReferences(x, y);
    std::cout << "x: " << x << ", y: " << y << std::endl;  // Output: x: 9.9, y: 5.5
}


