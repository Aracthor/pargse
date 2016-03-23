#ifndef PARGSE_INTERNAL_H_
# define PARGSE_INTERNAL_H_

# ifdef __cplusplus
#  define PARGSE_EXTERN_C_BEGIN  extern "C" {
#  define PARGSE_EXTERN_C_END    }
# else
#  define PARGSE_EXTERN_C_BEGIN
#  define PARGSE_EXTERN_C_END
# endif

PARGSE_EXTERN_C_BEGIN

typedef struct pargse_fixed_arg_s	pargse_fixed_arg;


typedef int	(*pargse_parse_fixed_arg_method)(pargse_fixed_arg* arg, char* token);


typedef struct				pargse_fixed_arg_s
{

    unsigned int			position;
    void*				data;
    pargse_parse_fixed_arg_method	method;
}					pargse_fixed_arg;

typedef struct
{
    pargse_fixed_arg*	fixed_args;
    unsigned int	fixed_args_number;
}			pargse;

int	pargse_parse_fixed_int(pargse_fixed_arg* arg, char* token);
int	pargse_parse_fixed_str(pargse_fixed_arg* arg, char* token);

PARGSE_EXTERN_C_END

#endif /* !PARGSE_INTERNAL_H_ */
