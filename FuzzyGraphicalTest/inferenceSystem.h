#ifndef _FUZZY_INFERENCESYSTEM_H_
#define _FUZZY_INFERENCESYSTEM_H_

#include "linguisticVariable.h"
#include "ruleBase.h"
#include "ruleDescriptor.h"
#include <list>
#include <map>

namespace Fuzzy
{
	class InferenceSystem
	{
	public:
		InferenceSystem();
		InferenceSystem(const InferenceSystem& other);
		~InferenceSystem();

		float* Evaluate(float* input);
		virtual void Initialize() = 0;

		LinguisticVariable* AddInputLV(std::string name, float min, float max);
		LinguisticVariable* AddOutputLV(std::string name, float min, float max);
		bool AddRule(RuleDescriptor* ruleDesc, int ruleCount);

	private:
		std::map<std::string, LinguisticVariable*> m_mapVar;
		std::list<LinguisticVariable*> m_input;
		std::list<LinguisticVariable*> m_output;
		float* m_outputArray;
		RuleBase* m_ruleBase;
	};
}

#endif