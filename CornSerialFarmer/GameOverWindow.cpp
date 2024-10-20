#include "GameOverWindow.h"
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

GameOverWindow::GameOverWindow()
	: GameObject("GameOverWindow", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(960.f, 540.f));
	GetTransform()->SetSize(Vector2(861.f, 574.f));

	// Base UI
	UI* gameoverWindowUI = new Panel();
	AddComponent(gameoverWindowUI);

	// Base Image
	ImageRenderer* gameoverWindowImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverWindowImage", L"/Image/UI/game_popup/gameoverWindow.png")->GetImage());
	AddComponent(gameoverWindowImage);

	/// BUTTON -----------------------------------------------------------

	/// RESTART

	// Set Position & Size
	GameObject* restartButton = new GameObject("GameOverRestartButton", OBJECT_TYPE::UI);
	restartButton->GetTransform()->SetLocalPosition(Vector2(0.f, -60.f));
	restartButton->GetTransform()->SetSize(Vector2(364.f, 119.f));

	// Button Image
	ImageRenderer* restartButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverRestartButton", L"/Image/UI/game_popup/restartButton.png")->GetImage());
	restartButton->AddComponent(restartButtonImage);

	// Button Callback
	UI* restartButtonUI = new Button([restartButtonImage](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverRestartButton", L"/Image/UI/game_popup/restartButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			// Image
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverRestartButtonClick", L"/Image/UI/game_popup/restartButtonClick.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"RestartButtonClick", L"/Image/UI/game_popup/restartButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			restartButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverRestartButton", L"/Image/UI/game_popup/restartButton.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			SoundManager::GetInstance()->StopSoundBGM();
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
	exitButton->GetTransform()->SetLocalPosition(Vector2(0.f, 90.f));
	exitButton->GetTransform()->SetSize(Vector2(364.f, 119.f));

	// Button Image
	ImageRenderer* exitButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverExitButton", L"/Image/UI/game_popup/exitButton.png")->GetImage());
	exitButton->AddComponent(exitButtonImage);

	// Button Callback
	UI* exitButtonUI = new Button([exitButtonImage](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverExitButton", L"/Image/UI/game_popup/exitButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			//Image
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverExitButtonClick", L"/Image/UI/game_popup/exitButtonClick.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverExitButtonClick", L"/Image/UI/game_popup/exitButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			exitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"GameOverExitButton", L"/Image/UI/game_popup/exitButton.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			SoundManager::GetInstance()->StopSoundBGM();
			// Load Scene
			GameplayStatics::LoadScene("StartScene");
		}
		});
	exitButton->AddComponent(exitButtonUI);

	// Add Child
	AddObjectChild(exitButton);
}

GameOverWindow::~GameOverWindow()
{

}
