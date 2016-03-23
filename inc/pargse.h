#ifndef PARGSE_H_
# define PARGSE_H_

# include "pargse_internal.h"

PARGSE_EXTERN_C_BEGIN

void	pargse_init(pargse* pargse);
int	pargse_add_fixed_int_arg(pargse* pargse, int* number);
int	pargse_add_fixed_str_arg(pargse* pargse, char** str);

PARGSE_EXTERN_C_END

#endif /* !PARGSE_H_ */
