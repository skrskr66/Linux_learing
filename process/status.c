#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
int main(){
  u_int64_t a = 0;
  fork();
  while(1){
    a++;
    usleep(1000);
  }
  return 0;
}

