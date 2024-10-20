#include "StartScene.h"

// Basic
#include "GameObject.h"
#include "Transform.h"

// Camera
#include "Camera.h"
#include "CameraScript.h"

// Graphics
#include "../GraphicsEngine/GraphicsEngine.h"
#include "UI.h"
#include "ImageRenderer.h"
#include "Image.h"
#include "Animator.h"
#include "Panel.h"
#include "Button.h"

// Manager
#include "EventManager.h"
#include "ResourceManager.h"
#include "GameplayStatics.h"

// Sound
#include "SoundManager.h"
#include "Sound.h"

#include "StartSceneScript.h"

void StartScene::Enter()
{
	/// BGM
	SoundManager::GetInstance()->StopSoundBGM();
	SoundManager::GetInstance()->PlaySoundBGM(
		ResourceManager::GetInstance()->LoadResource<Sound>(L"StartBGM", L"/Sound/BGM/ETC/Casual game track.mp3")->GetSound());
	SoundManager::GetInstance()->SetBGMVolume(0.2f);
	SoundManager::GetInstance()->SetSFXVolume(0.5f);

	/// Title Image ----------------------------------------------------------

	// Object, Set Position & Size
	GameObject* titleObject = new GameObject("Title", OBJECT_TYPE::UI);
	titleObject->GetTransform()->SetLocalPosition(Vector2{ 960.f,540.f });
	titleObject->GetTransform()->SetSize(Vector2{ 1920, 1080 });

	// Component
	UI* titlePanel = new Panel();
	titleObject->AddComponent(titlePanel);
	Animator* titleAnimator = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"TitleImage", L"/Image/Animation/title/title_1.png")->GetImage());
	titleAnimator->CreateAnimation(L"title", Vector2(0, 0), Vector2(1920, 1080), Vector2(0, 0), Vector2(1920, 0), 0.2f, 4);
	titleAnimator->Play(L"title", true);
	titleObject->AddComponent(titleAnimator);

	// Add Object
	AddGameObject(titleObject);

	/// Start Button ---------------------------------------------------------

	// Object, Set Position & Size
	GameObject* startButtonObject = new GameObject("Title", OBJECT_TYPE::UI);
	startButtonObject->GetTransform()->SetLocalPosition(Vector2{ 1575.f,870.f });
	startButtonObject->GetTransform()->SetSize(Vector2{ 370.f, 101.f});

	// Button Image
	ImageRenderer* startButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"StartButtonFocus", L"/Image/UI/startButtonFocus.png")->GetImage());
	startButtonObject->AddComponent(startButtonImage);

	// Add Object
	AddGameObject(startButtonObject);

	/// Close Button ---------------------------------------------------------

	// Object, Set Position & Size
	GameObject* closeButtonObject = new GameObject("Title", OBJECT_TYPE::UI);
	closeButtonObject->GetTransform()->SetLocalPosition(Vector2{ 1575.f,990.f });
	closeButtonObject->GetTransform()->SetSize(Vector2{ 370.f, 101.f });

	// Button Image
	ImageRenderer* closeButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"CloseButton", L"/Image/UI/closeButton.png")->GetImage());
	closeButtonObject->AddComponent(closeButtonImage);

	// Add Object
	AddGameObject(closeButtonObject);

	/// Start Scene Script ---------------------------------------------------

	// Object
	GameObject* startSceneObject = new GameObject("startSceneObject", OBJECT_TYPE::DEFAULT);

	// Component
	StartSceneScript* startSceneScript = new StartSceneScript();
	startSceneScript->m_StartButtonImage = startButtonImage;
	startSceneScript->m_CloseButtonImage = closeButtonImage;
	startSceneObject->AddComponent(startSceneScript);

	// Add Object
	AddGameObject(startSceneObject);

	/// Button CallBack ------------------------------------------------------

	// Start Button Callback
	UI* startButtonUI = new Button([startSceneScript](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::HOVER) {
			startSceneScript->SetFocus(BUTTON_FOCUS::START);

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::CLICK) {
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			SoundManager::GetInstance()->StopSoundBGM();

			GameplayStatics::LoadScene("OpeningScene");
		}
		});
	startButtonObject->AddComponent(startButtonUI);

	// Close Button Callback
	UI* closeButtonUI = new Button([startSceneScript](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::HOVER) {
			startSceneScript->SetFocus(BUTTON_FOCUS::CLOSE);

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::CLICK) {
			DestroyWindow(GetFocus());

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
		}
		});
	closeButtonObject->AddComponent(closeButtonUI);

	/// Ending Button ---------------------------------------------------------

	// Object, Set Position & Size
	GameObject* endingCreditButton = new GameObject("EndingButton", OBJECT_TYPE::UI);
	endingCreditButton->GetTransform()->SetLocalPosition(Vector2{ 100.f,1000.f });
	endingCreditButton->GetTransform()->SetSize(Vector2{ 115.f, 100.f });

	// Button Image
	ImageRenderer* endingCreditButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"CreditButton", L"/EndingCredit/creditButton.png")->GetImage());
	endingCreditButton->AddComponent(endingCreditButtonImage);

	// Ending Credit Button Callback
	UI* endingCreditButtonUI = new Button([endingCreditButtonImage](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			endingCreditButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"CreditButton", L"/EndingCredit/creditButton.png")->GetImage());
		}
		if (event == BUTTON_EVENT::HOVER) {
			endingCreditButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"CreditButtonFocus", L"/EndingCredit/creditButtonFocus.png")->GetImage());

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			endingCreditButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"CreditButtonClick", L"/EndingCredit/creditButtonClick.png")->GetImage());
		}
		if (event == BUTTON_EVENT::CLICK) {
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			
			GameplayStatics::LoadScene("EndingCredit");
		}
		});
	endingCreditButton->AddComponent(endingCreditButtonUI);

	// Add Object
	AddGameObject(endingCreditButton);

}