#include "TutorialManager.h"
#include "TutorialMusicController.h"
#include "TutorialRoundSpikes.h"
#include "TutorialBurst.h"
#include "TutorialBeam.h"
#include "TutorialBeatCircle.h"
#include "TutorialGiantCircle.h"
#include "BackgroundScript.h"
#include "LObject.h"
#include "LCamera.h"
#include "LAnimator.h"
#include "LApplication.h"
#include "TrianglePrefab.h"
#include "Triangle.h"
#include "CheckPoint.h"

extern lu::Application application;
namespace lu::JSAB
{
	TutorialManager::TutorialManager()
		: mRoundSpikes(70)
		, mBursts(32)
		, mBeams(63)
		, mBeatCircles(8)
		, mGCircles(6)
		, mCircleLines(8)
	{
		mTriangleAppearTime = 5;
	}
	void TutorialManager::Initialize()
	{
		mTutorialMusic = Owner()->GetComponent<TutorialMusicController>();
		mMusic = mTutorialMusic;
		mBackground = SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetBackground();
		mNextScene = L"TitleScene";

		mCheckPoint = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<CheckPoint>();
		mCheckPoint->SetBackground(SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetBackground());
		mCheckPoint->SetManager(this);
		mCheckPoint->SetIsFinal(true);
		mCheckPoint->SetTimeline(mMusic, 5, 164.800, 0);
		mCheckPoint->SetBackgroundType(BackgroundScript::eBackgrounds::BLACK);
	}
	void TutorialManager::Update()
	{
		if (mTutorialMusic->IsPlaying())
		{
			if (mTutorialMusic->GetStage() < 8)
			{
				float percent = mTutorialMusic->GetPercent();
				if (percent > 0.8 && !mLevelTriangle->IsActive())
				{
					mLevelTriangle->SetStrategy(TriangleStrategy::eTriangleStrategyType::Tutorial);
					mLevelTriangle->Appear();
				}
			}
		}
		MusicManager::Update();
	}
	void TutorialManager::Play()
	{
		MusicManager::Play();
		OnStageChange(0);
	}
	void TutorialManager::OnMusicEnd()
	{
		mRoundSpikes.Reset();
		mBeams.Reset();
		mBursts.Reset();
		mCircleLines.Reset();
		mBeatCircles.Reset();
		mGCircles.Reset();
		mMusic->Finish();
		mbFin = true;
	}
	void TutorialManager::OnStageChange(int stage)
	{
		if (stage == 0)
		{
			mBackground->SetBackground(BackgroundScript::eBackgrounds::BLACK);
			Stage1();
		}
		if (stage == 1)
		{
			mRoundSpikes.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::DARKBLUE);
			Stage2();
		}
		if (stage == 2)
		{
			mBursts.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::PURPLE);
			Stage3();
		}
		if (stage == 3)
		{
			mBursts.Reset();
			mBeams.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::TURQUOISE);
			Stage4();
		}
		if (stage == 4)
		{
			mBursts.Reset();
			mBeams.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::GREY);
			Stage5();
		}
		if (stage == 5)
		{
			mBursts.Reset();
			mBeams.Reset();
			mBeatCircles.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::PINK);
			Stage6();
		}
		if (stage == 6)
		{
			mBursts.Reset();
			mBeams.Reset();
			mRoundSpikes.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::BLACK);
			Stage7();
		}
		if (stage == 7)
		{
			mBursts.Reset();
			mBeams.Reset();
			mRoundSpikes.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::PURPLE);
			Stage8();
		}
		if (stage == 8)
		{
			mBeams.Reset();
			mRoundSpikes.Reset();
			mCircleLines.Reset();
			mBackground->SetBackground(BackgroundScript::eBackgrounds::PURPLE);
			Stage9();
			Stage10();
		}
	}
	void TutorialManager::Stage1()
	{
		double beat[] = {
			0.850, 1.450, 2.100, 2.500, 3.150, 4.200, 4.800, 5.450, 5.850, 6.500, 6.800, 7.150, 7.500
		};
		float posY[] = { -51, 41, 230, -230 };//normal, small high, very high, very low
		int idicies[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 2, 3, 2 };

		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		float x = bounds.right + 42 * 0.5;
		float endX = bounds.left - 42 * 0.5;
		for (int i = 0; i < 13; i++)
		{
			Vector3 pos = { x, posY[idicies[i]], 1 };
			Vector3 endPos = { endX, posY[idicies[i]], 1 };
			TutorialRoundSpikes* bullet = mRoundSpikes.GetNext();
			bullet->mTransform->SetPosition(pos);
			bullet->Setup(6, pos, endPos);
			bullet->SetTimeline(mMusic, 0, beat[i], 0);
		}
	}
	void TutorialManager::Stage2()
	{
		double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
		double beat[] = {8.2, 8.95, 9.8, 10.6, 11.5, 12.55, 13.45, 14.25};
		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		float move = 180;
		for (int i = 0; i < 8; i++)
		{
			auto bullet = mBursts.GetNext();
			if (i % 2 == 0)
				bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
			else
				bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
			bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
		}		
	}
	
	void TutorialManager::Stage3()
	{
		{
			double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
			double beat[] = { 15.128, 15.878, 16.728, 17.528, 18.428, 19.478, 20.378, 21.178 };
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			float move = 180;
			for (int i = 0; i < 9; i++)
			{
				auto bullet = mBursts.GetNext();
				if (i % 2 == 0)
					bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
				else
					bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
				bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
			}
		}
		{
			double beat[] =	{ 14.850, 15.500, 16.583, 17.235, 17.450, 18.313, 18.959, 20.242, 20.697, 21.025 };
			float y = application.GetHeight() * 0.5;
			float x[] = { -60, - 20, 20, 60, 100, 140, 180, 220, 260, 300	};

			for(int i =0; i < 10; i++)
			{
				auto bullet = mBeams.GetNext();
				bullet->mTransform->SetPosition({ x[i], y, 0 });
				bullet->SetTimeline(mMusic, 1.3, beat[i], 0.35);
			}
		}
	}
	void TutorialManager::Stage4()
	{
		{
			double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
			double beat[] = { 28.984, 29.734, 30.584, 31.384, 32.284, 33.334, 34.234, 35.034 };
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			float move = 180;
			for (int i = 0; i < 9; i++)
			{
				auto bullet = mBursts.GetNext();
				if (i % 2 == 0)
					bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
				else
					bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
				bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
			}
		}
		{
			double beat[] ={ 28.701, 29.350, 30.219, 30.868, 31.949, 32.598, 33.677, 34.326};
			float y = application.GetHeight() * 0.5;
			float x[] = { 200, -200, 100, -100 };
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					auto bullet = mBeams.GetNext();
					if(i % 2 == 0)
						bullet->mTransform->SetPosition({ x[j], y, 0 });
					else
						bullet->mTransform->SetPosition({ x[2 + j], y, 0 });
					bullet->SetTimeline(mMusic, 1.3, beat[i], 0.35);
				}
			}
		}
	}
	void TutorialManager::Stage5()
	{
		{
			double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
			double beat[] = {35.912, 36.662, 37.512, 38.312, 39.212, 40.262, 41.162, 41.962};
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			float move = 180;
			for (int i = 0; i < 9; i++)
			{
				auto bullet = mBursts.GetNext();
				if (i % 2 == 0)
					bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
				else
					bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
				bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
			}
		}
		{
			double beat[] ={ 35.403, 36.052, 36.921, 37.57,	38.651,	39.3, 40.379, 41.028 };

			float y = application.GetHeight() * 0.5;
			float x[][3] = { {-300, 0, 300}, {-150, 150, 0}};
			
			for(int i =0; i < 8; i++)
			{
				int num = i % 2 == 0 ? 3 : 2;
				for (int j = 0; j < num; j++)
				{
					auto bullet = mBeams.GetNext();
					bullet->mTransform->SetPosition({ x[i % 2][j], y, 0 });
					bullet->SetTimeline(mMusic, 1.3, beat[i], 0.35);
				}
			}
		}
		{
			double show[] = { 35.629, 38.221 };
			double beat[8] = {36.493, 36.601, 36.709, 36.817, 39.949, 40.057, 40.165, 40.273,};
			Vector3 pos[] = { {-230, 150, 1}, {230, 150, 1}, {-230, -150, 1}, {230, -150, 1} };
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					int idx = i * 4 + j;
					auto c = mBeatCircles.GetNext();
					c->mTransform->SetPosition(pos[j]);
					c->FastAnim(true);
					c->SetTimeline(mMusic, beat[idx]- show[i], beat[idx], 0);
				}
			}
		}
	}
	void TutorialManager::Stage6()
	{
		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		double warning[] = { .319, .662, .736, .662, .736, .834, .687, .662 };
		double beat[] = { 42.84, 43.59, 44.44, 45.24, 46.14, 47.19, 48.09, 48.89 };
		float move = 180;
		for (int i = 0; i < 9; i++)
		{
			auto bullet = mBursts.GetNext();
			if (i % 2 == 0)
				bullet->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
			else
				bullet->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });
			bullet->SetTimeline(mMusic, warning[i], beat[i], 0);
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				Vector3 pos = { 200.f * (i ? -1 : 1), bounds.top + 40.f * j, 0 };
				auto bullet = mRoundSpikes.GetNext();
				bullet->Setup(0, pos, pos);
				bullet->SetTimeline(mMusic, 0, beat[0] - warning[0], 0);
			}
		}
	}
	void TutorialManager::Stage7()
	{
		double beat[] = { 56.187, 56.624, 59.651 , 60.088 };

		for(int i =0; i < 4; i++)
		{
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			auto b = mBeams.GetNext();
			b->mTransform->SetPosition({ (float)bounds.right, application.GetHeight() * 0.5f,0});
			b->SetTimeline(mMusic, 0, beat[i], 0.35);
			if (i % 2)
			{
				RECT bounds = SceneManager::MainCamera()->GetBoundary();
				float x = bounds.right + 42 * 0.5;
				float endX = bounds.left - 42 * 0.5;
				for (int j = 0; j < 20; j++)
				{
					float y = bounds.top + 40.f * j;
					auto c = mRoundSpikes.GetNext();
					c->Setup(6, {x, y, 0}, {endX, y, 0});
					c->SetTimeline(mMusic, 0, beat[i], 0);
				}
			}
		}
	}
	void TutorialManager::Stage8()
	{
		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		double beat[] = { 70.043 , 70.480, 73.507 , 73.944 };
		double semibeat[2][7] =
		{
			{71.798, 71.959, 72.12,	72.28,	72.441,	72.601,	72.762},
			{75.262, 75.423, 75.583, 75.744, 75.905, 76.065, 76.226 }
		};
		double warnings[7];
		for (int i = 0; i < 7; i++)
			warnings[i] = semibeat[0][i] - beat[1] - 0.8;


		for (int i = 0; i < 4; i++)
		{
			auto b = mBeams.GetNext();
			b->mTransform->SetPosition({ (float)bounds.right, application.GetHeight() * 0.5f,0 });
			b->SetTimeline(mMusic, 0, beat[i], 0.35);
			if (i % 2)
			{
				float x = bounds.right + 42 * 0.5;
				float endX = bounds.left - 42 * 0.5;
				for (int j = 0; j < 20; j++)
				{
					float y = bounds.top + 40.f * j;
					auto c = mRoundSpikes.GetNext();
					c->Setup(6, { x, y, 0 }, { endX, y, 0 });
					c->SetTimeline(mMusic, 0, beat[i], 0);
				}
			}
		}
		float dist = 100;
		Vector3 pos[] = { {0, bounds.top + dist, 0 }, { 0, bounds.bottom - dist, 0 } };
		for (int i = 0; i < 2; i++)
		{
			auto c = mCircleLines.GetNext();
			c->FitToWidth();
			c->mTransform->SetPosition(pos[i]);
			c->SetTimeline(mMusic, 0.848, beat[0] + 0.848);
		}
		for (int i = 0; i < 2; i++)
		{
			auto c = mCircleLines.GetNext();
			c->FitToWidth();
			c->mTransform->SetPosition(pos[i]);
			c->SetTimeline(mMusic, 0.848, beat[2] + 0.848);
		}
		for (int i =0; i < 2; i++)
		{
			auto c = mCircleLines.GetNext();
			c->FitToWidth();
			c->mTransform->SetPosition(pos[i]);
			c->MultipleShow(mMusic, warnings, semibeat[0]);
		}
		for (int i = 0; i < 2; i++)
		{
			auto c = mCircleLines.GetNext();
			c->FitToWidth();
			c->mTransform->SetPosition(pos[i]);
			c->MultipleShow(mMusic, warnings, semibeat[1]);
		}
	}
	void TutorialManager::Stage9()
	{
		double beat[3] = { 111.611, 123.718, 125.035 };
		Vector3 pos[6] = { {-640, 360, 0}, {640, 360, 0}, {-640, -360, 0}, {640, -360, 0}, {0, -500, 0},{0, 500, 0} };

		for (int i = 0; i < 6;i++)
		{
			auto c = mGCircles.GetNext();
			c->mTransform->SetPosition(pos[i]);
			c->SetTimeline(mMusic, beat[1] - beat[0], beat[1], beat[2] - beat[1]);
		}
	}

	void TutorialManager::Stage10()
	{
		double startTime = 125.467;
		double timePerBeat = 0.432;
		int numberOfBeats = 63;
		RECT bounds = SceneManager::MainCamera()->GetBoundary();

		for (int i = 0; i < numberOfBeats; i++)
		{
			auto b = mBeams.GetNext();
			b->SetRandomPosition();
			b->SetTimeline(mMusic, 1.3, startTime + timePerBeat * i, 0.35);
		}
		for (int i = 0, j = 0; i < numberOfBeats; i += 2, j++)
		{
			float move = 180;
			auto b = mBursts.GetNext();
			if (j % 2 == 0)
				b->SetUp({ 500, (float)bounds.top, 0 }, { 500, (float)bounds.top + move, 0 });
			else
				b->SetUp({ 500, (float)bounds.bottom, 0 }, { 500, (float)bounds.bottom - move, 0 });

			b->SetTimeline(mMusic, 0.4, startTime + timePerBeat * i, 0);
		}
		{
			double beats[8] = { 127.15, 130.6, 134, 137.45, 140.85, 144.5, 147.9 };				
			for (int i = 0; i < 8; i++)
			{
				auto c = mCircleLines.GetNext();
				c->FitToHeight();
				double time[7];
				double warning[7];
				double step = 0.432 * 2 / 7;
				for (int j = 0; j < 7; j++)
				{
					time[j] = beats[i] + step * j;
					warning[j] = time[j] - beats[i] + 2;
				}
				c->MultipleShow(mMusic, warning, time);
			}
		}
		{
			double beats[7] = { 129.2, 132.55, 136.1, 139.45, 142.85, 146.2, 149.75 };
			float x = bounds.right + 42 * 0.5;
			float endX = bounds.left - 42 * 0.5;
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					float y = i%2 ? bounds.bottom - 40.f * j : bounds.top + 40.f * j;
					auto c = mRoundSpikes.GetNext();
					c->Setup(6, { x, y, 0 }, { endX, y, 0 });
					c->SetTimeline(mMusic, 0, beats[i], 0);
				}
			}
			for (int j = 0; j < 20; j++)
			{
				float y = bounds.top + 40.f * j;
				auto c = mRoundSpikes.GetNext();
				c->Setup(8, { x, y, 0 }, { endX, y, 0 });
				c->SetTimeline(mMusic, 0, 152.75, 0);
			}
		}
	}
}
