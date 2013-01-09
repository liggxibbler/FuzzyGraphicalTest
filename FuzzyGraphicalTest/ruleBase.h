#ifndef _FUZZY_RULEBASE_H_
#define _FUZZY_RULEBASE_H_

#include "rule.h"
#include <list>

namespace Fuzzy
{
	class RuleBase
	{
	public:
		RuleBase();
		RuleBase(int iSize, int oSize);
		RuleBase(const RuleBase& other);
		~RuleBase();

		void Fire();
		void AddRule(Rule* rule);

	private:
		int m_inputCount;
		int m_outputCount;
		std::list<Rule*> m_rules;
	};
}

#endif