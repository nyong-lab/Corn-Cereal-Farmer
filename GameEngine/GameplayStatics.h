#pragma once

namespace GameplayStatics
{
	void LoadScene(string sceneName);
	void CreateObject(GameObject* gameObject);
	void DestroyObject(GameObject* gameObject);
	void PauseGame();
	void ResumeGame();
	void SetTimeScale(float timeScale);
};

