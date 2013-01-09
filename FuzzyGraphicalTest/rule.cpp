#include "rule.h"

using namespace Fuzzy;

Rule::Rule()
{
	m_input = 0;
	m_output = 0;
}

Rule::Rule(int iSize, int oSize)
{
	m_inputCount = iSize;
	m_outputCount = oSize;
	m_input = new Buffer*[m_inputCount];
	m_output = new Buffer*[m_outputCount];
}

Rule::Rule(const Rule& other)
{
}

Rule::~Rule()
{
}

void Rule::SetBuffers(Buffer** input, Buffer** output)
{
	m_input = input;
	m_output = output;
}

bool Rule::Fire()
{
	float result = 1.0f;
	float val;

	for(int i=0; i<m_inputCount; i++)
	{
		if(!m_input[i])
		{
			return false;
		}
		val = m_input[i]->Read();
		result = val < result ? val : result; // fuzzy AND the outputs
	}

	for(int i=0; i<m_outputCount; i++)
	{
		m_output[i]->Max(result);
	}

	return true;
}

Buffer** Rule::GetInputBuffer()
{
	return m_input;
}

Buffer** Rule::GetOutputBuffer()
{
	return m_output;
}