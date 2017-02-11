#ifndef PARGSE_HPP_
# define PARGSE_HPP_

# include <string>

# include "pargse.h"

class	Pargse
{
public:
    Pargse(int argc, char** argv);
    ~Pargse();

    int	addFixedCharArg(const char* name, char* c);
    int	addFixedCharArg(const std::string& name, char* c);
    int	addFixedIntArg(const char* name, int* c);
    int	addFixedIntArg(const std::string& name, int* c);
    int	addFixedStrArg(const char* name, char** str);
    int	addFixedStrArg(const std::string& name, char** str);

    int	addFlaggedCharArg(char flag, const char* name, bool mandatory, char* c);
    int	addFlaggedCharArg(char flag, const std::string& name, bool mandatory, char* c);
    int	addFlaggedIntArg(char flag, const char* name, bool mandatory, int* number);
    int	addFlaggedIntArg(char flag, const std::string& name, bool mandatory, int* number);
    int	addFlaggedStrArg(char flag, const char* name, bool mandatory, char** str);
    int	addFlaggedStrArg(char flag, const std::string& name, bool mandatory, char** str);
    int	addFlaggedBoolArg(char flag, const char* name, bool* boolean);
    int	addFlaggedBoolArg(char flag, const std::string& name, bool* boolean);

    int	parse();

private:
    pargse	m_pargse;
};

#endif // !PARGSE_HPP_
