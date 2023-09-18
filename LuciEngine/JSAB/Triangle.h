#pragma once
#include "LScript.h"
#include "LAudioSource.h"
#include "LAnimator.h"
#include "Player.h"
namespace lu::JSAB
{
	class Triangle : public Script
	{
	public:
		Triangle() {}
		virtual ~Triangle() {}
		virtual void OnCollisionEnter(Collider2D* other) override;

		void SetClips(std::shared_ptr<AudioClip> tuto, std::shared_ptr<AudioClip> level);
		void Setup();
		void OnTutoBurst();
		void OnLevelComplete();
	private:
		AudioSource* mAudio;
		Animator* mAnim;
		std::shared_ptr<AudioClip> mTuto;
		std::shared_ptr<AudioClip> mLevel;
		Player* mPlayer;
	};
}

