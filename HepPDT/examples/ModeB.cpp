
#if defined(NT_MSVCPP)
#pragma warning (disable: 4786)
#endif

#include <vector>
#include <iostream>

#include "ModeB.hh"

using namespace std;

ModeB &  ModeB::operator = ( const ModeB & rhs )
{
    ModeB temp( rhs );
    temp.swap(*this);
    return *this;
}

void ModeB::decay( const std::vector< PD > & products,
                      const PT                & parent,
                      std::vector<PT>         & daughters )
{
	std::cout << "ModeB decay " << std::endl;
}

/*
** Local Variables: --
** mode: c++ --
** c-file-style: "gnu" --
** tab-width: 2 --
** End: --
*/
