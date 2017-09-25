#include<stdio.h>
#include "myheader.h"
void set_buff(char *);
void decode_number();
void decode_string();
Element* decode();
int main(){
    char * filename="../res/demo.txt";
    char * data=read(filename);
    set_buff(data);
    struct  Element* e= decode();
    List* start=e->value.list;
    Element* number=start->elements;
    printf("Number is %d\n",number->value.num);
    List* end=start->next;
    Element* string=end->elements;
    printf("String is %s\n",string->value.str);
    return 0;
}

