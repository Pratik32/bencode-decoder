#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "myheader.h"
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

char* epoch_to_string(long epoch){
    time_t    t;
    struct tm ts;
    char     str[100];
    char*    buff;
    t = (time_t)epoch;
    ts = *localtime(&t);
    strftime(str, sizeof(str), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    buff = (char*)malloc(sizeof(str));
    strcpy(buff,str);
    return buff;

}
