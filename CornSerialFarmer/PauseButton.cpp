#include "PauseButton.h"
#include "Define.h"
#include "GameplayStatics.h"

#include "Transform.h"

#include "ResourceManager.h"
#include "Image.h"

#include "UI.h"
#include "ImageRenderer.h"
#include "Button.h"
#include "Panel.h"

#include "PauseWindow.h"
#include "PopupWindowBackground.h"
#include "PauseButtonScript.h"

// Sound
#include "SoundManager.h"
#include "Sound.h"

#include "KillWindow.h"

PauseButton::PauseButton()
	: GameObject("PauseButton", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(1750.f, 120.f));
	GetTransform()->SetSize(Vector2(128.f, 128.f));

	// Script 
	PauseButtonScript* pauseButtonScript = new PauseButtonScript();
	AddComponent(pauseButtonScript);

	// Button Image
	ImageRenderer* pauseButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"PauseButton_defalut", L"/UI/pauseButton_default.png")->GetImage());
	AddComponent(pauseButtonImage);

	// Button Callback
	UI* pauseButtonUI = new Button([pauseButtonImage, pauseButtonScript](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			pauseButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"PauseButton_defalut", L"/UI/pauseButton_default.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			pauseButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"PauseButton_hover", L"/UI/pauseButton_hover.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			pauseButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"PauseButton_down", L"/UI/pauseButton_down.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			if(!pauseButtonScript->m_IsClicked )
			{
				PopupWindowBackground* popupBG = new PopupWindowBackground();
				GameplayStatics::CreateObject(popupBG);

				PauseWindow* pauseWindow = new PauseWindow();
				pauseWindow->m_Background = popupBG;
				GameplayStatics::CreateObject(pauseWindow);

				pauseButtonScript->m_IsClicked = true;

				GameplayStatics::PauseGame();
			}

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			
		}
		});
	AddComponent(pauseButtonUI);

}

PauseButton::~PauseButton()
{

}
