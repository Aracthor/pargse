#include <iostream>

#include "Pargse.hpp"

//
// Simple C++ network client needing two arguments: host (string) and port (integer).
//
int		main(int argc, char** argv)
{
    char*	host;
    int		port;
    Pargse	pargse(argc, argv);

    if (pargse.addFixedStrArg("host", &host) ||
	pargse.addFixedIntArg("port", &port))
    {
	return 2;
    }

    if (pargse.parse())
    {
	return 1;
    }

    std::cout << "Host: " << host << ':' << port << std::endl;

    return 0;
}
