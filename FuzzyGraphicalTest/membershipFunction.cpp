#include "membershipFunction.h"

using namespace Fuzzy;

MembershipFunction::MembershipFunction()
{
	m_buffer = 0;
}

MembershipFunction::MembershipFunction(std::string name)
{
	m_buffer = 0;
	m_name = name;
}

MembershipFunction::MembershipFunction(const MembershipFunction& other)
{
}

MembershipFunction::~MembershipFunction()
{
}

Buffer* MembershipFunction::GetBuffer()
{
	return m_buffer;
}

float MembershipFunction::Fuzzify(float input)
{
	float output = Evaluate(input);
	m_buffer->Write(output);
	return output;
}

float MembershipFunction::Peek(float input)
{
	return Evaluate(input);
}

bool MembershipFunction::Initialize(float* params)
{
	m_buffer = new Buffer();
	if(!m_buffer)
	{
		return false;
	}
	return true;
}