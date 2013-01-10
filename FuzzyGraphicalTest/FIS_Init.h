#include "inferenceSystem.h"

namespace Fuzzy
{
	class FIS_Init : public InferenceSystem
	{
	public:
		virtual void Initialize()
		{
			LinguisticVariable *position, *velocity, *steer;
			RuleDescriptor rd[9];
			float params[3];

			position = this->AddInputLV("position", -1.0f, 1.0f);
			params[0] = -2.0f; params[1] = -1.0f; params[2] = 0.0f;
			position->AddTriMF("left", params);
			params[0] = -0.5f; params[1] = 0.0f; params[2] = 0.5f;
			position->AddTriMF("mid", params);
			params[0] = 0.0f; params[1] = 1.0f; params[2] = 2.0f;
			position->AddTriMF("right", params);

			velocity = this->AddInputLV("velocity", -1.0f, 1.0f);
			params[0] = -2.0f; params[1] = -1.0f; params[2] = 0.0f;
			velocity->AddTriMF("left", params);
			params[0] = -0.5f; params[1] = 0.0f; params[2] = 0.5f;
			velocity->AddTriMF("slow", params);
			params[0] = 0.0f; params[1] = 1.0f; params[2] = 2.0f;
			velocity->AddTriMF("right", params);

			steer = this->AddOutputLV("steer", -1.0f, 1.0f);
			params[0] = -2.0f; params[1] = -1.0f; params[2] = 0.0f;
			steer->AddTriMF("left", params);
			params[0] = -0.5f; params[1] = 0.0f; params[2] = 0.5f;
			steer->AddTriMF("center", params);
			params[0] = 0.0f; params[1] = 1.0f; params[2] = 2.0f;
			steer->AddTriMF("right", params);

			rd[0].AddInPair("position", "left");
			rd[0].AddInPair("velocity", "left");
			rd[0].AddOutPair("steer", "right");
			this->AddRule(&rd[0], 0);

			rd[1].AddInPair("position", "left");
			rd[1].AddInPair("velocity", "slow");
			rd[1].AddOutPair("steer", "right");
			this->AddRule(&rd[1], 0);

			rd[2].AddInPair("position", "left");
			rd[2].AddInPair("velocity", "right");
			rd[2].AddOutPair("steer", "center");
			this->AddRule(&rd[2], 0);

			rd[3].AddInPair("position", "mid");
			rd[3].AddInPair("velocity", "left");
			rd[3].AddOutPair("steer", "right");
			this->AddRule(&rd[3], 0);

			rd[4].AddInPair("position", "mid");
			rd[4].AddInPair("velocity", "slow");
			rd[4].AddOutPair("steer", "center");
			this->AddRule(&rd[4], 0);

			rd[5].AddInPair("position", "mid");
			rd[5].AddInPair("velocity", "right");
			rd[5].AddOutPair("steer", "left");
			this->AddRule(&rd[5], 0);

			rd[6].AddInPair("position", "right");
			rd[6].AddInPair("velocity", "left");
			rd[6].AddOutPair("steer", "center");
			this->AddRule(&rd[6], 0);

			rd[7].AddInPair("position", "right");
			rd[7].AddInPair("velocity", "slow");
			rd[7].AddOutPair("steer", "left");
			this->AddRule(&rd[7], 0);

			rd[8].AddInPair("position", "right");
			rd[8].AddInPair("velocity", "right");
			rd[8].AddOutPair("steer", "left");
			this->AddRule(&rd[8], 0);
		}
	};
}