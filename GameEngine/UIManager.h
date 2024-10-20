/// [2023/8/9] �ڿ���
/// --------------------------
/// UI�� �����ϴ� �Ŵ���

#pragma once

class UI;
class SceneManager;

class UIManager
{
public:
	UIManager();
	~UIManager();

public:
	void Initialize(SceneManager* sceneManager);
	void Update();

public:
	void SetFocusedUI(UI* ui);
	UI* FindFocusedUI();
	UI* FindTargetedUI(UI* parentUI);

private:
	UI* m_FocusedUI;
	SceneManager* m_SceneManager;
};

