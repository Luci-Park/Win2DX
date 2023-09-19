#pragma once
#include "Bullet.h"
#include "DubwooferDropBullet.h"
#include "BulletPool.h"
namespace lu::JSAB
{
	class DubwooferDropSpawner : public Script//public Bullet
	{
	public:
		DubwooferDropSpawner();
		virtual ~DubwooferDropSpawner(){}

	private:
		virtual void BulletSetUp() {};

		virtual void OnWarning() {};
		virtual void WhileWarning(double time) {};
		virtual void OnActivate();
		virtual void WhileActivate(double time) = 0;
		virtual void OnOutro() {};
		virtual void WhileOutro(double time) {};
		virtual void OnDeActivate() {};
		Vector3 GetRandomSpawn();
	private:
		BulletPool<DubwooferDropBullet> mDrops;
		std::vector<Vector3> mSpawnPos;
		int mPrevSpawn;
	};
}

