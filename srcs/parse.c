#include "pargse.h"

int	pargse_parse(pargse* pargse)
{
    if (pargse_parse_fixed_args(pargse) != 0)
    {
	return 1;
    }

    return 0;
}
