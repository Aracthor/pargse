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
typedef struct pargse_flagged_arg_s	pargse_flagged_arg;
typedef struct pargse_s			pargse;


typedef int	(*pargse_parse_arg_method)(pargse* pargse, const char* name, void* data, char* token);


typedef enum	pargse_bool_e
{
    pargse_false = 0,
    pargse_true = 1
}		pargse_bool;


typedef struct			pargse_fixed_arg_s
{
    unsigned int		position;
    const char*			name;
    void*			data;
    pargse_parse_arg_method	method;
}				pargse_fixed_arg;

typedef struct			pargse_flagged_arg_s
{
    char			flag;
    const char*			name;
    void*			data;
    pargse_bool			mandatory;
    pargse_parse_arg_method	method;
}				pargse_flagged_arg;

typedef struct		pargse_s
{
    unsigned int	argc;
    char**		argv;
    pargse_fixed_arg*	fixed_args;
    unsigned int	fixed_args_number;
    pargse_flagged_arg*	flagged_args;
    unsigned int	flagged_args_number;
}			pargse;

int	pargse_parse_char(pargse* pargse, const char* name, void* data, char* token);
int	pargse_parse_int(pargse* pargse, const char* name, void* data, char* token);
int	pargse_parse_str(pargse* pargse, const char* name, void* data, char* token);
int	pargse_parse_fixed_args(pargse* pargse);
int	pargse_parse_flagged_args(pargse* pargse);

void	pargse_error(const pargse* pargse, pargse_bool print_usage, const char* str, ...);

PARGSE_EXTERN_C_END

#endif /* !PARGSE_INTERNAL_H_ */
