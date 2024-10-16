#include <iostream>
#include "C:\Users\nicky\OneDrive\Desktop\Network\Network\include\Value.h"
#include <cassert>

void test_value_operations() {
    Value a(2.0);
    Value b(-3.0);
    Value c = a * b;
    Value d = c + a;
    Value e = d.tanh();

    // Expected values before backpropagation
    std::cout << "c: " << c << std::endl; // Should show the result of 2.0 * -3.0
    std::cout << "d: " << d << std::endl; // Should show c + a
    std::cout << "e (tanh): " << e << std::endl; // Should show tanh(d)

    // Perform backpropagation
    e.backward();

    // Check gradients
    std::cout << "Gradient of a: " << a.grad << std::endl;
    std::cout << "Gradient of b: " << b.grad << std::endl;
    std::cout << "Gradient of c: " << c.grad << std::endl;

    // Example assertions (to verify the expected output)
    assert(a.grad != 0); // Replace with the actual expected value if known
    assert(b.grad != 0);
    assert(c.grad != 0);
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_value_operations();
    return 0;
}
