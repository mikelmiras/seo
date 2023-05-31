#include <stdio.h>  // printf funtzioa erabili ahal izateko (man 3 printf)

int main(int argc, char *argv[]) {
  int i;
  for (i = 0; i < 100000; ++i) {
    printf("kaixo!\n");
  }
  return 0;
}
