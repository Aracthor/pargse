#include <stdio.h>
#include <stdlib.h>

#include "pargse.h"

static int	add_fixed_arg(pargse* pargse, void* data, pargse_parse_fixed_arg_method method)
{
    pargse->fixed_args_number++;
    pargse->fixed_args = realloc(pargse->fixed_args, pargse->fixed_args_number * sizeof(pargse_fixed_arg));
    if (pargse->fixed_args == NULL)
    {
	fputs("Realloc error.\n", stderr);
	return 1;
    }

    pargse->fixed_args[pargse->fixed_args_number - 1].position = pargse->fixed_args_number;
    pargse->fixed_args[pargse->fixed_args_number - 1].data = data;
    pargse->fixed_args[pargse->fixed_args_number - 1].method = method;

    return 0;
}

int	pargse_add_fixed_int_arg(pargse* pargse, int* number)
{
    return add_fixed_arg(pargse, number, &pargse_parse_fixed_int);
}

int	pargse_add_fixed_str_arg(pargse* pargse, char** str)
{
    return add_fixed_arg(pargse, str, &pargse_parse_fixed_str);
}
