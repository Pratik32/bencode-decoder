#include<stdio.h>
#include "myheader.h"
#include "bencodeutils.h"
void set_buff(char *);
void decode_number();
void decode_string();
Element* decode();
int main(){
    char*   filename="../res/stub.torrent";
    char*   data=read(filename);
    char*   key;
    Element* value;
    torrent_meta* meta;
    set_buff(data);
    meta = get_torrent_meta(data);

}
