#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[]){
  //main函数的参数值是从操作系统命令行上获得的。当我们要运行一个可执行文件时，在DOS提示符下键入文件名，再输入实际参数即可把这些实参传送到main的形参中去。
  //C:\>可执行文件名 参数 参数……
  //argv参数是字符串指针数组，其各元素值为命令行中各字符串(参数均按字符串处理)的首地址
  //env：字符指针的数组，每一个元素是指向一个环境变量的字符指针
  int i;
  for(i = 0;i < argc; i++){
    printf("argv[%d]=[%s]\n",i , argv[i]);
  }
  extern char **environ;
  for(i = 0;environ[i] != NULL;i++){
    printf("env[%d]=[%s]\n",i, environ[i]);
  }
  char *ptr = getenv("MYENV");
  printf("MYENV:[%s]\n",ptr);
  return 0;
}
