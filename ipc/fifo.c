/*命名管道的基本使用
 * int mkfifo(const char *pathname, mode_t mode);
 *    pathname : 管道文件名
 *    mode: 创建权限 0664
 *    返回值： 0 失败 -1
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
int main(){
  char *file = "./test.fifo";
  umask(0);
  int ret = mkfifo(file,0664);
  if(ret < 0){
    if(errno != EEXIST){
    perror("mkfifo error");
    return -1;
    }
  }
}
