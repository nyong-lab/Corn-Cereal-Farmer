/// [2023/8/9] 박연하
/// --------------------------
/// UI를 관리하는 매니저

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

