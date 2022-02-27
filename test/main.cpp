#include <iostream>
#include <string>

class Test {
  public:
    bool isnullptr() {
        if (this == nullptr)
            return true;
        else
            return false;
    }
};

int main() {
    Test *t = nullptr;
    std::cout << t->isnullptr() << std::endl;
}