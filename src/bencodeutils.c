/*
 *Decoder for bencode format.
 *
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "myheader.h"
#include "bencodeutils.h"
char*          data;
int            pos;
char           curr_byte;
extern long    filelen;

//Function declarations.

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
    long long strlen;
    int       i=0;
    char*     str;
    Element*  number;
    Element*  e;

    number=decode_number();
    strlen=number->value.num;
    str=(char*)malloc(strlen+1);
    while(i<strlen){
        curr_byte=get_next_byte();
        str[i]=curr_byte;
        i++;
    }
    str[i]='\0';
    printf("String is %s\n",str);
    e=(Element*)malloc(sizeof(Element));
    e->type=STRING;
    e->value.str=str;
    return e;
}

struct Element* decode_number(){    
    int       curr;
    long long res;
    int       prev;
    Element*  e;
    curr_byte=get_next_byte();
    curr=curr_byte-'0';
    res=curr;
    prev=0;
    while(curr>=0 && curr<=9){
        res=curr+prev*10;
        curr_byte=get_next_byte();
        curr=curr_byte-'0';
        prev=res;
    }
    printf("The number is: %lld\n",res);
    e=(Element*)malloc(sizeof(Element));
    e->type=INT;
    e->value.num=res;
    return e;
}

struct Element* decode_list(){
    List*    start;
    Element* e;
    Element* result;
    List*    prev;
    List*    curr;

    printf("Inside decode_list\n"); 
    start=(List*)malloc(sizeof(List));
    e=NULL;
    result=(Element*)malloc(sizeof(Element));
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
    prev=start;
    curr=NULL;

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
    if(pos>=filelen){
        printf("End of file\n");
        return -1;
    }
    return data[pos++];

}
void set_buff(char * buff){
    printf("Buffer set with size %d\n",strlen(buff));
    data=buff;
}


// Methods for accessing torrent meta data.



/*  Create a torrent_meta structure from given file.
 *  Currently implmenting map using struct+linkedlist
 *  Will come up with better idea about maps in C. 
 */

torrent_meta* get_torrent_meta(char* data){
    Dict*         map_root;
    torrent_meta* meta;
    char**        announce_list;
    char*         announce_url;
    Element*      tmp_ele;
    List*         list;
    char*         tmp_str;
    
    Element* root = decode(data);
    map_root = root->value.dict;
    
    announce_url = root->value.str;

    if(map_root->next == NULL){
        DEBUG("No announce list found\n");
    }
    tmp_ele = map_root->next->value;

    list = tmp_ele->value.list;
    
    /*
     * Iterate over the list and get all the announce urls.
     */
    while(list != NULL){

        tmp_str = LVALUE(list);
        printf("url is : %s \n",tmp_str);
        list=list->next;
    }
    
    
    




}
