#pragma once
#include "LResource.h"
#include "LTexture.h"
namespace lu
{
	using namespace lu::math;
	class GameObject;
	class Transform;
	class Collider2D;
	class Animator;
	class MeshRenderer;
	class Animation : public Resource
	{
	public:

		enum class eAnimationType
		{
			TrPosition, TrScale, TrRotation, TrLocalPosition, TrLocalScale, TrLocalRotation,
			CdCenter, CdSize, CdActive,
			MrTexture, MrColor, MrInterpolation, MrTint, MrActive,
			ScFunc,
			End
		};
		struct KeyFrame
		{
			KeyFrame(){}
			virtual ~KeyFrame() {}
			float timestamp;
			eAnimationType type;
			bool operator<(const KeyFrame& other) const
			{
				return timestamp < other.timestamp;
			}

		};
		struct FuncKey : KeyFrame
		{
			FuncKey():value(nullptr){}
			std::function<void()>value;
		};
		struct TextureKey : KeyFrame
		{
			TextureKey():value(nullptr){}
			std::shared_ptr<graphics::Texture> value;

			TextureKey& operator=(const TextureKey& other) {
				value = other.value;
			}
		};
		struct ColorKey : KeyFrame
		{
			Color value;
		};
		struct QuaternionKey : KeyFrame
		{
			Quaternion value;
		};
		struct Vector3Key : KeyFrame
		{
			Vector3 value;
		};
		struct Vector2Key : KeyFrame
		{
			Vector2 value;
		};
		struct FloatKey : KeyFrame { float value; };
		struct BoolKey : KeyFrame { bool value; };

		struct Timeline
		{
			int currIndex = 0;
			std::vector<KeyFrame> keyframes;
			bool IsComplete() { return currIndex >= keyframes.size(); }
			void Reset() { currIndex = 0; }
		};
	public:
		Animation(GameObject* owner);
		~Animation();
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }

		void Update();
		void LateUpdate();
		void Render();
		
		void Reset();
		bool IsComplete() { return mbComplete; }

		void AddKeyFrame(KeyFrame keyframe);
	private:
		void AnimTrPos(Timeline* timeline);
		void AnimTrScale(Timeline* timeline);
		void AnimTrRot(Timeline* timeline);
		void AnimTrLocPos(Timeline* timeline);
		void AnimTrLocScale(Timeline* timeline);
		void AnimTrLocRot(Timeline* timeline);
		void AnimCdCenter(Timeline* timeline);
		void AnimCdSize(Timeline* timeline);
		void AnimCdActive(Timeline* timeline);
		void AnimMrText(Timeline* timeline);
		void AnimMrColor(Timeline* timeline);
		void AnimMrColorpolation(Timeline* timeline);
		void AnimMrTint(Timeline* timeline);
		void AnimMrActive(Timeline* timeline);
		void AnimScFunc(Timeline* timeline);
		void SetAnimationFunctions();
	private:
		float mTime;
		float mDuration;
		bool mbComplete;
		std::vector<Timeline*> mTimelines;
		std::vector<std::function<void(Timeline* timeline)>> mAnimFunctions;
		Animator* mAni;
		Transform* mTr;
		Collider2D* mCd;
		MeshRenderer* mMr;


	};

}

