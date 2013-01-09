#ifndef _FUZZY_MEMBERSHIPFUNCTION_H_
#define _FUZZY_MEMBERSHIPFUNCTION_H_

#include "buffer.h"
#include <string>

namespace Fuzzy
{
	class MembershipFunction
	{
	public:
		MembershipFunction();
		MembershipFunction(std::string name);
		MembershipFunction(const MembershipFunction& other);
		~MembershipFunction();

		float Fuzzify(float input);
		float Peek(float input);
		virtual bool Initialize(float* params);
		virtual float Centroid() = 0;

		Buffer* GetBuffer();
		std::string GetID();

	protected:
		float m_minRange;
		float m_maxRange;
		float m_centroid;
		
		virtual float Evaluate(float input) = 0;
		std::string m_name;
		Buffer* m_buffer;
	};
}

#endif