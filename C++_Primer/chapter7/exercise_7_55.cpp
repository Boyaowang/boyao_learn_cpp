#include <string>
#include <iostream>
#include <type_traits>

struct Data {
    int ival;
    std::string s;
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_literal_type<Data>::value << std::endl;
    bool a =1;
    std::cout << a << '\n';
    // output: false
}
