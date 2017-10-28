
/* Defines the type of bencode object.
 * A bencode code object can be:Int/String/List/Dictionary.
 */
typedef enum BType{
    STRING,
    LIST,
    DICT,
    INT
}BType;

// A generic bencode type.
struct Element;

/* Defines a node in list of bencode elements.
 * 'next' gives the location of next element in the list.
 */
typedef struct List{
    struct Element* elements;
    struct List* next;
}List;

/* Represents an entry in dictionary of str(key):Element(value).
 * 'next' represents next entry in dictionary. 
 */
typedef struct Dict{
    char*  key;
    struct Element* value;
    struct Dict* next;
}Dict;


/* Defination of Element.
 * depending on the Btype, memory for one of the members of union will be
 * allocated.That's C's way of abstraction.
 */
typedef struct Element{
    BType type;

    union{
        long long num;
        List*     list;
        char*     str;
        Dict*     dict;
    }value;

}Element;

char* read(char*);

#define DEBUG(file,fmt,args...)    printf("DEBUG: %s:%d:%s(): " fmt,file,__LINE__,__func__,##args)

#define LVALUE(list)  list->elements->value.str  
#define NEXT_LIST(e)  e->elements->value.list                  

#define EXTEND_SIZE(ptr,size)  (char**)realloc(ptr,sizeof(char*)*size);
