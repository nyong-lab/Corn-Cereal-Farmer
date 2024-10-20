/// 
/// 2023.08.01 
/// �ۼ��� : ��â��
/// �ŸŴ����� ������
/// 

#pragma once
#include <unordered_map>
#include <string>
using std::string;
class Scene;

class SceneManager
{

public:
	SceneManager();
	~SceneManager();

public:
	void Initialize();
	void Finalize();

	void Start();
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render();
	void DebugRender();

public:
	void LoadScene(const string& sceneName);
	void SetStartScene(const string& sceneName);
	Scene* GetCurrentScene() const { return m_CurrentScene; }
	void AddScene(Scene* scene);

private:
	std::unordered_map<string, Scene*> m_Scenes;

	Scene* m_CurrentScene;

};