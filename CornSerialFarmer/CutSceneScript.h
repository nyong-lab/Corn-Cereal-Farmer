#pragma once
#include "MonoBehaviour.h"
#include <string>
class ImageRenderer;
class TextRenderer;
class Image;

class CutSceneScript :
    public MonoBehaviour
{
public:
	CutSceneScript();
	~CutSceneScript();

public:
	virtual void Start() override;
	void BtnCallBack();
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:
	int m_Index = 0;
	std::vector<std::wstring> m_Text;
	std::vector<Image*> m_CutSceneImage;
	float m_StringSize = 0.f;
	TextRenderer* m_TextRenderer = nullptr;
	ImageRenderer* m_ImageRenderer = nullptr;
	ImageRenderer* m_SpaceRenderer = nullptr;
	bool m_IsPlaying = false;

	std::string m_NextSceneName;

	bool m_IsButtonHandled = false;

	float m_ElipseTime = 0.f;
};

