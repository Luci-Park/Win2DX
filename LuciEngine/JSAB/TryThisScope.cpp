#include "TryThisScope.h"
#include "LTime.h"
namespace lu::JSAB
{
	void TryThisScope::Update()
	{
		Bullet::Update();
	}
	void TryThisScope::BulletSetUp()
	{
		mTransform->SetScale(2000, 2000, 1);
		mRotateSpeed = -.1f;

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"TTScopeMesh", L"TT_Scope"));
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);

		mHole = object::Instantiate<GameObject>({0, 0, -1}, mTransform, eLayerType::Bullet)->mTransform;
		auto mr = mHole->Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"TTHole", L"TT_RedCircle"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);
		mr->SetColor(Color::black)->UseColor(true);

		mHoleAnim = mHole->Owner()->AddComponent<Animator>();
		auto ani = mHoleAnim->CreateAnimation(L"Shrink");
		ani->AddLocalScaleKey(0, { 1, 1, 1 });
		ani->AddLocalScaleKey(5, { 0, 0, 1 });
	}
	void TryThisScope::OnWarning()
	{
	}
	void TryThisScope::WhileWarning(double time)
	{
	}
	void TryThisScope::OnActivate()
	{
		mMr->SetActive(true);
		mHole->Owner()->SetActive(true);
		mHoleAnim->PlayAnimation(L"Shrink", false);
	}
	void TryThisScope::WhileActivate(double time)
	{
		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotateSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);
	}
	void TryThisScope::OnOutro()
	{
		DeActivate();
	}
	void TryThisScope::WhileOutro(double time)
	{
	}
	void TryThisScope::OnDeActivate()
	{
		mHole->Owner()->SetActive(false);
		mMr->SetActive(false);
		mTransform->SetScale(2000, 2000, 1);
	}
}