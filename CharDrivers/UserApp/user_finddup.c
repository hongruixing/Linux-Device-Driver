#include<stdio.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include"magic.h"

int main()
{
int fp,i=0;
char c;
int ret;

fp = open("/dev/datto_char",O_RDWR);
FILE *fp2 =fopen("test.txt","r");
 
//---------------------------------------	
	if(fp<0 && fp2<0)
	{
		perror("unable to open on of the file\n");
	}
	else
	{
		printf("both file opened\n");
	}
//---------------------------------------	
	while((c = fgetc(fp2)) != EOF){	
	ioctl(fp,IOC_WR,&c);
	ioctl(fp,IOC_RD,&c);
	printf("%c",c);
	}
	printf("\n");
	close(fp);
	fclose(fp2);	

	return 0;
}
