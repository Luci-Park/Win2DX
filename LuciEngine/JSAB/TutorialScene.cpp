#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "LCamera.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "TrianglePrefab.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"
#include "TutorialBeatBar.h"
#include "TutorialBeatCircle.h"
#include "LObject.h"
#include "LInput.h"
#include "CameraScript.h"
#include "TutorialEightBar.h"

namespace lu::JSAB::Tutorial
{
	CameraScript* burst;
	void TutorialScene::Initialize()
	{
		//Camera
		{
			bool active[]{ true, true, true, true, false };
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
			burst = camera->AddComponent<CameraScript>();
		}

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TutorialManager");
		auto ma = manager->AddComponent<TutorialManager>();
		auto m = manager->AddComponent<TutorialMusicController>();
		ma->SetMusic(m);
		m->Play();
		//burst = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TutorialBeatBar>();
		/*auto a = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent <TutorialEightBar>();
		a->Activate();
		a->mTransform->SetPosition({ 0, 360 - 40 * 4, 1 });
		auto b = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent <TutorialEightBar>();
		b->Activate();
		b->mTransform->SetPosition({ 0, -360 + 40 * 4, 1 });*/
		object::Instantiate<PlayerPrefab>(eLayerType::Player);
		Scene::Initialize(); 
	}
	void TutorialScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::W))
			burst->OnBeat(Vector3::Up);

		if (Input::GetKeyDown(eKeyCode::S))
			burst->OnBeat(Vector3::Down);

		if (Input::GetKeyDown(eKeyCode::A))
			burst->OnBeat(Vector3::Left);

		if (Input::GetKeyDown(eKeyCode::D))
			burst->OnBeat(Vector3::Right);

		if (Input::GetKeyDown(eKeyCode::F))
			burst->OnFlash();
		Scene::Update();
	}
	void TutorialScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TutorialScene::Render()
	{
		Scene::Render();
	}
}
