#include "testTypeInheritance.h"

// * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * * //

template<class Type>
Foam::demandDrivenEntry<Type>::demandDrivenEntry
(
    const Type& value
)
:
    value_(value)
{};

template<class T>
template<class TrackCloudType>
void Foam::boyaowang<T>::setCellValues
(
    TrackCloudType& cloud,
    trackingData& td
)
{
    T::setCellValues(cloud, td);
}


int main(int argc, char const *argv[]) {
  using namespace Foam;
  //jiechenbaba Jessie;
  //typedef jiechen<jiechenbaba> typea;
  //demandDrivenEntry<jiechen> boyao(Jessie);
  typedef jiechen<jiechenbaba> typea;
  typedef demandDrivenEntry<jiechen<jiechenbaba>> typeb;
  demandDrivenEntry<jiechen<jiechenbaba>> boyao2;
  //boyaowang<demandDrivenEntry> boyao2(15,20);
  return 0;
}
