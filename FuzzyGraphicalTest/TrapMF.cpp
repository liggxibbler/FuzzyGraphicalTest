#include "trapMF.h"

using namespace Fuzzy;

TrapMF::TrapMF(float min, float max)
{
	m_minRange = min;
	m_maxRange = max;
}

TrapMF::TrapMF()
{
}

TrapMF::TrapMF(const TrapMF& other)
{
}

TrapMF::~TrapMF()
{
}

bool TrapMF::Initialize(float* params)
{
	MembershipFunction::Initialize(params);

	if(!params)
	{
		return false;
	}
	
	m_left = params[0];
	m_midL = params[1];
	m_midL = params[2];
	m_right = params[3];
	
	CalculateCentroid();

	return true;
}

float TrapMF::Evaluate(float input)
{
	float m;
	static float epsilon;
	epsilon = (m_maxRange - m_minRange) / BIG_NUMBER;

	if(input < m_minRange)
	{
		return Evaluate(m_minRange + epsilon);
	}
	else if(input >= m_minRange && input < m_left)
	{
		return 0;
	}
	else if(input >= m_left && input < m_midL)
	{
		m = 1 / (m_midL - m_left); // slope of left side line segment
		return m * (input - m_left); // line equation
	}
	else if(input >= m_midL && input < m_midR)
	{
		return 1.0f;
		
	}
	else if(input >= m_midR && input < m_right)
	{
		m = (-1) / (m_right - m_midR); // slope of right side line segment
		return 1 + m * (input - m_midR); // line equation
	}
	else if(input >= m_right && input < m_maxRange)
	{
		return 0;
	}
	else if(input > m_maxRange)
	{
		return Evaluate(m_maxRange - epsilon);
	}

	return -1;
}

void TrapMF::CalculateCentroid()
{
	
}

float TrapMF::Centroid()
{
	return m_centroid;
}