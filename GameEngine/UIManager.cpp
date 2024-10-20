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
	// ��Ŀ���� UI ã��
	m_FocusedUI = FindFocusedUI();
	if (!m_FocusedUI) return;

	// FocusedUI ������ �θ�, �ڽ� UI�� �� ���� Ÿ���� �� UI�� �����´�
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
	// �̹� ��Ŀ������ ��� or ��Ŀ�� ������û�� ���
	if (m_FocusedUI == ui || ui == nullptr)
	{
		m_FocusedUI = ui;
		return;
	}

	m_FocusedUI = ui;

	// ���� ������ UI ��������
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
	// ���� ������ UI ��������
	vector<GameObject*>& UIVector = m_SceneManager->GetCurrentScene()->GetGameObjects();

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�
	UI* focusedUI = m_FocusedUI;

	// ���콺�� UI ���� ���� ���� ��
	vector<GameObject*>::iterator target = UIVector.end();
	vector<GameObject*>::iterator iter = UIVector.begin();
	for (; iter != UIVector.end(); ++iter)
	{
		if((*iter)->GetComponent<UI>())
		{
			if ((*iter)->GetComponent<UI>()->GetMouseOn())
			{
				// Focused UI ����
				target = iter;
			}
		}
	}

	// Focus�� UI�� ���� ���
	if (UIVector.end() == target)
	{
		return nullptr;
	}

	focusedUI = (*target)->GetComponent<UI>();

	// ���� ������ �� �ڷ� ���� ��ü
// 	UIVector.erase(target);
// 	UIVector.push_back(focusedUI->GetGameObject());

	return focusedUI;
}

UI* UIManager::FindTargetedUI(UI* parentUI)
{
	UI* targetUI = nullptr;

	// �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�
	static list<UI*> queue;
	static vector<UI*> noneTargets;

	queue.clear();
	noneTargets.clear();

	if(parentUI != nullptr) queue.push_back(parentUI);
	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		UI* ui = queue.front();
		queue.pop_front();

		// ť���� ������ UI�� TargetUI���� Ȯ��
		// Target UI�� ��, ���� ���� ������ �ڽ� UI ��ȯ
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

		// ť�� �ڽ� UI �߰�
		// TODO : �̰� ���� ��� ������
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
