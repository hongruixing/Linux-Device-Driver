#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main(){

	int fp;
	char buffer[] = "hello from userspace";
	char buffer[sizeof(buffer)];
	fp = open("/dev/uppercase", O_RDWR);

	if(fp <0)
	{
		printf("failed to open the file\n");
	}

	printf("Check the dmesg for successful file opening\n");
	
			
	write(fp,buffer, sizeof(buffer));
		
	lseek(fp,0,SEEK_SET);
	read(fp,buffer1,sizeof(buffer1));
	printf("%s\n",buffer1);

	close(fp);
	printf("File closed check dmesg\n");


return 0;
}
