#ifndef _FUZZY_RULEDESCRIPTOR_H_
#define _FUZZY_RULEDESCRIPTOR_H_

#include "pairDescriptor.h"
#include <string>
#include <list>

namespace Fuzzy
{
	struct RuleDescriptor
	{
		void AddInPair(std::string var, std::string val)
		{
			input.push_back(new PairDescriptor(var, val));
		}
		void AddOutPair(std::string var, std::string val)
		{
			output.push_back(new PairDescriptor(var, val));
		}
		void Shutdown()
		{
			std::list<PairDescriptor*>::iterator iter;
			for(iter = input.begin(); iter != input.end(); iter++)
			{
				delete *iter;
			}
			for(iter = output.begin(); iter != output.end(); iter++)
			{
				delete *iter;
			}
		}
		std::list<PairDescriptor*> input;
		std::list<PairDescriptor*> output;
	};
}

#endif