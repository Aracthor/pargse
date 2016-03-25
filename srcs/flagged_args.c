#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pargse.h"

static int	add_flagged_arg(pargse* pargse, char flag, const char* name, pargse_bool mandatory, void* data,
				pargse_parse_arg_method method)
{
    pargse->flagged_args_number++;
    pargse->flagged_args = realloc(pargse->flagged_args, pargse->flagged_args_number * sizeof(pargse_flagged_arg));
    if (pargse->flagged_args == NULL)
    {
	fputs("Realloc error.\n", stderr);
	return 2;
    }

    pargse->flagged_args[pargse->flagged_args_number - 1].flag = flag;
    pargse->flagged_args[pargse->flagged_args_number - 1].name = name;
    pargse->flagged_args[pargse->flagged_args_number - 1].mandatory = mandatory;
    pargse->flagged_args[pargse->flagged_args_number - 1].data = data;
    pargse->flagged_args[pargse->flagged_args_number - 1].method = method;

    return 0;
}


int	pargse_add_flagged_char_arg(pargse* pargse, char flag, const char* name, pargse_bool mandatory, char* c)
{
    return add_flagged_arg(pargse, flag, name, mandatory, c, &pargse_parse_char);
}

int	pargse_add_flagged_int_arg(pargse* pargse, char flag, const char* name, pargse_bool mandatory, int* number)
{
    return add_flagged_arg(pargse, flag, name, mandatory, number, &pargse_parse_int);
}

int	pargse_add_flagged_str_arg(pargse* pargse, char flag, const char* name, pargse_bool mandatory, char** str)
{
    return add_flagged_arg(pargse, flag, name, mandatory, str, &pargse_parse_str);
}

int	pargse_add_flagged_bool_arg(pargse* pargse, char flag, const char* name, pargse_bool* boolean)
{
    return add_flagged_arg(pargse, flag, name, pargse_false, boolean, NULL);
}

static void	unexpected_token(pargse* pargse, const char* token)
{
    pargse_error(pargse, pargse_true, "Unexpected token \"%s\".\n", token);
}

static unsigned int	find_complete_name(pargse* pargse, const char* token)
{
    unsigned int	index;

    index = 0;
    while (index < pargse->flagged_args_number && strcmp(&token[2], pargse->flagged_args[index].name) != 0)
    {
	index++;
    }

    if (index == pargse->flagged_args_number)
    {
	pargse_error(pargse, pargse_true, "Unknown parameter \"%s\".\n", &token[2]);
    }

    return index;
}

static unsigned int	find_flag(pargse* pargse, char flag)
{
    unsigned int	index;

    index = 0;
    while (index < pargse->flagged_args_number && flag != pargse->flagged_args[index].flag)
    {
	index++;
    }

    if (index == pargse->flagged_args_number)
    {
	pargse_error(pargse, pargse_true, "Unknown flag '%c'.\n", flag);
    }

    return index;
}

static pargse_flagged_arg*	find_arg(pargse* pargse, pargse_bool* found, const char* token)
{
    unsigned int		index;

    if (token[0] != '-')
    {
	unexpected_token(pargse, token);
	return NULL;
    }

    if (token[1] == '-')
    {
	index = find_complete_name(pargse, token);
    }
    else if (token[2] != '\0')
    {
	unexpected_token(pargse, token);
	return NULL;
    }
    else
    {
	index = find_flag(pargse, token[1]);
    }

    if (index >= pargse->flagged_args_number)
    {
	return NULL;
    }
    if (found[index])
    {
	pargse_error(pargse, pargse_false, "Duplicate argument %s.\n", pargse->flagged_args[index].name);
	return NULL;
    }
    found[index] = pargse_true;

    return &pargse->flagged_args[index];
}

static int	read_token(pargse* pargse, pargse_bool* found, pargse_flagged_arg** current_arg, char* token)
{
    if (*current_arg == NULL)
    {
	*current_arg = find_arg(pargse, found, token);
	if (*current_arg == NULL)
	{
	    return 1;
	}
	if ((*current_arg)->method == NULL)
	{
	    *current_arg = NULL;
	}
    }
    else
    {
	if ((*current_arg)->method(pargse, (*current_arg)->name, (*current_arg)->data, token) != 0)
	{
	    return 1;
	}
	*current_arg = NULL;
    }

    return 0;
}

static void		set_booleans_args(pargse* pargse, pargse_bool* found)
{
    unsigned int	i;

    for (i = 0; i < pargse->flagged_args_number; i++)
    {
	if (pargse->flagged_args[i].method == NULL)
	{
	    *((pargse_bool*)pargse->flagged_args[i].data) = found[i];
	}
    }
}

static int		check_mandatories(pargse* pargse, pargse_bool* found)
{
    int			error = 0;
    unsigned int	i;

    for (i = 0; error == 0 && i < pargse->flagged_args_number; i++)
    {
	if (pargse->flagged_args[i].mandatory && !found[i])
	{
	    pargse_error(pargse, pargse_true, "Missing mandatory argument %s.\n", pargse->flagged_args[i].name);
	    error = 1;
	}
    }

    return error;
}

int			pargse_parse_flagged_args(pargse* pargse)
{
    unsigned int	index;
    pargse_bool*	found;
    pargse_flagged_arg*	current_arg;
    int			error = 0;

    if (pargse->flagged_args_number > 0)
    {
	found = malloc(pargse->flagged_args_number * sizeof(pargse_bool));
	if (found == NULL)
	{
	    fputs("Malloc error.\n", stderr);
	    return 2;
	}
	memset(found, 0, pargse->flagged_args_number * sizeof(pargse_bool));
	current_arg = NULL;

	index = pargse->fixed_args_number + 1;

	error = 0;
	for (index = pargse->fixed_args_number + 1; index < pargse->argc && error == 0; index++)
	{
	    if (read_token(pargse, found, &current_arg, pargse->argv[index]) != 0)
	    {
		free(found);
		return 1;
	    }
	}

	if (current_arg != NULL)
	{
	    pargse_error(pargse, pargse_true, "Missing data after token \"%s\".\n", pargse->argv[pargse->argc - 1]);
	    free(found);
	    return 1;
	}

	set_booleans_args(pargse, found);
	error = check_mandatories(pargse, found);

	free(found);
    }


    return error;
}
