#include <stdio.h>
//#include <TXLib.h>
#include <stdlib.h>

#include "list.h"
#include "grafic_printf.h"

void do_list ()
{
    FILE* ptr_output_file = fopen ( "code.dot", "w" );

    const char dot_file_name[ MAX_NAME_LEN ] = "code.dot";
    const char picture_file_name[ MAX_NAME_LEN ] = "a.png";

    list_t list = {};
    list_t* ptr_list = &list;
    list_ctor ( ptr_list );

    dumpass ( ptr_list );

    list_verifier ( ptr_list );

    dumpass ( ptr_list );

    insert_elem ( ptr_list, 0, 10 );
    dumpass ( ptr_list );

    insert_elem ( ptr_list, 1, 20 );
    dumpass ( ptr_list );

    insert_elem ( ptr_list, 2, 30 );
    dumpass ( ptr_list );

fprintf ( stderr, "\nPRINTF BEFORE DISASTER\n\n");

    elem_out ( ptr_list, 1 );
    dumpass ( ptr_list );

    //insert_elem ( ptr_list, 3, 30 );

    dumpass ( ptr_list );

    create_printf_code ( ptr_output_file, ptr_list );

    fclose ( ptr_output_file );

    do_code ( dot_file_name, picture_file_name );


    list_dtor ( ptr_list );
}

errors_t list_ctor ( list_t* ptr_list )
{
    // TODO: check ptr by assert

    ptr_list->free = 1;

    ptr_list->array_data = ( list_elem_t* ) calloc ( LIST_CAPACITY, sizeof( list_elem_t ));
    for ( int i = 1; i < LIST_CAPACITY; i++ )
        ptr_list->array_data [ i ] = POISON_VALUE;

    ptr_list->array_next = ( list_elem_t* ) calloc ( LIST_CAPACITY, sizeof( list_elem_t ));
    for ( int i = 1; i < LIST_CAPACITY - 1; i++ )
        ptr_list->array_next [ i ] = -( i + 1 );

    ptr_list->array_next [ LIST_CAPACITY - 1 ] = POISON_VALUE;

    ptr_list->array_prev = ( list_elem_t* ) calloc ( LIST_CAPACITY, sizeof( list_elem_t ));
    for ( int i = 0; i < LIST_CAPACITY; i++ )
        ptr_list->array_prev [ i ] = POISON_VALUE;

    ptr_list->array_next [ 0 ] = 0;
    ptr_list->array_prev [ 0 ] = 0;

    list_verifier ( ptr_list );

    return LIST_FUNC_DONE;
}


//TODO as marcos
errors_t list_verifier ( list_t* ptr_list )
{
    errors_t check_result = checker ( ptr_list );
    if ( check_result != 0 )
        fprintf ( stderr,"************\nERROR - %d\n************\n", check_result );

    return LIST_FUNC_DONE;
}

errors_t checker ( list_t* ptr_list )
{
    if ( ptr_list->free < 0 || ptr_list->free > LIST_CAPACITY )
        return ERROR_FREE;

    if ( ptr_list->array_next [ 0 ] < 0 || ptr_list->array_next [ 0 ] > LIST_CAPACITY )
        return ERROR_HEAD;

    if ( ptr_list->array_prev [ 0 ] < 0 || ptr_list->array_prev [ 0 ] > LIST_CAPACITY )
        return ERROR_TAIL;

    if ( !ptr_list->array_data )
        return BAD_PTR_CODE;

    if ( !ptr_list->array_next )
        return BAD_PTR_NEXT;

    if ( !ptr_list->array_prev )
        return BAD_PTR_TAIL;

    for ( int i = 0; i < LIST_CAPACITY - 1; i++ )
    {
        if ( ptr_list->array_data [ i ] != POISON_VALUE )
            if ( i != ptr_list->array_prev [ ptr_list->array_next [ i ] ] )
                return SHITTY_NEXT_PREV;
    }

    return LIST_FUNC_DONE;
}

errors_t insert_elem ( list_t* ptr_list, list_elem_t prev_index, int value )
{
    list_verifier ( ptr_list );

    int next_free_elem_index = - ( ptr_list->array_next [ ptr_list->free ] );

    ptr_list->array_data [ ptr_list->free ] = value;

    ptr_list->array_next [ ptr_list->free ] = ptr_list->array_next [ prev_index ];
    ptr_list->array_prev [ ptr_list->array_next [ prev_index ] ] = ptr_list->free;

    ptr_list->array_next [ prev_index ] = ptr_list->free;
    ptr_list->array_prev [ ptr_list->free ] = prev_index;

    ptr_list->free = next_free_elem_index;

    list_verifier ( ptr_list );

    return LIST_FUNC_DONE;
}

errors_t elem_out ( list_t* ptr_list, list_elem_t delete_index )
{
    list_verifier ( ptr_list );

    ptr_list->array_data [ delete_index ] = POISON_VALUE;

    ptr_list->array_next [ ptr_list->array_prev [ delete_index ] ] = ptr_list->array_next [ delete_index ];
    ptr_list->array_prev [ ptr_list->array_next [ delete_index ] ] = ptr_list->array_prev [ delete_index ];

    ptr_list->array_next [ delete_index ] = - ( ptr_list->free );
    ptr_list->array_prev [ delete_index ] = POISON_VALUE;

    ptr_list->free = delete_index;

    list_verifier ( ptr_list );

    return LIST_FUNC_DONE;
}

errors_t list_dtor ( list_t* ptr_list )
{
    ptr_list->free = POISON_VALUE;

    free ( ptr_list->array_data );
    free ( ptr_list->array_next );
    free ( ptr_list->array_prev );

    return LIST_FUNC_DONE;
}

/*errors_t dumpass ( list_t* ptr_list )
{
    char cmd_command [ CMD_COMMAND_LEN ] = {};
    sprintf ( cmd_command, "dot code.dot -T png -o %s", picture_file_name );
    fprintf ( stderr, "comanda = %s\n", cmd_command );
    system ( cmd_command );

    return LIST_FUNC_DONE;
}*/

errors_t dumpass ( list_t* ptr_list )
{
    fprintf ( stderr, "CODE:\n");
    fprintf ( stderr, "FREE = %d\n", ptr_list->free );
    for ( int i = 0; i < LIST_CAPACITY; i++ )
        fprintf ( stderr, "%3d  ", i );

    fprintf ( stderr, "\n|");
    for ( int i = 0; i < LIST_CAPACITY; i++ )
        fprintf ( stderr, "%3d| ", ptr_list->array_data [ i ] );

    fprintf ( stderr, "\n|");
    for ( int i = 0; i < LIST_CAPACITY; i++ )
        fprintf ( stderr, "%3d| ", ptr_list->array_next [ i ] );

    fprintf ( stderr, "\n|");
    for ( int i = 0; i < LIST_CAPACITY; i++ )
        fprintf ( stderr, "%3d| ",ptr_list->array_prev [ i ] );

    fprintf ( stderr, "\n---------------------------------------------------------\n");
    return LIST_FUNC_DONE;
}
//TODO прочитать документацию дота, и сделать переменную отвечающую за номер текущего вывода и выводить эту хуйню
