#include<stdio.h>
#include "myheader.h"
#include "bencodeutils.h"
void set_buff(char *);
void decode_number();
void decode_string();
Element* decode();
int main(){
    char*   filename="../res/2.torrent";
    char*   data=read(filename);
    char*   key;
    Element* value;
    //torrent_meta meta;
    set_buff(data);
    Element* e= decode();
    if(e==NULL){
        printf("NULL response returned from decoder\n");
    
    }
    Dict* start=e->value.dict;
    
    while(start!=NULL){
        key=start->key;
        printf("key is :%s\n",key);
        value=start->value;
        printf("value is:%lld\n",value->value.num);
        start=start->next;
    }
    return 0;
}
