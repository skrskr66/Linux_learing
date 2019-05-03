#include<stdio.h>
#include<unistd.h>


int main(){
	printf("parent pid:%d\n",getpid());	
	pid_t pid = fork();
	if(pid < 0){
	return 0 ;
}else if (pid==0){
	printf("child pid:%d\n",getpid());
}else{
	printf("parents\n");
}
	printf("nihaoa\n");
	return 0;
}


