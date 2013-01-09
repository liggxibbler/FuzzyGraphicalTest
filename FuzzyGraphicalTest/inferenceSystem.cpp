#include "inferenceSystem.h"

using namespace Fuzzy;

InferenceSystem::InferenceSystem()
{
	m_ruleBase = new RuleBase();
	m_outputArray = 0;
}

InferenceSystem::InferenceSystem(const InferenceSystem& other)
{
}

InferenceSystem::~InferenceSystem()
{
}

float* InferenceSystem::Evaluate(float* input)
{
	LinguisticVariable* lv;
	std::list<LinguisticVariable*>::iterator iter;
	static float* output;

	for(iter = m_output.begin(); iter != m_output.end(); iter++)
	{
		lv = *iter;
		lv->ClearBuffers();
	}

	// Fuzzify input vars
	int index = 0;
	for(iter = m_input.begin(); iter != m_input.end(); iter++)
	{
		lv = *iter;
		lv->ClearBuffers();
		lv->Fuzzify(input[index++]);
	}

	// Evaluate rules
	m_ruleBase->Fire();

	// Instantiate ouput array
	if(!m_outputArray)
	{
		m_outputArray = new float[m_output.size()];
	}

	// Defuzzify output vars and store in array
	index = 0;
	for(iter = m_output.begin(); iter != m_output.end(); iter++)
	{
		lv = *iter;
		m_outputArray[index++] = lv->Defuzzify(DEFUZZ_METHOD_CENTROID, 100);
	}

	return m_outputArray;
}

LinguisticVariable* InferenceSystem::AddInputLV(std::string name, float min, float max)
{
	LinguisticVariable* lv;
	lv = new LinguisticVariable(name, min, max);
	m_mapVar[name] = lv;
	m_input.push_back(lv);

	return lv;
}

LinguisticVariable* InferenceSystem::AddOutputLV(std::string name, float min, float max)
{
	LinguisticVariable* lv;
	lv = new LinguisticVariable(name, min, max);
	m_mapVar[name] = lv;
	m_output.push_back(lv);

	return lv;
}

bool InferenceSystem::AddRule(RuleDescriptor* ruleDesc, int ruleCount)
{
	int inputCount = ruleDesc->input.size();
	int outputCount = ruleDesc->output.size();
	
	Rule* rule = new Rule(inputCount, outputCount);
	Buffer** buffer = rule->GetInputBuffer();

	PairDescriptor* pd;
	LinguisticVariable* lv;
	MembershipFunction* mf;
	int i;

	std::list<PairDescriptor*>::iterator iter;	

	i=0;
	for(iter = ruleDesc->input.begin(); iter != ruleDesc->input.end(); iter++)
	{
		pd = *iter;
		lv = m_mapVar[pd->variable];
		mf = lv->GetMF(pd->value);
		buffer[i++] = mf->GetBuffer();
	}

	i=0;
	buffer = rule->GetOutputBuffer();
	for(iter = ruleDesc->output.begin(); iter != ruleDesc->output.end(); iter++)
	{
		pd = *iter;
		lv = m_mapVar[pd->variable];
		mf = lv->GetMF(pd->value);
		buffer[i++] = mf->GetBuffer();
	}
	
	m_ruleBase->AddRule(rule);
	
	return true;
}