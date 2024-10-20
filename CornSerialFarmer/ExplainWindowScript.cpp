#include "ExplainWindowScript.h"

#include "EventManager.h"
#include "TextRenderer.h"
#include "ImageRenderer.h"

ExplainWindowScript::ExplainWindowScript()
	: MonoBehaviour(typeid(this).name())
	, m_Text(nullptr)
	, m_TextBox(nullptr)
	, m_TextData()
{

}

ExplainWindowScript::~ExplainWindowScript()
{
	
}

void ExplainWindowScript::Start()
{
	m_Text->SetText(L"");
	m_TextBox->SetIsActivate(false);

	EventManager::GetInstance()->RegisterClient("ShowExplainWindow", MakeCallInfo(&ExplainWindowScript::SetText));
}

void ExplainWindowScript::SetText(std::any text)
{
	m_TextData = std::any_cast<std::wstring>(text);

	if (m_TextData == L"")
	{
		m_Text->SetText(m_TextData);
		m_TextBox->SetIsActivate(false);
	}
	else
	{
		m_Text->SetText(m_TextData);
		m_TextBox->SetIsActivate(true);
	}
}
