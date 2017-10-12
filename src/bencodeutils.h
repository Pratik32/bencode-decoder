
//Represent a torrent file.
typedef struct torrent_meta{

    char*  filename;
    long   tsize;
    char*  pieces;
    char*  info_hash;
    char*  folder;
    char** piece_hash;
    int    tpieces;
    char** annouce_list;
}torrent_meta;

//torrent_meta* get_torrent_meta(char*);

char* get_announce_list();
char* get_info_hash();
char* get_filename();
