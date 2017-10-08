#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* buff;
FILE* file;
long  filelen;
char* read(char* filename){
	int count=0;
    file=fopen(filename,"r");
	fseek(file,0L,SEEK_END);	
	filelen=ftell(file);
	rewind(file);
	printf("file length is:%ld\n",filelen);
	buff=(char*)malloc((filelen)*sizeof(char));
    if(buff==NULL){
        printf("malloc failed to allocate memory");
    }
	count=fread(buff,sizeof(char),filelen,file);
    printf("Number of chars read %d\n",count);
    printf("%ld",filelen);
	fclose(file);
    printf("utils.c:read() returning following buffer:\n%s\n",buff);
	return buff;
}
