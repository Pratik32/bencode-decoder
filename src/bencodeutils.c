/*
 *
 *Decoder for bencode format.
 *
 *
 */


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
Element* decode_number();
Element* decode_list();
Element* decode_dictionary();
char get_next_byte();
void set_buff(char*);




struct Element* decode(){
    char c=get_next_byte();
    struct Element* e;
    switch(c){
        case 'd':
            printf("Dictionary\n");
            e=decode_dictionary();
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

Element* decode_dictionary(){
    printf("Inside decode_dictionary()\n");
    Element* result=(Element*)malloc(sizeof(Element));
    Dict* start =(Dict*)malloc(sizeof(Dict));
    Element* e;
    Element* str_e;
    Element* value;
    char*    key;
    Dict*    prev;
    Dict*    curr;

    curr_byte=get_next_byte();
    if(curr_byte!='e'){
        pos--;
        str_e=decode();
        key=str_e->value.str;
        printf("key is %s %c\n",key,curr_byte);
        value=decode();
        start->key=key;
        start->value=value;
        result->type=DICT; 
    }else{
        result->type=DICT;
        return result;

    }
    prev=start;
    while((curr_byte=get_next_byte())!='e'){
        pos--;
        str_e=decode();
        key=str_e->value.str;
        value=decode();
        curr=(Dict*)malloc(sizeof(Dict));
        curr->key=key;
        curr->value=value;
        prev->next=curr;
        prev=prev->next;
    }
    result->value.dict=start;
    return result;
    
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
    printf("String is %s\n",str);
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
    printf("The number is: %lld\n",res);
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
        prev=prev->next;
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
    printf("Buffer set with size %d\n",strlen(buff));
    data=buff;
}
