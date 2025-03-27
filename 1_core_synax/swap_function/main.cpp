#include <iostream>      // For std::cout
#include <utility>       // For std::swap (not used here, but could be an alternative)
#include <cassert>       // For assert()
#include <cmath>         // For std::abs in floating-point comparisons
#include <stdexcept>     // For std::invalid_argument

// Swap values pointed to by a and b
// Throws exceptions if pointers are null or identical
template <typename T>
void swapPointers(T* a, T* b){
    if(a == nullptr || b == nullptr)
        throw std::invalid_argument("Null pointer");
    if(a == b)
        throw std::invalid_argument("Same pointers");

    T tmp = *a;  // Copy value pointed by a
    *a = *b;     // Assign value from b to a
    *b = tmp;    // Assign stored value to b
}

// Swap values passed by reference
template <typename T>
void swapReferences(T& x, T& y){
    T tmp = x;  // Copy x
    x = y;      // Assign y to x
    y = tmp;    // Assign stored value to y
}

int main(){
    int a = 10, b = 20;
    swapPointers(&a, &b);                            // Swapping using pointers
    assert(a == 20 && b == 10);                      // Validate the swap
    swapReferences(a, b);                            // Swapping using references
    assert(a == 10 && b == 20);

    float x = 5.5f, y = 9.9f;
    swapReferences(x, y);                            // Swap floats using references
    assert(std::abs(x - 9.9f) < 0.01f &&              // Use tolerance for float comparison
           std::abs(y - 5.5f) < 0.01f);
    swapPointers(&x, &y);                            // Swap floats using pointers
    assert(std::abs(x - 5.5f) < 0.01f &&              // Check correctness with tolerance
           std::abs(y - 9.9f) < 0.01f);

    double m = 3.3, n = 7.7;
    swapPointers(&m, &n);                            // Swap doubles using pointers
    assert(std::abs(m - 7.7) < 0.0001 &&              // Double comparison with tighter tolerance
           std::abs(n - 3.3) < 0.0001);
    swapReferences(m, n);                            // Swap doubles using references
    assert(std::abs(m - 3.3) < 0.0001 &&
           std::abs(n - 7.7) < 0.0001);

    char c = 'a', d = 'b';
    swapReferences(c, d);                            // Swap chars by reference
    assert(c == 'b' && d == 'a');
    swapPointers(&c, &d);                            // Swap chars by pointer
    assert(c == 'a' && d == 'b');

    std::cout << "Done" << std::endl;                // Output result
    return 0;                                        // Return success
}
