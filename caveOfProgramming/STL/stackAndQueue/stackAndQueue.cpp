#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class test {
private:
  string name;

public:
  test (string name):name(name){};
  virtual ~test (){
    // /std::cout << "call destructor" << '\n';
  };
  void print() {
    std::cout << name << '\n';
  }
};

int main(int argc, char const *argv[]) {
  //stack last in first out!!!
  stack<test> testStack;

  testStack.push(test("jiechen"));
  testStack.push(test("zixin"));
  testStack.push(test("jianbiao"));
  testStack.push(test("zhongwei"));

  while (!testStack.empty()) {
    test &top = testStack.top();
    std::cout << "Top of the stack is: ";
    top.print();
    std::cout << "The size of the stack is: "<< testStack.size() << '\n';
    testStack.pop();
  }
/*
  test &top = testStack.top(); //check last in first out, like a stack of plates
  top.print();

  testStack.pop(); // remove the element on top

  test &top2 = testStack.top(); //check last in first out, like a stack of plates
  top2.print();
*/
  //queue is just the opposite to the stack which is first in first out
  std::cout << "**************start looking at queue **********************" << '\n';
  queue<test> testQueue;

  testQueue.push(test("jiechen"));
  testQueue.push(test("zixin"));
  testQueue.push(test("jianbiao"));
  testQueue.push(test("zhongwei"));

  while (!testQueue.empty()) {
    //test &top = testQueue.front();
    std::cout << "Top of the queue is: ";
    testQueue.front().print();
    std::cout << "The size of the queue is: "<< testQueue.size() << '\n';
    testQueue.pop();
  }
  return 0;
}
