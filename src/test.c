#include<stdio.h>
#include "myheader.h"
void set_buff(char *);
void decode_number();
void decode_string();
Element* decode();
int main(){
    char * filename="demo.txt";
    char * data=read(filename);
    set_buff(data);
    struct  Element* e= decode();
    printf("The number is %d\n",e->value.num);
    return 0;
}

