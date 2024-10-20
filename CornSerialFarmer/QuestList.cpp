#include "QuestList.h"
#include "Define.h"

#include "Transform.h"

#include "ResourceManager.h"
#include "Image.h"
#include "Font.h"

#include "UI.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "Panel.h"

QuestList::QuestList()
	: GameObject("QuestList", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(1724.f, 864.f));
	GetTransform()->SetSize(Vector2(392.f, 434.f));

	// Empty UI
	UI* questListBaseUI = new Panel();
	AddComponent(questListBaseUI);

	// Base Image
	ImageRenderer* questListBaseImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"QuestListBase", L"/UI/questBase.png")->GetImage());
	AddComponent(questListBaseImage);

	/// Quest List
	for (int questNum = 0; questNum < QUESTCOUNT; questNum++)
	{
		string questName = "questName" + to_string(questNum);
		m_Quest[questNum] = new GameObject(questName, OBJECT_TYPE::UI);

		AddObjectChild(m_Quest[questNum]);

		// Set Position & Size
		Transform* questTransform = m_Quest[questNum]->GetTransform();

		float listPosition = 0.f;
		switch (questNum) {
		case 0: listPosition = -119.f; break;
		case 1: listPosition = -56.f; break;
		case 2: listPosition = 7.f; break;
		case 3: listPosition = 70.f; break;
		default: break;
		}

		questTransform->SetLocalPosition(Vector2(-139.f, listPosition));
		questTransform->SetSize(Vector2(42.f, 42.f));

		// Empty UI
		UI* questListUI = new Panel();
		m_Quest[questNum]->AddComponent(questListUI);

		// Quest List Image
		m_CheckBoxImage[questNum] = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"noneCheck", L"/UI/nonecheck.png")->GetImage());
		m_Quest[questNum]->AddComponent(m_CheckBoxImage[questNum]);

		// Quest List Text 
		m_QuestText[questNum] = new TextRenderer(
			Vector2(-465.f, -20.f),
			L"绢录备 历录备 快快快旷 捞巴历巴 窍扁",
			ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_18", L"/Font/Galmuri9.ttf", L"Galmuri9", 18.f)->Getfont(),
			COLOR::QUESTLIST);
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_18")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_18")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_LEADING);
 		m_QuestText[questNum]->SetTextAlignLeft();
		m_Quest[questNum]->AddComponent(m_QuestText[questNum]);
	}
}

QuestList::~QuestList()
{

}
