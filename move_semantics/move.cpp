#include <iostream>

class Obj {
public:

 Obj(){}

 // Copy
 Obj(const Obj& in) {
    std::cout << "using copy constructor\n";
    this->ptr = new int(*(in.ptr));
    this->someVal = in.someVal;
 } 

 // Move
 Obj(Obj&& rValRef) {
    std::cout << "using move constructor\n";
    this->ptr = rValRef.ptr;
    this->someVal = rValRef.someVal;
    rValRef.ptr = nullptr;
 }

// Move And Swap
 Obj& operator=(Obj in) {
    std::cout << "copy and move assignment\n";
    std::swap(this->someVal, in.someVal);
    std::swap(this->ptr, in.ptr);
    return *this;
 } 

// Destructor
 ~Obj() {
    std::cout << "Deleting ptr: " << this->ptr << std::endl;
    delete ptr;
    ptr = nullptr;
 }

// +
 Obj operator+(const Obj& in) {
    Obj T{};
    T.ptr = new int(this->someVal + in.someVal);
    T.someVal = this->someVal + in.someVal;
    return T;
 }  

 int *ptr = nullptr;
 int someVal = 0;
};


int main(int argc, char** argv) {
    Obj A{};
    A.ptr = new int(5);
    A.someVal = 5;
    std::cout << "A vals\n";
    std::cout << A.someVal << std::endl;
    std::cout << A.ptr << "->" << *(A.ptr) << std::endl;

    Obj B{A};
    std::cout << "B vals\n";
    std::cout << B.someVal << std::endl;
    std::cout << B.ptr << "->" << *(B.ptr) << std::endl;

    Obj C{A + B};
    std::cout << "C vals\n";
    std::cout << C.someVal << std::endl;
    std::cout << C.ptr << "->" << *(C.ptr) << std::endl;


    Obj D = C + A;
    std::cout << "D vals\n";
    std::cout << D.someVal << std::endl;
    std::cout << D.ptr << "->" << *(D.ptr) << std::endl;

    std::cout << "finished" << std::endl;
}
