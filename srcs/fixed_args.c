#include <stdio.h>
#include <stdlib.h>

#include "pargse.h"

static int	add_fixed_arg(pargse* pargse, const char* name, void* data, pargse_parse_arg_method method)
{
    pargse->fixed_args_number++;
    pargse->fixed_args = realloc(pargse->fixed_args, pargse->fixed_args_number * sizeof(pargse_fixed_arg));
    if (pargse->fixed_args == NULL)
    {
	fputs("Realloc error.\n", stderr);
	return 2;
    }

    pargse->fixed_args[pargse->fixed_args_number - 1].position = pargse->fixed_args_number;
    pargse->fixed_args[pargse->fixed_args_number - 1].name = name;
    pargse->fixed_args[pargse->fixed_args_number - 1].data = data;
    pargse->fixed_args[pargse->fixed_args_number - 1].method = method;

    return 0;
}

int	pargse_add_fixed_int_arg(pargse* pargse, const char* name, int* number)
{
    return add_fixed_arg(pargse, name, number, &pargse_parse_int);
}

int	pargse_add_fixed_str_arg(pargse* pargse, const char* name, char** str)
{
    return add_fixed_arg(pargse, name, str, &pargse_parse_str);
}


static void	missing_fixed_arg(pargse* pargse, const pargse_fixed_arg* arg)
{
    pargse_error(pargse, pargse_true, "Missing argument %s at position %d.\n", arg->name, arg->position);
}

int			pargse_parse_fixed_args(pargse* pargse)
{
    unsigned int	i;
    pargse_fixed_arg*	arg;

    for (i = 0; i < pargse->fixed_args_number; i++)
    {
	arg = &pargse->fixed_args[i];
	if (i + 1 >= pargse->argc)
	{
	    missing_fixed_arg(pargse, arg);
	    return 1;
	}

	if (arg->method(pargse, arg->name, arg->data, pargse->argv[i + 1]) != 0)
	{
	    return 1;
	}
    }

    return 0;
}
