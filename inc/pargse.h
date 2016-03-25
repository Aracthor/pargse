#ifndef PARGSE_H_
# define PARGSE_H_

# include "pargse_internal.h"

PARGSE_EXTERN_C_BEGIN

void	pargse_init(pargse* pargse, int argc, char** argv);

int	pargse_add_fixed_char_arg(pargse* pargse, const char* name, char* c);
int	pargse_add_fixed_int_arg(pargse* pargse, const char* name, int* number);
int	pargse_add_fixed_str_arg(pargse* pargse, const char* name, char** str);

int	pargse_add_flagged_char_arg(pargse* pargse, char flag, const char* name, pargse_bool mandatory, char* c);
int	pargse_add_flagged_int_arg(pargse* pargse, char flag, const char* name, pargse_bool mandatory, int* number);
int	pargse_add_flagged_str_arg(pargse* pargse, char flag, const char* name, pargse_bool mandatory, char** str);
int	pargse_add_flagged_bool_arg(pargse* pargse, char flag, const char* name, pargse_bool* boolean);

int	pargse_parse(pargse* pargse);

PARGSE_EXTERN_C_END

#endif /* !PARGSE_H_ */
