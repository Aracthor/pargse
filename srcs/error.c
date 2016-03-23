#include "pargse.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

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
	strncat(buffer, " ", remaining);
	remaining -= 1;
	strncat(buffer, pargse->fixed_args[i].name, remaining);
	remaining -= strlen(pargse->fixed_args[i].name);
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
