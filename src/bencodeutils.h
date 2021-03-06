struct file;
typedef struct file{
    char* name;
    long  len;
}file;

//Represent a torrent file.
typedef struct torrent_meta{

    file** file;
    long   tsize;
    long   tpieces;
    char*  info_hash;
    char*  folder;
    char** piece_hash;
    char** announce_list;
    char*  date;
    long   piece_len;
}torrent_meta;

//torrent_meta* get_torrent_meta(char*);

char* get_announce_list();
char* get_info_hash();
char* get_filename();
torrent_meta* get_torrent_meta(char*);
