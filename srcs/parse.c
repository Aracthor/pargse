#include <stdlib.h>

#include "pargse.h"

static void	destroy(pargse* pargse)
{
    if (pargse->fixed_args != NULL)
    {
	free(pargse->fixed_args);
    }
    if (pargse->flagged_args != NULL)
    {
	free(pargse->flagged_args);
    }
}

int	pargse_parse(pargse* pargse)
{
    if (pargse_parse_fixed_args(pargse) != 0)
    {
	destroy(pargse);
	return 1;
    }

    if (pargse_parse_flagged_args(pargse) != 0)
    {
	destroy(pargse);
	return 1;
    }

    destroy(pargse);

    return 0;
}


int		pargse_parse_char(pargse* pargse, const char* name, void* data, char* token)
{
    if (token[0] == '\0' || token[1] != '\0')
    {
	pargse_error(pargse, pargse_false,
		     "Need a single characeter as argument for %s, instead of \"%s\".\n", name, token);
	return 1;
    }
    *((char*)data) = token[0];
    return 0;
}

static void	bad_int_arg(pargse* pargse, const char* name, char *token)
{
    pargse_error(pargse, pargse_false, "Need a number as argument for %s, instead of \"%s\".\n", name, token);
}

int			pargse_parse_int(pargse* pargse, const char* name, void* data, char* token)
{
    unsigned int	i;

    for (i = 0; token[i] != '\0'; i++)
    {
	if (token[i] < '0' || token[i] > '9')
	{
	    bad_int_arg(pargse, name, token);
	    return 1;
	}
    }

    if (i == 0)
    {
	bad_int_arg(pargse, name, token);
	return 1;
    }

    *((int*)data) = atoi(token);
    return 0;
}

int		pargse_parse_str(pargse* pargse, const char* name, void* data, char* token)
{
    (void)pargse;
    (void)name;
    *((char**)data) = token;
    return 0;
}
