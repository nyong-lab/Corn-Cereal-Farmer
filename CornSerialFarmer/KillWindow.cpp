#include "KillWindow.h"
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
#include "Font.h"

#include "SoundManager.h"
#include "Sound.h"

#include "Animation.h"
#include "Animator.h"

#include "KillWindowScript.h"

#include "EventManager.h"

KillWindow::KillWindow(int date, int npc1, int npc2, int npc3, int npc4)
	: GameObject("KillWindow", OBJECT_TYPE::UI)
	, m_Npc1(npc1)
	, m_Npc2(npc2)
	, m_Npc3(npc3)
	, m_Npc4(npc4)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(960.f, 540.f));
	GetTransform()->SetSize(Vector2(1920.f, 1080.f));

	// Base UI
	UI* killWindowUI = new Panel();
	AddComponent(killWindowUI);

	// Base Image
	ImageRenderer* killWindowImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"KillWindowImage", L"/Image/Kill/killBase.png")->GetImage());
	AddComponent(killWindowImage);

	/// Script
	KillWindowScript* killWindowScript = new KillWindowScript;
	AddComponent(killWindowScript);

	/// BUTTON -----------------------------------------------------------

	/// YES

	// Set Position & Size
	GameObject* yesButton = new GameObject("YesButton", OBJECT_TYPE::UI);
	yesButton->GetTransform()->SetLocalPosition(Vector2(-180.f, 400.f));
	yesButton->GetTransform()->SetSize(Vector2(280.f, 140.f));

	// Button Image
	ImageRenderer* yesButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"YesButton", L"/Image/Kill/killyesButton.png")->GetImage()
	);
	yesButton->AddComponent(yesButtonImage);

	// Button Callback
	UI* yesButtonUI = new Button([yesButtonImage, killWindowScript, this](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			yesButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"YesButton", L"/Image/Kill/killyesButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			// Image
			yesButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"YesButtonClick", L"/Image/Kill/killyesButtonClick.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			yesButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"YesButtonClick", L"/Image/Kill/killyesButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			yesButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"YesButton", L"/Image/UI/game_popup/killyesButton.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());

			// Send Event
			EventManager::GetInstance()->SendEvent("CompleteKill",killWindowScript->m_SelectIndex);
			GameplayStatics::DestroyObject(this);
		}
		});
	yesButton->AddComponent(yesButtonUI);

	// Add Child
	AddObjectChild(yesButton);

	/// NO

	// Set Position & Size
	GameObject* noButton = new GameObject("NoButton", OBJECT_TYPE::UI);
	noButton->GetTransform()->SetLocalPosition(Vector2(180.f, 400.f));
	noButton->GetTransform()->SetSize(Vector2(280.f, 140.f));

	// Button Image
	ImageRenderer* noButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"NoButton", L"/Image/Kill/killnoButton.png")->GetImage());
	noButton->AddComponent(noButtonImage);

	// Button Callback
	UI* noButtonUI = new Button([noButtonImage, killWindowScript, this](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			noButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"NoButton", L"/Image/Kill/killnoButton.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::HOVER) {
			// Image
			noButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"NoButtonClick", L"/Image/Kill/killnoButtonClick.png")->GetImage()
			);

			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			noButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"NoButtonClick", L"/Image/Kill/killnoButtonClick.png")->GetImage()
			);
		}
		if (event == BUTTON_EVENT::CLICK) {
			// Image
			killWindowScript->m_SelectIndex = -1;

			noButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"NoButton", L"/Image/UI/game_popup/killnoButton.png")->GetImage()
			);
			// Sound
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());
			SoundManager::GetInstance()->StopSoundBGM();

			// Send Event
			EventManager::GetInstance()->SendEvent("CompleteKill", killWindowScript->m_SelectIndex);
			GameplayStatics::DestroyObject(this);
		}
		});
	noButton->AddComponent(noButtonUI);

	// Add Child
	AddObjectChild(noButton);

	/// TEXT -----------------------------------------------------------

	GameObject* completeDate = new GameObject("CompleteDateText", OBJECT_TYPE::UI);
	completeDate->GetTransform()->SetLocalPosition(Vector2(0.f,-330.f));

	// Empty UI
	UI* completeDateUI = new Panel();
	completeDate->AddComponent(completeDateUI);

	wstring textData = to_wstring(date) + L"일차 완료";
	// Date Text Renderer
	TextRenderer* completetDateText = new TextRenderer(
		Vector2(0.f, -90.f),
		textData,
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri7_48", L"/Font/Galmuri7.ttf", L"Galmuri7", 48.f)->Getfont(),
		COLOR::WHITE
	);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri7_48")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri7_48")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	completetDateText->SetTextAlignMiddle();
	completeDate->AddComponent(completetDateText);

	// Add Child
	AddObjectChild(completeDate);

	/// NPC SELECT BOX -----------------------------------------------------------

	for (int npcIndex = 0; npcIndex < 4; npcIndex++)
	{
		if (npcIndex == 0 && npc1 == 999) continue;

		string NPCSelectName = "NPCSelect" + to_string(npcIndex);
		m_NpcSelect[npcIndex] = new GameObject(NPCSelectName, OBJECT_TYPE::UI);

		// Position
		float xPos = 0.f;
		if      (npcIndex == 0) xPos = -250.f;
		else if (npcIndex == 1) xPos = -80.f;
		else if (npcIndex == 2) xPos = 90.f;
		else if (npcIndex == 3) xPos = 260.f;

		// Set Position & Size
		m_NpcSelect[npcIndex]->GetTransform()->SetLocalPosition(Vector2(xPos, 80.f));
		m_NpcSelect[npcIndex]->GetTransform()->SetSize(Vector2(140.f, 160.f));

		/// Animator
		m_NpcSelectAnimator[npcIndex] = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"NPCImage", L"/Image/Kill/npcIdle.png")->GetImage());
		m_NpcSelectAnimator[npcIndex]->CreateAnimation(L"SelectNPC1", Vector2(0, 0), Vector2(140, 160), Vector2(0, 160), Vector2(140, 0), 0.1f, 4);
		m_NpcSelectAnimator[npcIndex]->CreateAnimation(L"SelectNPC2", Vector2(0, 0), Vector2(140, 160), Vector2(0, 320), Vector2(140, 0), 0.1f, 4);
		m_NpcSelectAnimator[npcIndex]->CreateAnimation(L"SelectNPC3", Vector2(0, 0), Vector2(140, 160), Vector2(0, 480), Vector2(140, 0), 0.1f, 4);
		m_NpcSelectAnimator[npcIndex]->CreateAnimation(L"SelectNPC4", Vector2(0, 0), Vector2(140, 160), Vector2(0, 640), Vector2(140, 0), 0.1f, 4);
		m_NpcSelectAnimator[npcIndex]->CreateAnimation(L"SelectNPC5", Vector2(0, 0), Vector2(140, 160), Vector2(0, 800), Vector2(140, 0), 0.1f, 4);
		m_NpcSelectAnimator[npcIndex]->CreateAnimation(L"SelectNPC6", Vector2(0, 0), Vector2(140, 160), Vector2(0, 960), Vector2(140, 0), 0.1f, 4);
		// none
		m_NpcSelectAnimator[npcIndex]->CreateAnimation(L"SelectNPC999", Vector2(0, 0), Vector2(140, 160), Vector2(0, 0), Vector2(140, 0), 0.1f, 4);
		m_NpcSelect[npcIndex]->AddComponent(m_NpcSelectAnimator[npcIndex]);

		/// Select Icon
		string NPCSelectIconName = "NPCSelectIcon" + to_string(npcIndex);
		m_NpcSelectIcon[npcIndex] = new GameObject(NPCSelectIconName, OBJECT_TYPE::UI);
		m_NpcSelectIcon[npcIndex]->GetTransform()->SetLocalPosition(Vector2(0.f, -120.f));
		m_NpcSelectIcon[npcIndex]->GetTransform()->SetSize(Vector2(62.f, 49.f));

		m_NpcSelectImage[npcIndex] = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"NpcSelectIcon", L"/Image/Kill/killSelect.png")->GetImage()
		);
		m_NpcSelectIcon[npcIndex]->AddComponent(m_NpcSelectImage[npcIndex]);
		m_NpcSelect[npcIndex]->AddObjectChild(m_NpcSelectIcon[npcIndex]);

		/// Button Callback
		UI* npcSelectButton = new Button([this, npcIndex, killWindowScript](BUTTON_EVENT event) {
			if (event == BUTTON_EVENT::HOVER) {
				// Sound
				SoundManager::GetInstance()->PlaySoundSFX(
					ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
			}
			if (event == BUTTON_EVENT::CLICK) {

				int i = 0;
				if (m_Npc1 == 999) i = 1;

				for (; i < 4; i++)
				{
					m_NpcSelectImage[i]->SetImage(
						ResourceManager::GetInstance()->LoadResource<Image>(L"NpcSelectIcon", L"/Image/Kill/killSelect.png")->GetImage()
					);
					m_NpcSelectAnimator[i]->GetCurrentAnimation()->SetFrameFixed(0);
				}
				m_NpcSelectImage[npcIndex]->SetImage(
					ResourceManager::GetInstance()->LoadResource<Image>(L"NpcSelectIconFocus", L"/Image/Kill/killSelectFocus.png")->GetImage()
				);
				m_NpcSelectAnimator[npcIndex]->GetCurrentAnimation()->ReleaseFrameFixed();

				// Sound
				SoundManager::GetInstance()->PlaySoundSFX(
					ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());

				if (npcIndex == 0) killWindowScript->m_SelectIndex = m_Npc1;
				else if (npcIndex == 1) killWindowScript->m_SelectIndex = m_Npc2;
				else if (npcIndex == 2) killWindowScript->m_SelectIndex = m_Npc3;
				else if (npcIndex == 3) killWindowScript->m_SelectIndex = m_Npc4;
			}
			});
		m_NpcSelect[npcIndex]->AddComponent(npcSelectButton);

		AddObjectChild(m_NpcSelect[npcIndex]);
	}

	if (m_NpcSelect[0])
	{
		wstring AnimationKey1 = L"SelectNPC" + to_wstring(m_Npc1);
		m_NpcSelectAnimator[0]->Play(AnimationKey1, true);
		m_NpcSelectAnimator[0]->FindAnimation(AnimationKey1)->SetFrameFixed(0);
	}
	
	wstring AnimationKey2 = L"SelectNPC" + to_wstring(m_Npc2);
	m_NpcSelectAnimator[1]->Play(AnimationKey2, true);
	m_NpcSelectAnimator[1]->FindAnimation(AnimationKey2)->SetFrameFixed(0);

	wstring AnimationKey3 = L"SelectNPC" + to_wstring(m_Npc3);
	m_NpcSelectAnimator[2]->Play(AnimationKey3, true);
	m_NpcSelectAnimator[2]->FindAnimation(AnimationKey3)->SetFrameFixed(0);

	wstring AnimationKey4 = L"SelectNPC" + to_wstring(m_Npc4);
	m_NpcSelectAnimator[3]->Play(AnimationKey4, true);
	m_NpcSelectAnimator[3]->FindAnimation(AnimationKey4)->SetFrameFixed(0);

}

KillWindow::~KillWindow()
{

}

