#include <iostream>

int main(int argc, char const *argv[]) {
  printf("what is the vlaue of argc = %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("The %dth value of argv[%d] is = %s\n",i,i, argv[i] );
  }

  return 0;
}
