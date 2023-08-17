
#include "LAnimation.h"
#include "LTime.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LCollider2D.h"
#include "LMeshRenderer.h"

namespace lu
{
	Animation::Animation(GameObject* owner)
		:Resource(enums::eResourceType::Animation)
	{
		mTr = owner->mTransform;
		mCd = owner->GetComponent<Collider2D>();
		mMr = owner->GetComponent<MeshRenderer>();
		mTimelines = std::vector<Timeline*>((UINT)eAnimationType::End);
		SetAnimationFunctions();
	}
	Animation::~Animation()
	{
		for (int i = 0; i < mTimelines.size(); i++)
			if (mTimelines[i])
			{
				delete mTimelines[i];
				mTimelines[i] = nullptr;
			}
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mbComplete) return;

		mTime += Time::DeltaTime();
		for (int i = 0; i < (UINT)eAnimationType::End; i++)
		{
			Timeline* timeline = mTimelines[i];
			if (timeline == nullptr) continue;
			if (timeline->IsComplete()) continue;
			mAnimFunctions[i](timeline);			
		}
		if (mTime > mDuration)
		{
			mbComplete = true;
		}
	}
	void Animation::Render()
	{
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		for (int i = 0; i < (UINT)eAnimationType::End; i++)
		{
			if(mTimelines[i])
				mTimelines[i]->Reset();
		}
	}

	void Animation::AddPositionKey(float timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrPosition);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddScaleKey(float timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrScale);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddRotationKey(float timestamp, Quaternion quaternion)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrRotation);
		if (timestamp > mDuration)
			mDuration = timestamp;
		QuaternionKey* key = new QuaternionKey();
		key->timestamp = timestamp;
		key->value = quaternion;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddLocalPositionKey(float timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrLocalPosition);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddLocalScaleKey(float timestamp, Vector3 vector3)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrLocalScale);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector3Key* key = new Vector3Key();
		key->timestamp = timestamp;
		key->value = vector3;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddLocalRotationKey(float timestamp, Quaternion quaternion)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::TrLocalRotation);
		if (timestamp > mDuration)
			mDuration = timestamp;
		QuaternionKey* key = new QuaternionKey();
		key->timestamp = timestamp;
		key->value = quaternion;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddColliderCenterKey(float timestamp, Vector2 vector2)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::CdCenter);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector2Key* key = new Vector2Key();
		key->timestamp = timestamp;
		key->value = vector2;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddColliderSizeKey(float timestamp, Vector2 vector2)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::CdSize);
		if (timestamp > mDuration)
			mDuration = timestamp;
		Vector2Key* key = new Vector2Key();
		key->timestamp = timestamp;
		key->value = vector2;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddColliderActiveKey(float timestamp, bool active)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::CdActive);
		if (timestamp > mDuration)
			mDuration = timestamp;
		BoolKey* key = new BoolKey();
		key->timestamp = timestamp;
		key->value = active;
		timeline->keyframes.push_back(key);
	}
	
	void Animation::AddTextureKey(float timestamp, std::shared_ptr<graphics::Texture> texture)
	{		
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrTexture);
		if (timestamp > mDuration)
			mDuration = timestamp;
		TextureKey* key = new TextureKey();
		key->timestamp = timestamp;
		key->value = texture;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddColorKey(float timestamp, Color color)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrColor);
		if (timestamp > mDuration)
			mDuration = timestamp;
		ColorKey* key = new ColorKey();
		key->timestamp = timestamp;
		key->value = color;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddInterpolationKey(float timestamp, float interpolation)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrInterpolation);
		if (timestamp > mDuration)
			mDuration = timestamp;
		FloatKey* key = new FloatKey();
		key->timestamp = timestamp;
		key->value = interpolation;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddTintKey(float timestamp, Color color)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrTint);
		if (timestamp > mDuration)
			mDuration = timestamp;
		ColorKey* key = new ColorKey();
		key->timestamp = timestamp;
		key->value = color;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddRendererActiveKey(float timestamp, bool active)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::MrActive);
		if (timestamp > mDuration)
			mDuration = timestamp;
		BoolKey* key = new BoolKey();
		key->timestamp = timestamp;
		key->value = active;
		timeline->keyframes.push_back(key);
	}
	void Animation::AddFunctionKey(float timestamp, std::function<void()> function)
	{
		Timeline* timeline = GetTimlineOfType(eAnimationType::ScFunc);
		if (timestamp > mDuration)
			mDuration = timestamp;
		FuncKey* key = new FuncKey();
		key->timestamp = timestamp;
		key->value = function;
		timeline->keyframes.push_back(key);

	}

	Animation::Timeline* Animation::GetTimlineOfType(eAnimationType type)
	{
		if (mTimelines[(UINT)type] == nullptr)
			mTimelines[(UINT)type] = new Timeline();

		return mTimelines[(UINT)type];
	}
	void Animation::AnimTrPos(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mTr->SetPosition(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetPosition(pos);
		}
	}
	void Animation::AnimTrScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mTr->SetScale(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetScale(pos);
		}
	}
	void Animation::AnimTrRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			QuaternionKey* keyframe = dynamic_cast<QuaternionKey*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mTr->SetRotation(keyframe->value);
			assert(keyframe->value == Quaternion::Identity);
		}
		else
		{
			QuaternionKey* prev = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex - 1]);
			QuaternionKey* next = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->value, next->value, t);
			mTr->SetRotation(rot);
		}
	}
	void Animation::AnimTrLocPos(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalPosition(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetLocalPosition(pos);
		}
	}
	void Animation::AnimTrLocScale(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector3Key* keyframe = dynamic_cast<Vector3Key*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalScale(keyframe->value);
		}
		else
		{
			Vector3Key* prev = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector3Key* next = dynamic_cast<Vector3Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector3 pos = Vector3::Lerp(prev->value, next->value, t);
			mTr->SetLocalScale(pos);
		}
	}
	void Animation::AnimTrLocRot(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			QuaternionKey* keyframe = dynamic_cast<QuaternionKey*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mTr->SetLocalRotation(keyframe->value);
		}
		else
		{

			QuaternionKey* prev = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex - 1]);
			QuaternionKey* next = dynamic_cast<QuaternionKey*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Quaternion rot = Quaternion::Lerp(prev->value, next->value, t);
			mTr->SetLocalRotation(rot);
		}
	}
	void Animation::AnimCdCenter(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector2Key* keyframe = dynamic_cast<Vector2Key*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mCd->SetCenter(keyframe->value);
		}
		else
		{
			Vector2Key* prev = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector2Key* next = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->value, next->value, t);
			mCd->SetCenter(pos);
		}
	}
	void Animation::AnimCdSize(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			Vector2Key* keyframe = dynamic_cast<Vector2Key*>(timeline->keyframes[0]);
			if (keyframe->timestamp >= mTime)
				mCd->SetSize(keyframe->value);
		}
		else
		{
			Vector2Key* prev = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex - 1]);
			Vector2Key* next = dynamic_cast<Vector2Key*>(timeline->keyframes[timeline->currIndex]);
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			Vector2 pos = Vector2::Lerp(prev->value, next->value, t);
			mCd->SetSize(pos);
		}
	}
	void Animation::AnimCdActive(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			BoolKey* keyframe = dynamic_cast<BoolKey*>(timeline->keyframes[timeline->currIndex]);
			if (mTime >= keyframe->timestamp)
			{
				mCd->SetActive(keyframe->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrText(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			TextureKey* textureKey = dynamic_cast<TextureKey*>(timeline->keyframes[timeline->currIndex]);
			if (mTime >= textureKey->timestamp)
			{
				mMr->GetMaterial()->SetTexture(textureKey->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrColor(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			ColorKey* keyframe = (ColorKey*) & timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				mMr->SetColor(keyframe->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimMrColorpolation(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			FloatKey* keyframe = (FloatKey*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mMr->SetInterpolation(keyframe->value);
		}
		else
		{
			FloatKey* prev = (FloatKey*) & timeline->keyframes[timeline->currIndex - 1];
			FloatKey* next = (FloatKey*) & timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->SetInterpolation(prev->value + t*(next->value - prev->value));
		}
	}
	void Animation::AnimMrTint(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime) timeline->currIndex++;
		if (timeline->IsComplete())return;
		if (timeline->currIndex == 0)
		{
			ColorKey* keyframe = (ColorKey*) & timeline->keyframes[0];
			if (keyframe->timestamp >= mTime)
				mMr->GetMaterial()->SetTint(keyframe->value);
		}
		else
		{
			ColorKey* prev = (ColorKey*)&timeline->keyframes[timeline->currIndex - 1];
			ColorKey* next = (ColorKey*)&timeline->keyframes[timeline->currIndex];
			float t = (mTime - prev->timestamp) / (next->timestamp - prev->timestamp);
			mMr->GetMaterial()->SetTint(Color::Lerp(prev->value, next->value, t));
		}
	}
	void Animation::AnimMrActive(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			BoolKey* keyframe = dynamic_cast<BoolKey*>(timeline->keyframes[timeline->currIndex]);
			if (mTime >= keyframe->timestamp)
			{
				mMr->SetActive(keyframe->value);
				timeline->currIndex++;
			}
		}
	}
	void Animation::AnimScFunc(Timeline* timeline)
	{
		if (timeline->keyframes[timeline->currIndex]->timestamp < mTime)
		{
			FuncKey* keyframe = (FuncKey*) & timeline->keyframes[timeline->currIndex];
			if (mTime >= keyframe->timestamp)
			{
				keyframe->value();
				timeline->currIndex++;
			}
		}
	}
	void Animation::SetAnimationFunctions()
	{
		mAnimFunctions = std::vector<std::function<void(Timeline * timeline)>>((UINT)eAnimationType::End);
		mAnimFunctions[(UINT)eAnimationType::TrPosition] = ([this](Timeline* timeline) { this->AnimTrPos(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrScale] = ([this](Timeline* timeline) { this->AnimTrScale(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrRotation] = ([this](Timeline* timeline) { this->AnimTrRot(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrLocalPosition] = ([this](Timeline* timeline) { this->AnimTrLocPos(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrLocalScale] = ([this](Timeline* timeline) { this->AnimTrLocScale(timeline); });
		mAnimFunctions[(UINT)eAnimationType::TrLocalRotation] = ([this](Timeline* timeline) { this->AnimTrLocRot(timeline); });
		mAnimFunctions[(UINT)eAnimationType::CdCenter] = ([this](Timeline* timeline) { this->AnimCdCenter(timeline); });
		mAnimFunctions[(UINT)eAnimationType::CdSize] = ([this](Timeline* timeline) { this->AnimCdSize(timeline); });
		mAnimFunctions[(UINT)eAnimationType::CdActive] = ([this](Timeline* timeline) { this->AnimCdActive(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrTexture] = ([this](Timeline* timeline) { this->AnimMrText(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrColor] = ([this](Timeline* timeline) { this->AnimMrColor(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrInterpolation] = ([this](Timeline* timeline) { this->AnimMrColorpolation(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrTint] = ([this](Timeline* timeline) { this->AnimMrTint(timeline); });
		mAnimFunctions[(UINT)eAnimationType::MrActive] = ([this](Timeline* timeline) { this->AnimMrActive(timeline); });
		mAnimFunctions[(UINT)eAnimationType::ScFunc] = ([this](Timeline* timeline) { this->AnimScFunc(timeline); });
	}
}