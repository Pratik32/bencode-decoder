#include<stdio.h>
#include<stdlib.h>
//#include "myheader.h"

FILE*	 file;
char	 filename[80];
long 	 filelen;

int main(){
	char * ptr=filename;
	printf("Enter the name of the file\n");
	scanf("%s",filename);
	printf("Filename is %s\n",ptr);
	file=fopen(ptr,"r");
	char* data;
	data=read(&filename);
	printf("%d\n",data);
	printf("%c\n",data[0]);
	return 0;
}













