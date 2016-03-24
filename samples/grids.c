#include <stdio.h>

#include "pargse.h"

int		main(int argc, char** argv)
{
    pargse	pargse;
    int		width;
    int		height;
    char*	name = NULL;
    int		x, y;
    int		repeat;

    pargse_init(&pargse, argc, argv);
    if (pargse_add_fixed_int_arg(&pargse, "width", &width) ||
	pargse_add_fixed_int_arg(&pargse, "height", &height) ||
	pargse_add_flagged_int_arg(&pargse, 'r', "repeat", pargse_true, &repeat) ||
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


    while (repeat > 0)
    {
	printf("\n");
	for (y = 0; y < height; y++)
	{
	    for (x = 0; x < width; x++)
	    {
		printf("#");
	    }
	    printf("\n");
	}
	repeat--;
    }

    return 0;
}
