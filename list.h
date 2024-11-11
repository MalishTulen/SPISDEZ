#ifndef LIST_HEADER
#define LIST_HEADER

typedef int list_elem_t;
const int LIST_CAPACITY = 10;
const int POISON_VALUE = -334;
const int CMD_COMMAND_LEN = 50;
const int MAX_NAME_LEN = 20;

enum include_types_t
{
    BEFORE_ELEM         =   0,
    AFTER_ELEM          =   1,
    IN_THE_BEGINNING    =   2,
    AT_THE_END          =   3,
};

enum errors_t
{
    LIST_FUNC_DONE   = 0,
    ERROR_FREE       = 1,
    ERROR_HEAD       = 2,
    ERROR_TAIL       = 3,
    BAD_PTR_CODE     = 4,
    BAD_PTR_NEXT     = 5,
    BAD_PTR_TAIL     = 6,
    SHITTY_NEXT_PREV = 7,
};

struct list_t
{
    list_elem_t*   array_data;
    list_elem_t*   array_next;
    list_elem_t*   array_prev;
    list_elem_t    free;
};

void     do_list        ();
errors_t list_ctor      ( list_t* ptr_list );
errors_t list_verifier  ( list_t* ptr_list );
errors_t checker        ( list_t* list );
//errors_t elem_include   ( list_t* ptr_list, list_elem_t index, int value, int type_include );
errors_t insert_elem    ( list_t* ptr_list, list_elem_t prev_index, int value );
errors_t elem_out       ( list_t* ptr_list, list_elem_t prev_index );
errors_t dumpass        ( list_t* ptr_list );
errors_t list_dtor      ( list_t* ptr_list );

//chin chan chon chi sdelal za dva miska risa

#endif
