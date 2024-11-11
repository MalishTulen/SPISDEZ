#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "grafic_printf.h"

errors_t create_printf_code ( FILE* ptr_output_file, list_t* ptr_list )
{
    fprintf ( ptr_output_file, "digraph data{\n" );
    fprintf ( ptr_output_file, "rankdir = LR;\n" );
    for ( int i = 0; i < LIST_CAPACITY; i++ )
    {
        fprintf ( ptr_output_file, "node%d [ shape = record, label = \" <f0> %d | <f1> %d | <f2> %d | <f3> %d \"] ;\n", i, i, ptr_list->array_data [ i ], ptr_list->array_next [ i ], ptr_list->array_prev [ i ]);
    }

    fprintf ( ptr_output_file, "free [ shape = circle, style = bold, label = \" free \" ];\n" );

    /*fprintf ( ptr_output_file, "{ rank = same; ");

    for ( int i = 0; i < LIST_CAPACITY; i++ )
        fprintf ( ptr_output_file, "\"node%d\"; ", i );

    fprintf ( ptr_output_file, "}\n");*/


    fprintf ( ptr_output_file, "{\nedge[color = white, weight = 1000 ];\nnode0" );

    for ( int i = 1; i < LIST_CAPACITY; i++ )
        fprintf ( ptr_output_file, "->node%d", i );

    fprintf ( ptr_output_file, ";\n}\n" );



    fprintf ( ptr_output_file, "{\nedge[color = red, arrowhead = vee]\n" );
    for ( int i = 0; i < LIST_CAPACITY; i++ )
    {
        if ( ptr_list->array_next [ i ] >= 0 )
            //if ( ptr_list->array_next [ ptr_list->array_prev [ i ] ] >= 0 )
                fprintf ( ptr_output_file, "node%d:<f1>->node%d:<f0>\n", i, ptr_list->array_next [ i ]);
    }

    for ( int i = 0; i < LIST_CAPACITY; i++ )
    {
        if ( ptr_list->array_next [ i ] < 0 && ptr_list->array_next [ i ] != POISON_VALUE )
            fprintf ( ptr_output_file, "node%d:<f1>->node%d:<f0>\n", i, - ( ptr_list->array_next [ i ] ) );
    }
    fprintf ( ptr_output_file, "}\n");

    fprintf ( ptr_output_file, "{\nedge[color = blue, arrowhead = vee]\n" );
    for ( int i = 0; i < LIST_CAPACITY; i++ )
    {
        if ( ptr_list->array_prev [ i ] >= 0 )
            fprintf ( ptr_output_file, "node%d:<f2>->node%d:<f3>\n", i, ptr_list->array_prev [ i ]);
    }

    fprintf ( ptr_output_file, "}\n");

    fprintf ( ptr_output_file, "free->node%d:<f0>;", ptr_list->free );

    fprintf ( ptr_output_file, "}\n");

    return LIST_FUNC_DONE;
}

errors_t do_code ( const char* ptr_otput_file, const char* ptr_picture_file )
{
    char cmd_command [ CMD_COMMAND_LEN ] = {};
    sprintf ( cmd_command, "dot %s -T png -o %s", ptr_otput_file, ptr_picture_file );
    fprintf ( stderr, "command = '%s'\n", cmd_command );
    system ( cmd_command );

    return LIST_FUNC_DONE;
}
