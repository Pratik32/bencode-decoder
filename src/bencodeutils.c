#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "myheader.h"
char*   data;
int     pos;
char    curr_byte;

//Represents the first value of the entire dictionary.

//  Function declarations.

Element* decode_string();
struct Element* decode_number();
struct Element* decode_list();
char get_next_byte();
void set_buff(char*);




struct Element* decode(){
    char c=get_next_byte();
    struct Element* e;
    switch(c){
        case 'd':

            break;
        case 'i':
            printf("Number \n");
            e=decode_number();
            break;

        case 'l':
            printf("List \n");
            e=decode_list();
            break;

        default:
            printf("String \n");
            pos--;
            e=decode_string();
            break;
    }
    return e;


}

Element* decode_string(){
    printf("Inside decode_string\n");
    Element* number =decode_number();
    long long strlen=number->value.num;
    int i=0;
    char * str=(char*)malloc(strlen+1);
    while(i<strlen){
        curr_byte=get_next_byte();
        str[i]=curr_byte;
        i++;
    }
    str[i]='\0';
    printf("String is %s \n",str);
    Element* e=(Element*)malloc(sizeof(Element));
    e->type=STRING;
    e->value.str=str;
    return e;
}

struct Element* decode_number(){    
    curr_byte=get_next_byte();
    int curr=curr_byte-'0';
    long long res=curr;
    int prev=0;

    while(curr>=0 && curr<=9){
        res=curr+prev*10;
        curr_byte=get_next_byte();
        curr=curr_byte-'0';
        prev=res;
    }
    printf("The number is: %d\n",res);
    struct Element* e=(Element*)malloc(sizeof(Element));
    e->type=INT;
    e->value.num=res;
    return e;

}

struct Element* decode_list(){
    printf("Inside decode_list\n"); 
    List* start=(List*)malloc(sizeof(List));
    Element* e=NULL;
    Element* result=(Element*)malloc(sizeof(Element));
    curr_byte=get_next_byte();
    if(curr_byte!='e'){
        pos--;
        e=decode();
        start->elements=e;
        start->next=NULL;
    }else{
        result->type=LIST;
        result->value.list=NULL;
        return result;
    }
    List* prev=start;
    List* curr=NULL;

    while((curr_byte=get_next_byte())!='e'){
        pos--;
        e=decode();
        curr=(List*)malloc(sizeof(List));
        curr->elements=e;
        curr->next=NULL;
        prev->next=curr;
        prev=curr;
    }

    result->type=LIST;
    result->value.list=start;
    return result;

}
char get_next_byte(){
    if(pos>=strlen(data)){
        printf("End of file\n");
        return -1;
    }
    return data[pos++];

}
void set_buff(char * buff){
    printf("Inside set_buff\n");
    data=buff;

}
