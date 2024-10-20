#pragma once

#include "Define.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

class GameObject;

class Scene
{
public:
	/// constructor need name
	Scene();
	Scene(string name);
	~Scene();

public:
	virtual void Enter() abstract;
	virtual void Exit();
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float deltaTime);
	virtual void Render();
	virtual void DebugRender();

	bool IsPause() { return m_IsPaused; }
	void Pause() { m_IsPaused = true; }
	void Resume() { m_IsPaused = false; }

public:
	void AddGameObject(GameObject* object);
	void RemoveGameObject(GameObject* object);
	vector<GameObject*>& GetGameObjects() { return m_GameObjects; }
// 	const vector<GameObject*>& GetGameObject(OBJECT_TYPE objType) { return m_GameObjects[(int)objType]; }
// 	vector<GameObject*>& GetUIObject() { return m_GameObjects[(int)OBJECT_TYPE::UI]; };

	string GetName() const { return m_Name; }


private:
	string m_Name;

	bool m_IsPaused = false;

	/// GameObject vector
	vector<GameObject*> m_GameObjects;
};