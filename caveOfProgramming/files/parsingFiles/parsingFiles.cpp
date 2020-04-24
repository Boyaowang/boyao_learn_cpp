#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {

  string gameCharactersFileName = "text.txt";
  ifstream gameCharacters;

  gameCharacters.open(gameCharactersFileName);

  if (!gameCharacters) {
    std::cout << "Cannot read the file" << '\n';
    return 1;
  }

   string line;
   int attackForce;

  while (gameCharacters) {
    getline(gameCharacters,line,' ');
    gameCharacters >> attackForce;

    //gameCharacters.get();
    gameCharacters >> ws;
    if (!gameCharacters) {
      break;
    }
    std::cout << line  << "-----"<< attackForce << '\n';
  }
  /**************************/
/*
  string line2;
  int attackForce2;

  while (gameCharacters >> line2 >> attackForce2) {
    std::cout << line2 << "-----"<<attackForce2 << '\n';
  };
*/ // I prefer this **************************************
  return 0;
}
