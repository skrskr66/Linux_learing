#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
  int ret;
  FILE *fp = NULL;
  fp = fopen("./tmp.txt","r+");
  if(fp == NULL){
    perror("打开失败");
    return -1;
  }
  fseek(fp ,10,SEEK_SET);

  char *ptr = "nihao---\n";

  ret = fwrite(ptr, 1,strlen(ptr), fp);
  printf("write item:%d\n",ret);

  fseek(fp, 0, SEEK_SET);
  char buf[1024] = {0};

  ret = fread(buf, 1, 1023, fp);
  perror("fread error");
  printf("read buf[%s]-ret[%d]\n",buf,ret);

  fclose(fp);
  return 0;
}
