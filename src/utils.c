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
	printf("file length is:%d\n",filelen);
	buff=(char*)malloc((filelen+1)*sizeof(char));
	fread(buff,filelen+1,1,file);
	buff[filelen+1]='\0';
	fclose(file);
	//char c=*buff;
	printf("%d\n",buff);
	return buff;
}
