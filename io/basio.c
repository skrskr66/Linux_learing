#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
  
  FILE *fp = NULL;

  fp = fopen("./tmp.txt","w+");
  if(fp == NULL){
    perror("fopen error");
    return -1;
  }
  char buf[1024] = "nihaobite\n";
  fwrite(buf, strlen(buf), 1, fp);
  
  fseek(fp,0,SEEK_SET);
  //返回值：从文件起始位置到当前跳转位置的偏移量
  memset(buf, 0x00, 1024);
  int ret = fread(buf, 1024,1,fp);
  printf("ret:%d--buf:[%s]\n",ret,buf);
  fclose(fp);
  return 0;
}
