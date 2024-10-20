#include "pch.h"

#include "SceneManager.h"
#include "Scene.h"

#include "UIManager.h"
#include "UI.h"

#include "GameObject.h"
#include "Input.h"

UIManager::UIManager()
	: m_FocusedUI(nullptr)
	, m_SceneManager(nullptr)
{

}

UIManager::~UIManager()
{

}

void UIManager::Initialize(SceneManager* sceneManager)
{
	m_SceneManager = sceneManager;
}

void UIManager::Update()
{
	// 포커스된 UI 찾기
	m_FocusedUI = FindFocusedUI();
	if (!m_FocusedUI) return;

	// FocusedUI 내에서 부모, 자식 UI들 중 실제 타겟팅 된 UI를 가져온다
	UI* targetUI = FindTargetedUI(m_FocusedUI);

	bool leftButtonTap = Input::GetKeyDown(KEY::LBTN);
	bool leftButtonAway = Input::GetKeyUp(KEY::LBTN);

	if (targetUI != nullptr)
	{
		targetUI->MouseOn();

		if (leftButtonTap)
		{
			targetUI->m_LeftButtonDown = true;
			targetUI->MouseLeftButtonDown();
		}
		else if (leftButtonAway)
		{
			if (targetUI->m_LeftButtonDown)
				targetUI->MouseLeftButtonClick();
			targetUI->m_LeftButtonDown = false;
		}
	}
	
}

void UIManager::SetFocusedUI(UI* ui)
{
	// 이미 포커싱중인 경우 or 포커싱 해제요청인 경우
	if (m_FocusedUI == ui || ui == nullptr)
	{
		m_FocusedUI = ui;
		return;
	}

	m_FocusedUI = ui;

	// 현재 씬에서 UI 가져오기
	vector<GameObject*>& UIVector = m_SceneManager->GetCurrentScene()->GetGameObjects();
	vector<GameObject*>::iterator iter = UIVector.begin();
	for (; iter != UIVector.end(); ++iter)
	{
		
		if (m_FocusedUI == (*iter)->GetComponent<UI>())
			break;
	}

	UIVector.erase(iter);
	UIVector.push_back((GameObject*)m_FocusedUI);
}

#include <iostream>
UI* UIManager::FindFocusedUI()
{
	// 현재 씬에서 UI 가져오기
	vector<GameObject*>& UIVector = m_SceneManager->GetCurrentScene()->GetGameObjects();

	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다
	UI* focusedUI = m_FocusedUI;

	// 마우스가 UI 범위 내에 있을 때
	vector<GameObject*>::iterator target = UIVector.end();
	vector<GameObject*>::iterator iter = UIVector.begin();
	for (; iter != UIVector.end(); ++iter)
	{
		if((*iter)->GetComponent<UI>())
		{
			if ((*iter)->GetComponent<UI>()->GetMouseOn())
			{
				// Focused UI 변경
				target = iter;
			}
		}
	}

	// Focus된 UI가 없을 경우
	if (UIVector.end() == target)
	{
		return nullptr;
	}

	focusedUI = (*target)->GetComponent<UI>();

	// 벡터 내에서 맨 뒤로 순번 교체
// 	UIVector.erase(target);
// 	UIVector.push_back(focusedUI->GetGameObject());

	return focusedUI;
}

UI* UIManager::FindTargetedUI(UI* parentUI)
{
	UI* targetUI = nullptr;

	// 부모 UI 포함, 모든 자식들을 검사한다
	static list<UI*> queue;
	static vector<UI*> noneTargets;

	queue.clear();
	noneTargets.clear();

	if(parentUI != nullptr) queue.push_back(parentUI);
	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		UI* ui = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI인지 확인
		// Target UI들 중, 제일 낮은 계층의 자식 UI 반환
		if (ui->GetMouseOn())
		{
			if (targetUI != nullptr)
			{
				noneTargets.push_back(targetUI);
			}
			targetUI = ui;
		}
		else
		{
			noneTargets.push_back(ui);
		}

		// 큐에 자식 UI 추가
		// TODO : 이거 밑줄 어떻게 지우지
		GameObject* OwnerObejct = ui->GetGameObject();
		vector<GameObject*>& childVector = OwnerObejct->GetObjectChildren();

		for (auto& child : childVector)
		{
			UI* childUI = child->GetComponent<UI>();
			if (childUI != nullptr) {
				queue.push_back(childUI);
			}
		}
	}

	if (Input::GetKeyUp(KEY::LBTN))
	{
		for (auto& noneTarget : noneTargets)
		{
			noneTarget->m_LeftButtonDown = false;
		}
	}

	return targetUI;
}
