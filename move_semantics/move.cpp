#include <iostream>
#include <utility>

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
    std::cout << "Deleting ptr: " << this->ptr << " for " << this << std::endl;
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    } 
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
    std::cout << "A vals (" << &A << ")\n";;
    std::cout << A.someVal << std::endl;
    std::cout << A.ptr << "->" << *(A.ptr) << std::endl;

    Obj B{A};
    std::cout << "B vals (" << &B << ")\n";;
    std::cout << B.someVal << std::endl;
    std::cout << B.ptr << "->" << *(B.ptr) << std::endl;

    Obj C{A + B}; // won't work -- copy ellision
    std::cout << "C vals (" << &C << ")\n";;
    std::cout << C.someVal << std::endl;
    std::cout << C.ptr << "->" << *(C.ptr) << std::endl;


    Obj D = C + A; // won't work -- copy ellision
    std::cout << "D vals (" << &D << ")\n";;
    std::cout << D.someVal << std::endl;
    std::cout << D.ptr << "->" << *(D.ptr) << std::endl;

    // Dangerous, D can still be manipulated afterward
    Obj E = std::move(D); // casts lvalue D into rvalue to use move constructor
    std::cout << "E vals (" << &E << ")\n";;
    std::cout << E.someVal << std::endl;
    std::cout << E.ptr << "->" << *(E.ptr) << std::endl;
    

    std::cout << "finished" << std::endl;
}
