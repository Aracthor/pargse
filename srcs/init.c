#include <stddef.h>

#include "pargse.h"

void	pargse_init(pargse* pargse, int argc, char** argv)
{
    pargse->argc = argc;
    pargse->argv = argv;
    pargse->fixed_args = NULL;
    pargse->fixed_args_number = 0;
    pargse->flagged_args = NULL;
    pargse->flagged_args_number = 0;
}
