#ifndef LIST_HEADER
#define LIST_HEADER

typedef int list_elem_t;
const int LIST_CAPACITY = 10;
const int POISON_VALUE = -69;

enum include_type
{
    BEFORE_ELEM         =   0,
    AFTER_ELEM          =   1,
    IN_THE_BEGINNING    =   2,
    AT_THE_END          =   3,
};
struct list_t
{
    list_elem_t*   array_code;
    list_elem_t*   array_next;
    list_elem_t*   array_prev;
    list_elem_t    free;
    list_elem_t    head;
    list_elem_t    tail;
};

#endif
