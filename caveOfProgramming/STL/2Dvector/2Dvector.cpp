#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

  vector<vector<int>> grid(3, vector<int>(9,7)); //3 rows and 2 columns initialized to 7

  std::cout << "The row size of grid is "<< grid.size() << '\n';
  std::cout << "The column size of the grid is "<< grid[1].size() << '\n';

  grid[1].push_back(565656);
  
  for (int row = 0; row < grid.size() ; row++) {
    for (int col = 0; col < grid[row].size(); col++) {
      std::cout << grid[row][col] << ' ';
    }
    std::cout << '\n';
  };

  return 0;
}
