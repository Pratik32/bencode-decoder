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

    while(start!=NULL){
        if(start->elements->type==STRING){
            printf("The string is: %s\n",start->elements->value.str);
        }else{
        
            printf("The number is:%lld\n",start->elements->value.num);
        }

        start=start->next;
    }
    return 0;
}

