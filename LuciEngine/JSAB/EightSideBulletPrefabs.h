#pragma once
#include "LGameObject.h"

namespace lu
{
	class MeshRenderer;
}

namespace lu::JSAB
{
	class TutorialEightBullets : public GameObject
	{
	public:
		TutorialEightBullets(){}
		virtual ~TutorialEightBullets(){}

		virtual void Initialize() override;
	private:
		void SetMeshRenderer(MeshRenderer* mr);
		void SetEnterEffect(MeshRenderer* mr);
		void CreateEnterEffect();
	};
}

