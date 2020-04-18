#ifndef demandDrivenEntry_H
#define demandDrivenEntry_H
#include <iostream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class demandDrivenEntry Declaration
\*---------------------------------------------------------------------------*/
class jiechenbaba
{
public:
  jiechenbaba(){
    std::cout << "jiechenbaba" << '\n';
  };
};

template<class T>
class jiechen:
public T
{
public:
  jiechen(){
    std::cout << "jiechen" << '\n';
  };
};


template<class Type>
class demandDrivenEntry
:public Type
{
    // Private Data

        //- Value
        Type value_;


public:

    //- Constructors

        //- Construct from dictionary and value - cannot be re-read
        demandDrivenEntry
        (
            const Type& value
        );
        demandDrivenEntry(){};

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
template<class T>
class wang
:public demandDrivenEntry<T>
{};
//****************************************************************************//

template<class T>
class boyaowang
:public T
{
public:
    int a, b;
    boyaowang(int a, int b):a(a), b(b){};
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
  class constantProperties
    :
        public T::constantProperties
    {

    };
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    typedef typename T::trackingData trackingData;
public:
    template<class TrackCloudType>
    void setCellValues(TrackCloudType& cloud, trackingData& td);
};


} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif
