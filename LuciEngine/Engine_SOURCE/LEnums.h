#pragma once
namespace lu::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Collider2D,
		MeshRenderer,
		Mesh,
		Animator,
		Particle,
		Camera,
		Script,
		End
	};

	enum class eLayerType
	{
		Player,
		Bullet,
		UI,
		Camera,
		End 
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		ComputeShader,
		Material,
		Mesh,
		Animation,
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