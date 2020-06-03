#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {

  std::vector<int> gradeList = {65, 67, 90, 100, 88, 85, 75, 55, 45, 100, 62, 82, 71};
  std::vector<string> gradeLevel = {"F","D","C","B","A","A++"};

  string finalGrade;

  for (std::vector<int>::iterator it = gradeList.begin(); it != gradeList.end(); it++) {
    if (*it<60) {
      std::cout << "The score is "<< gradeLevel[0] << '\n';
    }else{
      finalGrade = gradeLevel[(*it-50)/10];
      if (*it != 100) {
        if ((*it%10)>7) {
        finalGrade+= '+';
      }else if ((*it%10)<3) {
        finalGrade+= '-';
      }
      }
      std::cout << "The score is " << finalGrade << '\n';
    }
  }

  return 0;
}
