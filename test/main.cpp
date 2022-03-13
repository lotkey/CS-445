#include <iostream>
#include <string>

int main() {
    float x = 1.1;
    {
        int x = x * 10;
        std::cout << x << std::endl;
    }
}