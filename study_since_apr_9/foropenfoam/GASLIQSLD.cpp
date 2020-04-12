#include <iostream>
using namespace std;

typedef int label;

template<class ParcelType>
class ReactingMultiphaseParcel:public ParcelType
{
public:
        static const label GAS;
        static const label LIQ;
        static const label SLD;
};

//const label ReactingMultiphaseParcel<ParcelType>::GAS(1);
//const label ReactingMultiphaseParcel::GAS(0);
/*
template<class ParcelType>
const label ReactingMultiphaseParcel<ParcelType>::LIQ(1);

template<class ParcelType>
const label ReactingMultiphaseParcel<ParcelType>::SLD(2);
*/
int main(int argc, char const *argv[]) {
  //ReactingMultiphaseParcel boyao;
  //std::cout << boyao.GAS << '\n';
  return 0;
}
