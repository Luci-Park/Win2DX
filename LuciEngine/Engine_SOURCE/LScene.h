#pragma once
#include "LEntity.h"
#include "LLayer.h"
namespace lu
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<Layer*> mLayers;
	};
}

