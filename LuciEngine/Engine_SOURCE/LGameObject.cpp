#include "LGameObject.h"
#include "LRenderer.h"
#include "LGraphicDevice_Dx11.h"
#include "LTransform.h"

namespace lu
{
	GameObject::GameObject(eLayerType layer)
		: mLayer(layer)
	{
		mTransform = AddComponent<Transform>();
	}

	GameObject::GameObject(eLayerType layer, Transform* parent)
		:mLayer(layer)
	{
		mTransform = AddComponent<Transform>();
		mTransform->SetParent(parent);
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
			{
				delete mComponents[i];
				mComponents[i] = nullptr;
			}
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr)
			{
				delete mScripts[i];
				mScripts[i] = nullptr;
			}
		}
	}

	void GameObject::Update()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr && mComponents[i]->GetState() == eState::Active)
				mComponents[i]->Update();
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr && mScripts[i]->GetState() == eState::Active)
				mScripts[i]->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr && mComponents[i]->GetState() == eState::Active)
				mComponents[i]->LateUpdate();
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr && mScripts[i]->GetState() == eState::Active)
				mScripts[i]->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr && mComponents[i]->GetState() == eState::Active)
				mComponents[i]->Render();
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr && mScripts[i]->GetState() == eState::Active)
				mScripts[i]->Render();
		}
	}

	void GameObject::SetState(eState state)
	{
		Entity::mState = state;
		if (Entity::Active == state)
			OnEnable();
		else if (Entity::InActive == state)
			OnDisable();
		const std::vector<Transform*>& children = mTransform->GetChildren();
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Owner()->SetState(state);
		}
		for (int i = 0; i < mComponents.size(); i++)
			mComponents[i]->SetState(state);
		for (int i = 0; i < mScripts.size(); i++)
			mScripts[i]->SetState(state);
	}

}