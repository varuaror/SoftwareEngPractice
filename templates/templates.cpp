#include <iostream>

//Function
template <typename T=int>
T func1(T in) {
  T ret;
  std::cout << in << std::endl;
  ret = in*2;
  return ret;
}

int main () {

  double ret1 = func1<double>(5.0); // explicit
  std::cout << ret1 << std::endl;

  int ret2 = func1(7); // default + compiler deduction
  std::cout << ret2 << std::endl;
  
  double  ret3 = func1(7.3); // compiler deduction
  std::cout << ret3 << std::endl;

  return 0;
}
