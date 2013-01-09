#ifndef _FUZZY_RULE_H_
#define _FUZZY_RULE_H_

#include "buffer.h"
#include <list>

namespace Fuzzy
{
	class Rule
	{
	public:
		Rule();
		Rule(int iSize, int oSize);
		Rule(const Rule&);
		~Rule();

		void SetBuffers(Buffer** input, Buffer** output);
		Buffer** GetInputBuffer();
		Buffer** GetOutputBuffer();

		bool Fire();

	private:
		int m_inputCount, m_outputCount;
		Buffer** m_input;
		Buffer** m_output;
	};
}

#endif