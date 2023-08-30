#include "TutorialManager.h"
#include "TutorialMusicController.h"
#include "TutorialBeatBar.h"
#include "LObject.h"
#include "LCamera.h"
#include "LAnimator.h"
#include "LApplication.h"
#include "TutorialEightBullets.h"
#include "TutorialBurst.h"
#include "TutorialBeatCircle.h"

extern lu::Application application;
namespace lu::JSAB
{
	TutorialManager::TutorialManager()
		: mStage1Bullets(13)
		, mBurstBullets(8)
		, mBeatBars(10)
		, mBeatCircles(4)
	{
	}
	void TutorialManager::Initialize()
	{
	}
	void TutorialManager::Update()
	{
		double time = MusicController::_MusicController->GetTime();
		int stage = MusicController::_MusicController->GetStage();

		if (stage == 0)Stage1(time);
		if (stage == 1)Stage2(time);
		if (stage == 2)Stage3(time);
		if (stage == 3)Stage4(time);
		if (stage == 4)Stage5(time);
		if (stage == 5)Stage6(time);
		if (stage == 6)Stage7(time);
		if (stage == 7)Stage8(time);
		if (stage == 8)Stage9(time);
		if (stage == 9)Stage10(time);
	}
	void TutorialManager::Stage1(double time)
	{
		const double beat[] = {
			0.763, 1.430, 2.079, 2.497, 3.163, 4.255, 4.886, 5.520, 5.980, 6.638, 6.855, 7.173, 7.471
		};
		const float posY[] = { -51, 41, 230, -230 };//normal, small high, very high, very low
		const int idicies[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 2, 3, 2 };
		static int idx = 0;

		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		float x = bounds.right + 42 * 0.5;
		float endX = bounds.left - 42 * 0.5;
	
		if (idx >= 13 && beat[12] > time)
			idx = 0;
		
		if (idx < 13 && beat[idx] <= time)
		{
			Vector3 pos = { x, posY[idicies[idx]], 1 };
			Vector3 endPos = { endX, posY[idicies[idx]], 1 };
			TutorialEightBullets* bullet = mStage1Bullets.GetNext();
			bullet->mTransform->SetPosition(pos);
			bullet->Setup(7, pos, endPos);
			bullet->Activate();
			idx++;
		}
	}
	void TutorialManager::Stage2(double time)
	{
		const double beat[] = {
			7.691, 8.566, 9.441, 10.316, 11.191, 12.066, 12.941, 13.816
		};
		static int idx = 0;
		if (idx >= 8 && beat[7] > time)
			idx = 0;
		if (idx < 8 && beat[idx] <= time)
		{
			auto bullet = mBurstBullets.GetNext();
			bullet->IsEven(idx % 2 == 0);
			bullet->Activate();
			idx++;
		}
		
	}
	void TutorialManager::Stage3(double time)
	{
		{
			const double beat[] = {
				14.619,	15.494,	16.369,	17.244,	18.119,	18.994,	19.9, 20.7
			};
			static int idx = 0;
			if (idx >= 8 && beat[7] > time)
				idx = 0;
			if (idx < 8 && beat[idx] <= time)
			{
				auto bullet = mBurstBullets.GetNext();
				bullet->IsEven(idx % 2 == 0);
				bullet->Activate();
				idx++;
			}
		}
		{
			const double beat[] =
			{ 
				14.850, 15.500, 16.583, 17.235, 17.450, 18.313, 18.959, 20.242, 20.697, 21.025
				//14.854, 15.557, 16.562, 17.232, 17.467, 18.374, 18.924, 20.063, 20.7, 21.035
			};
			const float y = application.GetHeight() * 0.5;
			const float x[] = 
			{ 
				-60, - 20, 20, 60, 100, 140, 180, 220, 260, 300
			};
			static int idx = 0;
			if (idx >= 10 && beat[9] > time)
				idx = 0;
			if (idx < 10 && beat[idx]<= time)
			{
				auto bullet = mBeatBars.GetNext();
				bullet->mTransform->SetPosition({ x[idx], y, 0 });
				bullet->Activate();
				idx++;
			}
			
		}
	}
	void TutorialManager::Stage4(double time)
	{
		{
			const double beat[] = { 
				28.475,	29.35,	30.225,	31.1, 31.975, 32.85, 33.756, 34.556
			};
			static int idx = 0;
			if (idx >= 8 && beat[7] > time)
				idx = 0;
			if (idx < 8 && beat[idx] <= time)
			{
				auto bullet = mBurstBullets.GetNext();
				bullet->IsEven(idx % 2 == 0);
				bullet->Activate();
				idx++;
			}
		}
		{
			const double beat[] =
			{ 

				28.701, 29.350, 30.219, 30.868, 31.949, 32.598, 33.677, 34.326
				//28.701,	29.565,	30.429,	31.293,	32.157,	33.021,	33.885,	34.749,	35.613
			};

			const float y = application.GetHeight() * 0.5;
			const float x[] = { 200, -200, 100, -100 };
			static int idx = 0;
			if (idx >= 8 && beat[7] > time)
				idx = 0;
			if (idx < 8 && beat[idx] <= time)
			{
				for (int i = 0; i < 2; i++)
				{
					auto bullet = mBeatBars.GetNext();
					if (idx % 2 == 0)
						bullet->mTransform->SetPosition({ x[i], y, 0 });
					else
						bullet->mTransform->SetPosition({ x[2 + i], y, 0 });
					bullet->Activate();
				}
				idx++;
			}
		}
	}
	void TutorialManager::Stage5(double time)
	{
		{
			const double beat[] = {
				35.403,	36.278,	37.153,	38.028,	38.903,	39.778,	40.684,	41.484
			};
			static int idx = 0;
			if (idx >= 8 && beat[7] > time)
				idx = 0;
			if (idx < 8 && beat[idx] <= time)
			{
				auto bullet = mBurstBullets.GetNext();
				bullet->IsEven(idx % 2 == 0);
				bullet->Activate();
				idx++;
			}
		}
		{
			const double beat[] =
			{ 
				35.403,	36.052,	36.921,	37.57,	38.651,	39.3,	40.379,	41.028
				//35.629,	36.493,	37.357,	38.221,	39.085,	39.949,	40.813,	41.677
			};

			const float y = application.GetHeight() * 0.5;
			const float x[][3] = { {-300, 0, 300}, {-150, 150, 0}};
			static int idx = 0;
			if (idx >= 8 && beat[7] > time)
			{
				idx = 0;
			}
			if (idx < 8 && beat[idx] < time)
			{
				int num = idx % 2 == 0 ? 3 : 2;
				for (int i = 0; i < num; i++)
				{
					auto bullet = mBeatBars.GetNext();
					bullet->mTransform->SetPosition({ x[idx % 2][i], y, 0 });
					bullet->Activate();
				}
				idx++;
			}
		}
		{
			const double beat[] = { 35.629,
				36.493,	36.601,	36.709,	36.817,
				38.221,
				39.949,	40.057,	40.165,	40.273,
			};
			static int idx = 0;
			const Vector3 pos[] = { {-230, 150, 1}, {230, 150, 1}, {-230, -150, 1}, {230, -150, 1} };
			while (idx < 10 && beat[idx] < time)
			{
				if (idx == 0 || idx == 5)
				{
					for (int i = 0; i < 4; i++)
					{
						auto c = mBeatCircles.GetNext();
						c->mTransform->SetPosition(pos[i]);
						c->Show();						
					}
				}
				else
				{
					mBeatCircles.GetNext()->Activate();
				}
				idx++;
			}
			if (idx >= 10 && beat[9] > time)
				idx = 0;
		}
	}
	void TutorialManager::Stage6(double time)
	{
	}
	void TutorialManager::Stage7(double time)
	{
	}
	void TutorialManager::Stage8(double time)
	{
	}
	void TutorialManager::Stage9(double time)
	{
	}
	void TutorialManager::Stage10(double time)
	{
	}
}