#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){
	int fd = open("/dev/nextchar",O_RDWR);
	char temp;
	if(fd<0){
		printf("Failed to open file\n");
		exit(1);
	}

	if(write(fd,"A", 1) < 0)
	{
		printf("Failed to write file\n");
		exit(1);


}
	//close(fd);
	lseek(fd,0,SEEK_SET);	

/*	fd = open("/dev/nextchar",O_RDWR);
	if(fd<0){
		printf("Failed to open file\n");
		exit(1);
	}

*/	if(read(fd,&temp, 1) < 0)
	{
		printf("Failed to read file\n");
		exit(1);
}
	
	printf("Value from kernel space is %c\n",temp);

	close(fd);

return 0;
}
