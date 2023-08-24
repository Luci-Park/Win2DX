#pragma once
#include "MusicController.h"

namespace lu
{
	class AudioSource;
}

namespace lu::JSAB
{
	class TutorialMusicController : public MusicController
	{
	public:
		TutorialMusicController();

		virtual void Initialize() override;
		virtual void Update() override;
		void PlayNextPart();
	private:
		AudioSource* mAudioSource;
		std::vector<std::pair<double, double>> mCheckPoints;
		double mEndTime;
		double mTime;
		float mFadeDuration;
		float mFadeTime;
		float mStartVolume;
		int mStageIdx;
		int mNextStageIdx;
		bool mbIsPlaying;
	};
}

