#include "StartSceneScript.h"
#include "Input.h"
#include "GameplayStatics.h"
#include "Image.h"
#include "ResourceManager.h"
#include "ImageRenderer.h"

// Sound
#include "SoundManager.h"
#include "Sound.h"

StartSceneScript::StartSceneScript()
	: MonoBehaviour(typeid(this).name())
	, m_FocusButton(BUTTON_FOCUS::START)
	, m_StartButtonImage(nullptr)
	, m_CloseButtonImage(nullptr)
{

}

StartSceneScript::~StartSceneScript()
{

}

void StartSceneScript::Start()
{

}

void StartSceneScript::Update(float deltaTime)
{
	FindButtonFocus();
	SetButtonImage();
}

void StartSceneScript::FindButtonFocus()
{
	if (Input::GetKeyDown(KEY::W) || Input::GetKeyDown(KEY::S))
	{
		if (m_FocusButton == BUTTON_FOCUS::START)
			m_FocusButton = BUTTON_FOCUS::CLOSE;
		else m_FocusButton = BUTTON_FOCUS::START;

		SoundManager::GetInstance()->PlaySoundSFX(
			ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
	}

	if (Input::GetKeyUp(KEY::SPACE))
	{
		if (m_FocusButton == BUTTON_FOCUS::START)
		{
			GameplayStatics::LoadScene("OpeningScene");
		}
		else DestroyWindow(GetFocus());

		SoundManager::GetInstance()->StopSoundBGM();
		SoundManager::GetInstance()->PlaySoundSFX(
			ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
	}
}

void StartSceneScript::SetButtonImage()
{
	if (m_FocusButton == BUTTON_FOCUS::START)
	{
		m_StartButtonImage->SetImage(
			ResourceManager::GetInstance()->LoadResource<Image>(L"StartButtonFocus", L"/Image/UI/startButtonFocus.png")->GetImage());

		m_CloseButtonImage->SetImage(
			ResourceManager::GetInstance()->LoadResource<Image>(L"CloseButton", L"/Image/UI/closeButton.png")->GetImage());
	}
	else
	{
		m_StartButtonImage->SetImage(
			ResourceManager::GetInstance()->LoadResource<Image>(L"StartButton", L"/Image/UI/startButton.png")->GetImage());

		m_CloseButtonImage->SetImage(
			ResourceManager::GetInstance()->LoadResource<Image>(L"CloseButtonFocus", L"/Image/UI/closeButtonFocus.png")->GetImage());
	}
}

