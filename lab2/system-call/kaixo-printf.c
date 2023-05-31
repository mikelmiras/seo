#include <stdio.h>  // printf funtzioa erabili ahal izateko (man 3 printf)

int main(int argc, char *argv[]) {
  int i;
  for (i = 0; i < 2; ++i) {
    printf("kaixo!");
  }
  write(1, "Agur", 5);
  return 0;
}
