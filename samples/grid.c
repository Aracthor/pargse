#include <stdio.h>

#include "pargse.h"

int		main(int argc, char** argv)
{
    pargse	pargse;
    int		width;
    int		height;
    char*	name = NULL;
    int		x, y;

    pargse_init(&pargse, argc, argv);
    if (pargse_add_flagged_int_arg(&pargse, 'x', "width", pargse_true, &width) ||
	pargse_add_flagged_int_arg(&pargse, 'y', "height", pargse_true, &height) ||
	pargse_add_flagged_str_arg(&pargse, 'n', "name", pargse_false, &name))
    {
	return 2;
    }

    if (pargse_parse(&pargse))
    {
	return 1;
    }

    if (name != NULL)
    {
	printf("Name of the grid: %s\n", name);
    }
    for (y = 0; y < height; y++)
    {
	for (x = 0; x < width; x++)
	{
	    printf("#");
	}
	printf("\n");
    }

    return 0;
}
