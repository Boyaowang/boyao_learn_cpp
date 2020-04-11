#include <iostream>
#include "name1.h"
#include "name2.h"
using namespace std;


#define Scalar 

class Istream;

/*---------------------------------------------------------------------------*\
                           Class pTraits Declaration
\*---------------------------------------------------------------------------*/

template<class PrimitiveType>
class pTraits:
    public PrimitiveType
{

public:

    // Constructors

        //- Construct from primitive
        pTraits(const PrimitiveType& p):PrimitiveType(p)
        {}
        //- Construct from Istream
        pTraits(Istream& is):PrimitiveType(is)
        {}
};

template<>
class pTraits<Scalar>
{
    Scalar p_;

public:

    //- Component type
    typedef Scalar cmptType;

    //- Equivalent type of labels used for valid component indexing
    typedef label labelType;


    // Member constants

        //- Dimensionality of space
        static const direction dim = 3;

        //- Rank of Scalar is 0
        static const direction rank = 0;

        //- Number of components in Scalar is 1
        static const direction nComponents = 1;


    // Static data members

        static const char* const typeName;
        static const char* const componentNames[];
        static const Scalar zero;
        static const Scalar one;
        static const Scalar max;
        static const Scalar min;
        static const Scalar rootMax;
        static const Scalar rootMin;


    // Constructors

        //- Construct from primitive
        explicit pTraits(const Scalar& val);

        //- Construct from Istream
        pTraits(Istream& is);


    // Member Functions

        //- Access to the value
        operator Scalar() const
        {
            return p_;
        }

        //- Access to the value
        operator Scalar&()
        {
            return p_;
        }
};


int main(int argc, char const *argv[]) {
  food::east food1;
  food::west food2;
  food1.outputavalue();
  //Scalar a;
  return 0;
}
