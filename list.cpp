#include <stdio.h>

#include "list.h"

void do_list ()
{
    list_t list = {};
    list_t* ptr_list = &list;
    list_ctor ( ptr_list );

    //list_verifier ( ptr_list );

    list_dump ( ptr_list );

    list_dtor ( ptr_list );
}

int list_ctor ( list_t* ptr_list )
{
    ptr_list->free = 1;
    ptr_list->head = 1;
    ptr_list->tail = 1;

    ptr_list->array_code = ( list_elem_t* ) calloc ( LIST_CAPACITY, sizeof( list_elem_t ));
    for ( int i = 1; i < LIST_CAPACITY; i++ )
        ptr_list->array_code [ i ] = POISON_VALUE;

    ptr_list->array_next = ( list_elem_t* ) calloc ( LIST_CAPACITY, sizeof( list_elem_t ));
    for ( int i = 1; i < LIST_CAPACITY - 1; i++ )
        ptr_list->array_next [ i ] = ++i;

    ptr_list->array_next [ LIST_CAPACITY - 1 ] = 0;

    ptr_list->array_prev = ( list_elem_t* ) calloc ( LIST_CAPACITY, sizeof( list_elem_t ));



    //list_verifier ( list );
}


//TODO shit under
/*int list_verifier ( list_t list )
{
    free<0 and >LIST_CAPACITY

    head and tail ( same as free)

    validnost ukazateley

    next[i] == prev[next[i]]

}*/

int elem_include ( list_t* ptr_list, list_elem_t index, int value, int type_include )
{
    //TODO list_verifier
    switch ( type_include )
    case AFTER_ELEM:
    {
        //check if ind < 2
        list_elem_t prev_index = index - 1;
        insert_elem ( ptr_list, prev_index, value );
        break;
    }


}

int insert_elem ( list_t* ptr_list, list_elem_t prev_index, int value )
{
    ptr_list->array_code [ ptr_list->free ] = value;                                //присваивает первому свободной ячейке значение
    ptr_list->array_prev [ ptr_list->free ] = prev_index;                           //присваивает ячейке в массиве prev по адресу free индекс предыдущей ячейки ( prev index )
    ptr_list->array_next [ ptr_list->free ] = ptr_list->array_next [ prev_index ];  //присваивает ячейке в массиве next по адресу free индекс в массиве next по адресу предыдущего элемента
    ptr_list->array_next [ prev_index ] = ptr_list->array_next [ prev_index ] + 1;  //переопределяет индекс на который указывает next [ prev_index ] на индекс нового элемента + 1
    ptr_list->array_prev [ ptr_list->array_next [ prev_index ] ] = ptr_list->free;  //переопределяет индекс на который указывает prev [ next[ prev_index ] ] на индекс только что заполненной ячейки ( =free)

    ptr_list->free = ptr_list->array_next [ ptr_list->free ];       //free получает новый индекс: значение в массиве next под индексом старого free ( пустая ячейка указывают на следующую пустую ячейку)
}
