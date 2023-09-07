#include "TestScene.h"
#include "LObject.h"
#include "PlayerPrefab.h"
#include "LParticleSystem.h"
#include "LResources.h"
#include "LCamera.h"
namespace lu::JSAB
{
	TestScene::TestScene()
	{
	}
	TestScene::~TestScene()
	{
	}
	void TestScene::Initialize()
	{
		{
			bool active[]{ true, true, true, true, false };
			GameObject* camera = object::Instantiate<GameObject>(eLayerType::Camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
		}
		auto a = object::Instantiate<PlayerPrefab>(eLayerType::Player);
		auto p = a->AddComponent<ParticleSystem>();
		p->GetMaterial()->SetTexture(Resources::Find<Texture>(L"player1"));
		
		p->MaxParticles = 1000;
		p->Loop = true;

		p->SetLifeTime(30.f);
		p->SetSize(30, 0);
		p->SetTint({ 0, 0, 1, 0.5 }, { 0, 0, 1, 0.5 });
		p->SetRotation(45, 30);
		p->SetWorldSpace(ParticleSystem::Space::world);
		p->SetGravity(10);
		p->SetStartSpeed(20);
		p->Play();

	}
}