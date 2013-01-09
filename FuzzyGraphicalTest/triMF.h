#ifndef _FUZZY_TRIMF_H_
#define _FUZZY_TRIMF_H_
#define BIG_NUMBER 65536
#include "membershipFunction.h"

namespace Fuzzy
{
	class TriMF : public MembershipFunction
	{
	public:
		TriMF(float min, float max);
		TriMF();
		TriMF(const TriMF& other);
		~TriMF();

		virtual bool Initialize(float* params);
		virtual float Centroid();
	protected:
		virtual float Evaluate(float input);
	private:
		void CalculateCentroid();
		float m_left;
		float m_mid;
		float m_right;
	};
}

#endif