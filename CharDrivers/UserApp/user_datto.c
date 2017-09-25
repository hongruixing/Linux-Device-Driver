///////////////////////////////////////////////////////////////////
//  user_datto.c - Testing read() & ioctl() system calls on      //
//                  a Single Character Driver                    //
//  version - 1.0                                                //
//  Author - Vishal Verma , Syracuse University, vvverma@syr.edu //
///////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include"magic.h"

#define BUFFSIZE 128



//===================Test stub for testing the character driver=================
int main(void){
int file_desc;
char input;
char read_buff[BUFFSIZE];
const char *file_path ="/dev/datto_char"; 

	printf("\nStarting the user_datto to test the Single Character Driver\n ");
	
	printf("\nEnter the Character to be printed:\n");
	scanf("%c",&input);
	
	if((file_desc = open(file_path,O_RDWR)) < 0){
		perror("\nFile Failed to open\n");
	}
	printf("\nFile: %s was succuessfully opened\n ",file_path);
	
	printf("\n========Testing Requirement Number 5=================\n");
	printf("\nPerforming read operation on %s\n",file_path);
 	if((read(file_desc,&read_buff,sizeof(read_buff)))<0){
		perror("Failed to read");	
	}
	
	printf("\n========Testing Requirement Number 3=================\n");
	 if(ioctl(file_desc,IOC_WR,&input)){
		perror("Failed to use IOCTL");
	}
	
	printf("\n========Testing Requirement Number 4=================\n");
	printf("\nLength of the read buffer is %d\n",BUFFSIZE);
	

	if((read(file_desc,&read_buff,sizeof(read_buff))) <0){
		perror("Failed to read");
	}
	printf("%s\n",read_buff);
	
	
	close(file_desc);
	printf("\nFile: %s was succuessfully closed\n ",file_path);	

	return 0;
}
