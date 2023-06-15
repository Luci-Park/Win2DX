#pragma once
#include "LScene.h"

namespace lu
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

	private:
		static Scene* mActiveScene;
	};
}

