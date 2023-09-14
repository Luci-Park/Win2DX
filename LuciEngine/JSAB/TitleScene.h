#pragma once
#include "..\Engine_SOURCE\LScene.h"
namespace lu
{
	class AudioSource;
	class AudioClip;
	class GameObject;
	class Animator;
}
namespace lu::JSAB
{
	class BackgroundScript;
	class TitleObject;
	class MenuButtonObject;
	class CameraEffectScript;
}
namespace lu::JSAB::Title
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		void StartMusic();
	private:
		BackgroundScript* mbgs;
		TitleObject* mTitle;
		AudioSource* mbgm;
		MenuButtonObject* mButton;
		CameraEffectScript* mCamera;
		Animator* mText;
		bool mbIsInMenu;
		std::shared_ptr<AudioClip> mAudios[3];
	};
}

