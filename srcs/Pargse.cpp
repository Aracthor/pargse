#include "Pargse.hpp"

Pargse::Pargse(int argc, char** argv)
{
    pargse_init(&m_pargse, argc, argv);
}

Pargse::~Pargse()
{
}


int
Pargse::addFixedCharArg(const char* name, char* c)
{
    return pargse_add_fixed_char_arg(&m_pargse, name, c);
}

int
Pargse::addFixedCharArg(const std::string& name, char* c)
{
    return pargse_add_fixed_char_arg(&m_pargse, name.c_str(), c);
}

int
Pargse::addFixedIntArg(const char* name, int* number)
{
    return pargse_add_fixed_int_arg(&m_pargse, name, number);
}

int
Pargse::addFixedIntArg(const std::string& name, int* number)
{
    return pargse_add_fixed_int_arg(&m_pargse, name.c_str(), number);
}

int
Pargse::addFixedStrArg(const char* name, char** str)
{
    return pargse_add_fixed_str_arg(&m_pargse, name, str);
}

int
Pargse::addFixedStrArg(const std::string& name, char** str)
{
    return pargse_add_fixed_str_arg(&m_pargse, name.c_str(), str);
}


int
Pargse::addFlaggedCharArg(char flag, const char* name, bool mandatory, char* c)
{
    return pargse_add_flagged_char_arg(&m_pargse, flag, name, static_cast<pargse_bool>(mandatory), c);
}

int
Pargse::addFlaggedCharArg(char flag, const std::string& name, bool mandatory, char* c)
{
    return pargse_add_flagged_char_arg(&m_pargse, flag, name.c_str(), static_cast<pargse_bool>(mandatory), c);
}

int
Pargse::addFlaggedIntArg(char flag, const char* name, bool mandatory, int* number)
{
    return pargse_add_flagged_int_arg(&m_pargse, flag, name, static_cast<pargse_bool>(mandatory), number);
}

int
Pargse::addFlaggedIntArg(char flag, const std::string& name, bool mandatory, int* number)
{
    return pargse_add_flagged_int_arg(&m_pargse, flag, name.c_str(), static_cast<pargse_bool>(mandatory), number);
}

int
Pargse::addFlaggedStrArg(char flag, const char* name, bool mandatory, char** str)
{
    return pargse_add_flagged_str_arg(&m_pargse, flag, name, static_cast<pargse_bool>(mandatory), str);
}

int
Pargse::addFlaggedStrArg(char flag, const std::string& name, bool mandatory, char** str)
{
    return pargse_add_flagged_str_arg(&m_pargse, flag, name.c_str(), static_cast<pargse_bool>(mandatory), str);
}

int
Pargse::addFlaggedBoolArg(char flag, const char* name, bool* boolean)
{
    return pargse_add_flagged_arg(&m_pargse, flag, name, pargse_false, &boolean, NULL);
}

int
Pargse::addFlaggedBoolArg(char flag, const std::string& name, bool* boolean)
{
    return pargse_add_flagged_arg(&m_pargse, flag, name.c_str(), pargse_false, &boolean, NULL);
}


int
Pargse::parse()
{
    return pargse_parse(&m_pargse);
}
