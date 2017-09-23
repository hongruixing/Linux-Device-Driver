#include<stdio.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include"magic.h"

#define BUFFSIZE 12
#define error(x)  x<0? perror("\nFailed\n"):printf("\nSuccess\n") 

void signal_callback_handler(int signum){

   printf("Control C triggered signal %d\n",signum);
   // Cleanup and close up stuff here

   // Terminate program
   exit(signum);
}


int main()
{
int fp,i=0;
char c = 'B',a;
int ret;
char buff;
fp = open("/dev/datto_char",O_RDWR);
 signal(SIGINT, signal_callback_handler);
//---------------------------------------	
	error(fp);
//---------------------------------------		
	ioctl(fp,IOC_WR,&c);
	while((read(fp,&buff,sizeof(buff))==sizeof(buff)) ){
	printf("%c",buff);
	}
	printf("\n");
	close(fp);	

	return 0;
}
