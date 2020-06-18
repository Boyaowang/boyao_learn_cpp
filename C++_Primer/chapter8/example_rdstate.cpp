#include<iostream>
#include <vector>
#include<istream>

std::istream & print(std::istream &is) {
    static unsigned cnt = 0;
    ++cnt;
    std::cout << cnt << ((cnt % 10 == 1) ? "st" :
        (cnt % 10 == 2) ? "nd" : "th")
        << " call print" << "\n";

    std::cout<< "is.badbit: " << is.badbit << "\n"
        << "is.failbit: " << is.failbit << "\n"
        << "is.eofbit: " << is.eofbit << "\n"
        << "is.bad(): " << is.bad() << "\n"
        << "is.fail(): " << is.fail() << "\n"
        << "is.eof(): " << is.eof() << "\n"
        << "is.rdstate(): " << is.rdstate() << "\n";
    return is;
}

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    cout << "sizeof(iostate): " <<sizeof(std::istream::iostate)<<"\n";
    cout << "sizeof(goodbit): " << sizeof(std::istream::goodbit) << "\n";
    cout << typeid(std::istream::goodbit).name();
    cout << endl;

    print(cin);
    cout << endl;

    cin.setstate(std::istream:: badbit);
    print(cin);
    cout << endl;

    cin.clear();
    cin.setstate(std::istream::failbit);
    print(cin);
    cout << endl;

    cin.clear();
    cin.setstate(std::istream::eofbit);
    print(cin);
    cout << endl;


    cin.clear();
    cin.setstate(std::istream::badbit);
    cin.setstate(std::istream::failbit);
    print(cin);
    cout << endl;

    cin.clear();
    cin.setstate(std::istream::badbit);
    cin.setstate(std::istream::eofbit);
    print(cin);
    cout << endl;

    cin.clear();
    cin.setstate(std::istream::failbit);
    cin.setstate(std::istream::eofbit);
    print(cin);
    cout << endl;
}
