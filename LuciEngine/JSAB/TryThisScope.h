#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TryThisScope : public Bullet
	{
	public:
		TryThisScope(){}
		virtual ~TryThisScope(){}
		virtual void Update() override;
		void SetPosition(Vector3 pos) { mTarget = pos; }
	private:
		virtual void BulletSetUp() override;

		virtual void OnWarning() override;
		virtual void WhileWarning(double time) override;
		virtual void OnActivate() override;
		virtual void WhileActivate(double time) override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time) override;
		virtual void OnDeActivate() override;
	private:
		Transform* mHole;
		MeshRenderer* mMr;
		Animator* mHoleAnim;
		float mRotateSpeed;
		Vector3 mTarget;
		float mTime;
	};
}

