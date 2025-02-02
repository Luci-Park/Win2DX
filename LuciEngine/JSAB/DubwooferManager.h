#pragma once
#include "MusicManager.h"
#include "BulletPool.h"
namespace lu::JSAB
{
	class DubwooferDropSpawner;
	class DubwooferSpikeDropper;
	class DubwooferBeamBullet;
	class TutorialBeam;
	class MusicController;
	class CheckPoint;
	class DubwooferWater;
	class DubwooferManager : public MusicManager
	{
	public:
		DubwooferManager();
		virtual ~DubwooferManager() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Play() override;
		virtual void OnMusicEnd() override;
	private:
		void Drops(double time);
		void Spikes(double time);
		void BigBar(double time);
		void SmallBar(double time);
		void CheckPoints(double time);
		void Water(double time);
	private:
		CheckPoint* mCheckPoint;
		DubwooferDropSpawner* mDrops;
		DubwooferSpikeDropper* mSpikes;
		DubwooferWater* mWater;
		BulletPool<DubwooferBeamBullet> mThickBeams;
		BulletPool<TutorialBeam> mThinBeams;
		int mDropFlag;
		int mSpikeFlag;
		int mSpikeAppearFlag;
		int mBigBarFlag;
		int mSmallBarFlag;
		int mCheckPointFlag;
	};
}

