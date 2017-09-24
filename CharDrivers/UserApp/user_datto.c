#include<stdio.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include"magic.h"

#define BUFFSIZE 50


int main()
{
int fd;
char c = '0';
int ret;
char read_buff[BUFFSIZE];
fd = open("/dev/datto_char",O_RDWR);
 	if(read(fd,&read_buff,sizeof(read_buff))<0){
		perror("read error");	
	}
	 if(ioctl(fd,IOC_WR,&c)){
		perror("IOCTL error");
	}
	
	if(read(fd,&read_buff,sizeof(read_buff))){
		perror("read error");
	}
	printf("%s\n",read_buff);
	close(fd);	

	return 0;
}
