#include <iostream>

int main(void) {
    int x = 5;
    double y = 3;
    
    [x](){
        std::cout << x << std::endl;
    }();

    [x](){
        std::cout << x*2 << std::endl;
    }();

    std::cout << x << std::endl;
    std::cout << y << std::endl;

    [&](){
        x = 4;
        y = 9;    
    }();

    std::cout << x << std::endl;
    std::cout << y << std::endl;

    [=]() mutable {
        x = 13;
        y = 15;    
        std::cout << x << std::endl;
        std::cout << y << std::endl;
    }();
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    auto p = [](){std::cout << "hello world\n";};
    std::cout << "executing lambda...\n";
    p();

    /* non-mutable lambda error
    [=](){
        x = 13; //error
        y = 15; //error   
        std::cout << x << std::endl;
        std::cout << y << std::endl;
    }();
    */

    /* compile error
    [](){
        std::cout << x << std::endl;
    }();
    */

    return 0;
}
