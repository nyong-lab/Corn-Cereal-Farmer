#include "PauseWindow.h"
#include "Define.h"
#include "GameplayStatics.h"

#include "Transform.h"

#include "ResourceManager.h"
#include "Image.h"

#include "UI.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "Panel.h"
#include "Button.h"

#include "SoundManager.h"
#include "Sound.h"

#include "EventManager.h"

PauseWindow::PauseWindow()
	: GameObject("PauseWindow", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(960.f, 540.f));
	GetTransform()->SetSize(Vector2(738.f, 492.f));

	// Base UI
	UI* pauseWindowUI = new Panel();
	AddComponent(pauseWindowUI);

	// Base Image
	ImageRenderer* pauseWindowImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"PauseWindowImage", L"/Image/UI/pause_popup/pauseWindow.png")->GetImage(),
		{},
		{},
		GetTransform()->GetSize());
	AddComponent(pauseWindowImage);

	/// BUTTON -----------------------------------------------------------

	/// RESTART

	// Set Position & Size
	GameObject* restartButton = new GameObject("GamePauseRestartButton", OBJECT_TYPE::UI);
	restartButton->GetTransform()->SetLocalPosition(Vector2(0.f, -80.f));
	restartButton->GetTransform()->SetSize(Vector2(312.f, 100.f));

	// Button Image
	ImageRenderer* restartButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseRestartButton", L"/Image/UI/pause_popup/restartButton.png")->GetImage());
	restartButton->AddComponent(restartButtonImage);

	// Button Callback
	UI* restartButtonUI = new Button([restartButtonImage](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseRestartButton", L"/Image/UI/pause_popup/restartButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			// Image
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseRestartButtonClick", L"/Image/UI/pause_popup/restartButtonClick.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseRestartButtonClick", L"/Image/UI/pause_popup/restartButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseRestartButton", L"/Image/UI/pause_popup/restartButton.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			// Load Scene
			GameplayStatics::LoadScene("MainScene");
		}
		});
	restartButton->AddComponent(restartButtonUI);

	// Add Child
	AddObjectChild(restartButton);

	/// EXIT

	// Set Position & Size
	GameObject* exitButton = new GameObject("ExitButton", OBJECT_TYPE::UI);
	exitButton->GetTransform()->SetLocalPosition(Vector2(0.f, 30.f));
	exitButton->GetTransform()->SetSize(Vector2(312.f, 100.f));

	// Button Image
	ImageRenderer* exitButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseExitButton", L"/Image/UI/pause_popup/exitButton.png")->GetImage());
	exitButton->AddComponent(exitButtonImage);

	// Button Callback
	UI* exitButtonUI = new Button([exitButtonImage](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseExitButton", L"/Image/UI/pause_popup/exitButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			//Image
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseExitButtonClick", L"/Image/UI/pause_popup/exitButtonClick.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseExitButtonClick", L"/Image/UI/pause_popup/exitButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GamePauseExitButton", L"/Image/UI/pause_popup/exitButton.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			// Load Scene
			GameplayStatics::LoadScene("StartScene");
		}
		});
	exitButton->AddComponent(exitButtonUI);

	// Add Child
	AddObjectChild(exitButton);

	/// SOUND

	// Set Position & Size
	GameObject* soundButton = new GameObject("SoundButton", OBJECT_TYPE::UI);
	soundButton->GetTransform()->SetLocalPosition(Vector2(0.f, 140.f));
	soundButton->GetTransform()->SetSize(Vector2(312.f, 100.f));

	// Button Image
	ImageRenderer* soundButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"SoundButton", L"/Image/UI/pause_popup/soundButton.png")->GetImage());
	soundButton->AddComponent(soundButtonImage);

	// Button Callback
	UI* soundButtonUI = new Button([soundButtonImage, this](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			soundButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SoundButton", L"/Image/UI/pause_popup/soundButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			// Image
			soundButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SoundButtonClick", L"/Image/UI/pause_popup/soundButtonClick.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			soundButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SoundButtonClick", L"/Image/UI/pause_popup/soundButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			soundButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"SoundButton", L"/Image/UI/pause_popup/soundButton.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());

			if (SoundManager::GetInstance()->GetIsMute()) 
				SoundManager::GetInstance()->MuteOff();
			else SoundManager::GetInstance()->MuteOn();
		}
		});
	soundButton->AddComponent(soundButtonUI);

	// Add Child
	AddObjectChild(soundButton);

	/// CONTINUE

	// Set Position & Size
	GameObject* continueButton = new GameObject("ContinueButton", OBJECT_TYPE::UI);
	continueButton->GetTransform()->SetLocalPosition(Vector2(298.f, -165.f));
	continueButton->GetTransform()->SetSize(Vector2(104.f, 112.f));

	// Button Image
	ImageRenderer* continueButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ContinueButton", L"/Image/UI/pause_popup/continueButton.png")->GetImage());
	continueButton->AddComponent(continueButtonImage);

	// Button Callback
	UI* continueButtonUI = new Button([continueButtonImage, this](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			continueButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"ContinueButton", L"/Image/UI/pause_popup/continueButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			// Image
			continueButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"ContinueButtonClick", L"/Image/UI/pause_popup/continueButtonClick.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			continueButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"ContinueButtonClick", L"/Image/UI/pause_popup/continueButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			continueButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"ContinueButton", L"/Image/UI/pause_popup/continueButton.png")->GetImage()
			);
			
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			
			// Close pause window
			GameplayStatics::DestroyObject(this);
			GameplayStatics::DestroyObject(m_Background);
			EventManager::GetInstance()->SendEvent("ResumeGame", nullptr);

			GameplayStatics::ResumeGame();
		}
		});
	continueButton->AddComponent(continueButtonUI);

	// Add Child
	AddObjectChild(continueButton);



	
}

PauseWindow::~PauseWindow()
{

}
