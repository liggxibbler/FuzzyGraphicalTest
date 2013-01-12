#ifndef _FUZZY_TrapMF_H_
#define _FUZZY_TrapMF_H_

#define BIG_NUMBER 65536

#include "membershipFunction.h"

namespace Fuzzy
{
	class TrapMF : public MembershipFunction
	{
	public:
		TrapMF(float min, float max);
		TrapMF();
		TrapMF(const TrapMF& other);
		~TrapMF();

		virtual bool Initialize(float* params);
		virtual float Centroid();
	protected:
		virtual float Evaluate(float input);
	private:
		void CalculateCentroid();
		float m_left;
		float m_midL;
		float m_midR;
		float m_right;
	};
}

#endif