#include "ruleBase.h"

using namespace Fuzzy;

RuleBase::RuleBase()
{
	m_inputCount = 0;
	m_outputCount = 0;
}

RuleBase::RuleBase(int iSize, int oSize)
{
	m_inputCount = iSize;
	m_outputCount = oSize;
}

RuleBase::RuleBase(const RuleBase& other)
{
}

RuleBase::~RuleBase()
{
}

void RuleBase::Fire()
{
	Rule* rule;
	std::list<Rule*>::iterator iter;

	for(iter = m_rules.begin(); iter != m_rules.end(); iter++)
	{
		rule = *iter;
		rule->Fire();
	}
}

void RuleBase::AddRule(Rule* rule)
{
	m_rules.push_back(rule);
}