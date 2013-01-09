#ifndef _FUZZY_LINGUISTICVARIABLE_H_
#define _FUZZY_LINGUISTICVARIABLE_H_

#include "membershipFunction.h"
#include "triMF.h"
#include <list>
#include <string>
#include <map>

namespace Fuzzy
{
	enum DEFUZZ_METHOD
	{
		DEFUZZ_METHOD_CENTROID,
		DEFUZZ_METHOD_WEIGHTED_MF
	};

	class LinguisticVariable
	{
	public:
		LinguisticVariable();
		LinguisticVariable(std::string name, float min, float max);
		LinguisticVariable(const LinguisticVariable& other);
		~LinguisticVariable();

		void ClearBuffers();
		void Fuzzify(float input);
		float Defuzzify(DEFUZZ_METHOD dm, int numPoints);
		MembershipFunction* AddTriMF(std::string name, float *params);

		std::string GetName();
		MembershipFunction* GetMF(std::string name);

	private:
		float IntegrateTrapezoidal(float* integrant, int numPoints, float dx);
		float Centroid(int numPoints);
		float WeightedMF();

	private:
		std::map<std::string, MembershipFunction*> m_mapMF;
		std::string m_name;
		float m_minRange;
		float m_maxRange;
		std::list<MembershipFunction*> m_mf;
	};
}

#endif