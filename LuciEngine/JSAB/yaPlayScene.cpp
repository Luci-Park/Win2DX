#include "yaPlayScene.h"
#include "LTransform.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LMesh.h"
#include "yaCameraScript.h"
#include "LCamera.h"
#include "LSceneManager.h"
#include "BackgroundObject.h"
#include "LRenderer.h"
#include "LCollider2D.h"
#include "LObject.h"
#include "yaPlayerScript.h"
#include "LCollisionManager.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"

namespace lu
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		{
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

			player->SetName(L"Zelda");

			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.2f, 1.2f));

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));

			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			player->GetComponent<Transform>()->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, degree));
			player->AddComponent<gui::TransformWidget>();

			GameObject* child
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

			child->SetName(L"Zelda");
			child->mTransform->SetParent(player->mTransform);

			cd = child->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.2f, 1.2f));

			mr = child->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));

			degree = pi / 8.0f;

			child->GetComponent<Transform>()->SetLocalPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			//child->GetComponent<Transform>()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, degree));
		}

		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Bullet);
			player->SetName(L"Smile");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			Collider2D* cd = player->AddComponent<Collider2D>();
			//player->AddComponent<PlayerScript>();
		}

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->SetSize(5.0f);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			//camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Vector3 pos(800, 450, 0.0f);
		Vector3 pos2(800, 450, 1000.0f);
		Viewport viewport;
		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}