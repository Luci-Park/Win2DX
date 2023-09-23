#pragma once
#include "LScript.h"
#include "BulletPool.h"
namespace lu::JSAB
{
	class DubwooferDropSpawner;
	class DubwooferSpikeDropper;
	class DubwooferBeamBullet;
	class TutorialBeam;
	class MusicController;
	class DubwooferManager : public Script
	{
	public:
		DubwooferManager();
		virtual ~DubwooferManager() {}

		virtual void Initialize() override;
		virtual void Update() override;
	private:
		void Drops(double time);
		void Spikes(double time);
	private:
		DubwooferDropSpawner* mDrops;
		DubwooferSpikeDropper* mSpikes;
		BulletPool<DubwooferBeamBullet> mThickBeams;
		BulletPool<TutorialBeam> mThinBeams;
		MusicController* mMusic;
	};
}

