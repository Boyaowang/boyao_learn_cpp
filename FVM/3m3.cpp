#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class BoundsMatrix
{
        std::vector<T> inner_;
        unsigned int dimx_, dimy_;

public:
        BoundsMatrix (unsigned int dimx, unsigned int dimy)
                : dimx_ (dimx), dimy_ (dimy)
        {
                inner_.resize (dimx_*dimy_);
        }

        T& operator()(unsigned int x, unsigned int y)
        {
                if (x >= dimx_ || y>= dimy_)
                        throw std::out_of_range("matrix indices out of range"); // ouch
                return inner_[dimx_*y + x];
        }
};

int main(int argc, char const *argv[]) {


  BoundsMatrix<double> matrixS(9,9);
  std::vector<double> S{0,0,0,0,5,0,0,0,0};

  double dx = 0.08;
  double dy = 0.01;
  double dt = 0.0000001;
  double m = -(dx/dy);

  for (size_t i = 0; i < 6; i++) {
      matrixS(i,i+3) = 1/m;
      matrixS(i+3,i) = 1/m;
    }

  matrixS(2,2)= matrixS(6,6) = matrixS(8,8)= matrixS(0,0) = -(m+1/m);
  matrixS(1,1)= matrixS(7,7) = -(2*m+1/m);
  matrixS(3,3)= matrixS(5,5) = -(m+2/m);
  matrixS(4,4)= -2 * (m+1/m);

  for (size_t i = 0; i < 9; i++) {
    if (i==0 || i==1) {
      matrixS(i,i+1) = m;
    }
    if (i==1 || i==2) {
      matrixS(i,i-1) = m;
    }
    if (i==3 || i==4) {
      matrixS(i,i+1) = m;
    }
    if (i==4 || i==5) {
      matrixS(i,i-1) = m;
    }
    if (i==6 || i==7) {
      matrixS(i,i+1) = m;
    }
    if (i==7 || i==8) {
      matrixS(i,i-1) = m;
    }
  }

  // for (size_t i = 0; i < 9; i++) {
  //   for (size_t j = 0; j < 9; j++) {
  //     std::cout << matrixS(i,j) << "       ";
  //   }
  //   std::cout << '\n';
  // }

  // for (size_t i = 0; i < 9; i++) {
  //    std::cout << matrixS(i,i) << "       ";
  // }

  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      matrixS(i,j) *=dt;
    }
  }


//calculate
  for (size_t t = 0; t < 100000; t++) {
    for (size_t i = 0; i < 9; i++) {
      for (size_t j = 0; j < 9; j++) {
        S[i] += S[j]*matrixS(i,j);
      }
    }
  }

  for (size_t i = 0; i < S.size(); i++) {
    std::cout << S[i] << '\n';
  }

  // for (size_t i = 0; i < 9; i++) {
  //   for (size_t j = 0; j < 9; j++) {
  //     std::cout << matrixS(i,j) << "       ";
  //   }
  //   std::cout << '\n';
  // }

  // for (size_t i = 0; i < 9; i++) {
  //   for (size_t j = 0; j < 9; j++) {
  //     std::cout << matrixS(i,j) << " ";
  //   }
  //   std::cout << '\n';
  // }

  double totalS = 0;

  for (size_t i = 0; i < 9; i++) {
    totalS+= S[i];
  }







  return 0;
}
