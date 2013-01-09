#ifndef _FUZZY_PAIRDESCRIPTOR_H_
#define _FUZZY_PAIRDESCRIPTOR_H_

#include <string>

namespace Fuzzy
{
	struct PairDescriptor
	{
		PairDescriptor(std::string var, std::string val)
		{
			variable = var;
			value = val;
		}
		std::string variable;
		std::string value;
	};
}

#endif