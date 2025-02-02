#pragma once
namespace lu::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Rigidbody,
		Collider2D,
		MeshRenderer,
		Mesh,
		Animator,
		Particle,
		Camera,
		AudioListener,
		AudioSource,
		Text,
		Script,
		End
	};

	enum class eLayerType
	{
		Player,
		Bullet,
		BulletInteractor,
		Item,
		UI,
		System,
		Camera,
		End 
	};
	enum class eTagType
	{
		Player,
		Bullet,
		Item,
		None
	};
	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
		End
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End
	};

}