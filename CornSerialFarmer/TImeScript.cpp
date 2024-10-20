#include "TImeScript.h"
#include "TextRenderer.h"
#include "Transform.h"

TImeScript::TImeScript() :
	MonoBehaviour(typeid(this).name()),
	m_DeltaTime(0.f),
	m_FPS(0.f),
	m_TextRenderer(nullptr)
{
}

TImeScript::~TImeScript()
{
}

void TImeScript::Start()
{
	GetTransform()->SetLocalPosition({ 200.f, 200.f });
}

void TImeScript::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
	m_FPS = 1.f / m_DeltaTime;

	std::wstring text;
	text += L"DT : ";
	text += to_wstring(m_DeltaTime);
	text += L"\nFPS : ";
	text += to_wstring(m_FPS);
	m_TextRenderer->SetText(text);
}

void TImeScript::FixedUpdate(float deltaTime)
{
}

void TImeScript::Finalize()
{
}
