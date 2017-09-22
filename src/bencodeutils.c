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
char get_next_byte();
void set_buff(char*);




struct Element* decode(){
    char c=get_next_byte();
    struct Element* e;
    switch(c){
        case 'd':

            break;
        case 'i':
            e=decode_number();
            break;

        case 'l':

            break;

        default:
            pos--;
            e=decode_string();
            break;
    }
    return e;


}

Element* decode_string(){
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
    printf("Inside decode_number\n");    
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
