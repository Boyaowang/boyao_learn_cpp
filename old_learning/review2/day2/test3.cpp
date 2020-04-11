#include<iostream>
using namespace std;

class Accumulator{
private:
    int value;
public:
    Accumulator(int value){this->value=value;}
    Accumulator& add(int n){value+=n;}
    int get(){return value;};
};

int main(int argc, char* argv[]){
    Accumulator acc(10);
    acc.add(5).add(6).add(7); //<-----how does this work?????
    cout<<acc.get();
    return 0;
}
