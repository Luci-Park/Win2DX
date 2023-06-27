#pragma once
#include "LScene.h"

namespace lu
{
	class lu::JSAB::BackgroundScript;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
		lu::JSAB::BackgroundScript* bs;
	};
}

