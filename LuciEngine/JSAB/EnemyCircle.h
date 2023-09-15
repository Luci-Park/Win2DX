#pragma once
#include "Enemy.h"

namespace lu::JSAB
{
	class EnemyCircle : public Enemy
	{
	private:
		virtual void BulletSetUp() override;

		virtual void OnDeActivate() override;
		virtual void OnWarning() override;
		virtual void WhileWarning(double time) override;
		virtual void OnActivate() override;
		virtual void WhileActivate(double time) override;
		virtual void OnOutro() override;
		virtual void WhileOutro(double time) override;

		void CreateAnimation();
	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		std::shared_ptr<Texture> mReadySprite;
		std::shared_ptr<Texture> mActivateSprite;
	};
}
