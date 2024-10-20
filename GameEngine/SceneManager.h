/// 
/// 2023.08.01 
/// 작성자 : 정창도
/// 신매니저를 만들어보자
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