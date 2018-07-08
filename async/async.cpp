#include <thread>
#include <iostream>
#include <chrono>
#include <future>

void dumbFunc() {
  std::cout << "hello world\n";
}
void dumbFunc2() {
  std::cout << "hello world 2\n";
}
int async1() {
    return 99;
}

int main(void) {

//Threads
  std::thread t1(dumbFunc); 
  std::cout << "t1 ID = " << t1.get_id() << "\n";
  std::thread t2;
  std::cout << "made empty thread obj t2\n";
  std::cout << "t2 ID = " << t2.get_id() << "\n";
  std::cout << "Is t2 joinable: " << t2.joinable() << std::endl;
  //t2.join(); -- throws exception to be caught
  t2 = std::thread(dumbFunc2);
  std::cout << "Moved a thread obj into t2\n";
  std::cout << "t2 ID = " << t2.get_id() << "\n";
  std::cout << "Is t2 joinable: " << t2.joinable() << std::endl;

  std::thread t3([](int a, int b){std::this_thread::sleep_for(std::chrono::seconds(3)); std::cout << a << " " << b << std::endl;}, 5, 10);
  t3.detach();

  if (t1.joinable()) {
    t1.join();
    std::cout << "joined t1 ID = " << t1.get_id() << "\n";
    std::cout << "Is t1 joinable: " << t1.joinable() << std::endl;
  }
  if (t2.joinable()) {
    t2.join();
    std::cout << "joined t2 ID = " << t2.get_id() << "\n";
    std::cout << "Is t2 joinable: " << t2.joinable() << std::endl;
  }
  if (t3.joinable()) {
    t3.join();
  } else {
    std::cout << "t3 is not joinable\n";
  }
  //t3.join(); -- failure, no such process, throws exception

//Async
    //std::async sync1(dumbFunc); -- error, cannot create async obj this way
    std::async(dumbFunc); // useless
    std::future<int> f1;
    //std::future_status stat = f1.wait_for(std::chrono::seconds(1)); -- segfault, f1 is not valid yet
    //if (stat == std::future_status::deferred) {
    //    std::cout << "future f1 didn't start yet\n";
    //}
    f1 = std::async(async1);
    std::future_status stat = f1.wait_for(std::chrono::seconds(1));
    if (stat == std::future_status::ready) {
    std::cout << "got value from async = " << f1.get() << std::endl;
    }

//Packaged_Task


  return 0;
}
