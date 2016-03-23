#include <stddef.h>

#include "pargse.h"

void	pargse_init(pargse* pargse)
{
    pargse->fixed_args = NULL;
    pargse->fixed_args_number = 0;
}
