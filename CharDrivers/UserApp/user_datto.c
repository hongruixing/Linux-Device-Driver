#include<stdio.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include"magic.h"
#define BUFFSIZE 64
int main()
{
int fp,i=0;
char c = 'B';
int ret;
char buffer[BUFFSIZE];
fp = open("/dev/datto_char",O_RDWR);
 
//---------------------------------------	
	if(fp<0)
	{
		perror("unable to open on of the file\n");
	}
	else
	{
		printf("both file opened\n");
	}
//---------------------------------------	
	//while((c = fgetc(fp2)) != EOF){	
	ioctl(fp,IOC_WR,&c);
	//ioctl(fp,IOC_RD,&c);
	read(fp,buffer,sizeof(buffer));
	printf("%s",buffer);
	
	printf("\n");
	close(fp);	

	return 0;
}
