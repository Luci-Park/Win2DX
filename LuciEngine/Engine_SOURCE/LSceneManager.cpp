#include "LSceneManager.h"
#include "LPlayScene.h"
namespace lu
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
		mActiveScene = new PlayScene();
		mScenes.insert(std::make_pair(L"PlayScene", mActiveScene));
		mActiveScene->Initialize();
	}
	void SceneManager::Update()
	{
		if (mActiveScene != nullptr)
			mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		if (mActiveScene != nullptr)
			mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		if (mActiveScene != nullptr)
			mActiveScene->Render();
	}
	
	void SceneManager::Release()
	{
		for (auto it : mScenes)
		{
			delete it.second;
			it.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(std::wstring name)
	{
		auto it = mScenes.find(name);
		if (it == mScenes.end())
			return nullptr;
		mActiveScene->OnExit();
		mActiveScene = it->second;
		mActiveScene->OnEnter();
		return it->second;
	}
}