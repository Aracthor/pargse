#include <stdio.h>

#include "pargse.h"

/**
 * Simple network client needing two arguments: host (string) and port (integer).
 */
int		main(int argc, char** argv)
{
    pargse	pargse;
    char*	host;
    int		port;

    pargse_init(&pargse, argc, argv);
    if (pargse_add_fixed_str_arg(&pargse, "host", &host) ||
	pargse_add_fixed_int_arg(&pargse, "port", &port))
    {
	return 2;
    }

    if (pargse_parse(&pargse))
    {
	return 1;
    }

    printf("Host: %s:%d\n", host, port);

    return 0;
}
