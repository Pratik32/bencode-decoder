#include<stdio.h>
#include<stdlib.h>
//#include "myheader.h"


char* buff;
FILE* file;
long  filelen;
char* read(char* filename){
	file=fopen(filename,"r");
	fseek(file,0,SEEK_END);	
	filelen=ftell(file);
	rewind(file);
	printf("file length is:%ld\n",filelen);
	buff=(char*)malloc((filelen)*sizeof(char));
	fread(buff,filelen-1,1,file);
	buff[filelen]='\0';
	fclose(file);
	//char c=*buff;
    printf("utils.c:read() returning following buffer:\n%s\n",buff);
	return buff;
}
