#include "pargse.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void	concat_fixed_arg(char* buffer, size_t* remaining, pargse_fixed_arg* arg)
{
    strncat(buffer, " ", *remaining);
    (*remaining)--;
    strncat(buffer, arg->name, *remaining);
    remaining -= strlen(arg->name);
}

static void	concat_flagged_arg(char* buffer, size_t* remaining, pargse_flagged_arg* arg)
{
    strncat(buffer, " ", *remaining);
    (*remaining)--;
    if (!arg->mandatory)
    {
	strncat(buffer, "[", *remaining);
	(*remaining)--;
    }
    strncat(buffer, "-", *remaining);
    *remaining -= 3;
    buffer[0x1000 - *remaining - 2] = arg->flag;
    buffer[0x1000 - *remaining - 1] = ' ';
    strncat(buffer, arg->name, *remaining);
    *remaining -= strlen(arg->name);
    if (!arg->mandatory)
    {
	strncat(buffer, "]", *remaining);
	*remaining -= 1;
    }
}

static void		print_program_usage(const pargse* pargse)
{
    char		buffer[0x1000 + 1];
    size_t		remaining = 0x1000;
    unsigned int	i;

    buffer[0x1000] = '\0';

    strncpy(buffer, "USAGE: ", 0x1000);
    strncat(buffer, pargse->argv[0], remaining);
    remaining -= strlen(buffer);

    for (i = 0; i < pargse->fixed_args_number; i++)
    {
	concat_fixed_arg(buffer, &remaining, &pargse->fixed_args[i]);
    }

    for (i = 0; i < pargse->flagged_args_number; i++)
    {
	concat_flagged_arg(buffer, &remaining, &pargse->flagged_args[i]);
    }

    fprintf(stderr, "%s\n", buffer);
}

void		pargse_error(const pargse* pargse, pargse_bool print_usage, const char* str, ...)
{
    va_list	list;

    (void)pargse;
    va_start(list, str);
    vfprintf(stderr, str, list);
    va_end(list);

    if (print_usage)
    {
	print_program_usage(pargse);
    }
}
