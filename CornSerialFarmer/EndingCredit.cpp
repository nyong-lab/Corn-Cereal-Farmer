#include "EndingCredit.h"

// Basic
#include "GameObject.h"
#include "Transform.h"

// Graphics
#include "../GraphicsEngine/GraphicsEngine.h"
#include "UI.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "Image.h"
#include "Animator.h"
#include "Animation.h"
#include "Panel.h"
#include "Button.h"
#include "font.h"

// Manager
#include "EventManager.h"
#include "ResourceManager.h"
#include "GameplayStatics.h"

// Sound
#include "SoundManager.h"
#include "Sound.h"


#include "CreditBubbleScript.h"

void EndingCredit::Enter()
{
	/// BGM
	SoundManager::GetInstance()->StopSoundBGM();
	SoundManager::GetInstance()->PlaySoundBGM(
		ResourceManager::GetInstance()->LoadResource<Sound>(L"EndingCreditBGM", L"/Sound/BGM/NIGHT/Evil5 - Whispers From Beyond.ogg")->GetSound());
	SoundManager::GetInstance()->SetBGMVolume(0.3f);
	SoundManager::GetInstance()->SetSFXVolume(0.1f);

	/// Background ----------------------------------------------------------

	// Object, Set Position & Size
	GameObject* endingCredit = new GameObject("EndingCredit", OBJECT_TYPE::UI);
	endingCredit->GetTransform()->SetLocalPosition(Vector2{ 960.f,540.f });
	endingCredit->GetTransform()->SetSize(Vector2{ 1920, 1080 });

	// Component
	UI* endingCreditPanel = new Panel();
	endingCredit->AddComponent(endingCreditPanel);
	ImageRenderer* endingCreditBG = new ImageRenderer(ResourceManager::GetInstance()->LoadResource<Image>(L"EndingCreditBG", L"/EndingCredit/creditBG.png")->GetImage());
	endingCredit->AddComponent(endingCreditBG);

	// Add Object
	AddGameObject(endingCredit);

	/// Ending Credit Exit Button ---------------------------------------------------------

	// Object, Set Position & Size
	GameObject* endingCreditExitButton = new GameObject("EndingExitButton", OBJECT_TYPE::UI);
	endingCreditExitButton->GetTransform()->SetLocalPosition(Vector2{ 1700.f,1000.f });
	endingCreditExitButton->GetTransform()->SetSize(Vector2{ 307.f, 84.f });

	// Button Image
	ImageRenderer* endingCreditExitButtonImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"CreditExitButton", L"/EndingCredit/backTitleButton.png")->GetImage());
	endingCreditExitButton->AddComponent(endingCreditExitButtonImage);

	// Ending Credit Button Callback
	UI* endingCreditExitButtonUI = new Button([endingCreditExitButtonImage](BUTTON_EVENT event) {
		if (event == BUTTON_EVENT::DEFAULT) {
			endingCreditExitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"CreditExitButton", L"/EndingCredit/backTitleButton.png")->GetImage());
		}
		if (event == BUTTON_EVENT::HOVER) {
			endingCreditExitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"CreditExitButton", L"/EndingCredit/backTitleButton.png")->GetImage());

			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonHoverSound", L"/Sound/SFX/Button/Button_MouseUp.mp3")->GetSound());
		}
		if (event == BUTTON_EVENT::DOWN) {
			endingCreditExitButtonImage->SetImage(
				ResourceManager::GetInstance()->LoadResource<Image>(L"CreditExitButtonClick", L"/EndingCredit/backTitleButtonPush.png")->GetImage());
		}
		if (event == BUTTON_EVENT::CLICK) {
			SoundManager::GetInstance()->PlaySoundSFX(
				ResourceManager::GetInstance()->LoadResource<Sound>(L"ButtonClickSound", L"/Sound/SFX/Button/Button_Click.mp3")->GetSound());

			GameplayStatics::LoadScene("StartScene");
		}
		});
	endingCreditExitButton->AddComponent(endingCreditExitButtonUI);

	// Add Object
	AddGameObject(endingCreditExitButton);


	/// BUTTON --------------------------------------------------------------
	
	const int PEOPLE_COUNT = 8;
	GameObject* creditPeople[PEOPLE_COUNT];
	Animator* creditPeopleAnimator[PEOPLE_COUNT];

	GameObject* creditBubble[PEOPLE_COUNT];
	ImageRenderer* creditBubbleImage[PEOPLE_COUNT];

	for (int index = 0; index < PEOPLE_COUNT; index++)
	{
		string Name = "People" + to_string(index);
		creditPeople[index] = new GameObject(Name, OBJECT_TYPE::UI);

		// Position
		Vector2 pos = {};
		if      (index == 0) pos = Vector2(395.f, 210.f);
		else if (index == 1) pos = Vector2(767.f, 210.f);
		else if (index == 2) pos = Vector2(1157.f, 210.f);
		else if (index == 3) pos = Vector2(1542.f, 210.f);
		else if (index == 4) pos = Vector2(395.f, 705.f);
		else if (index == 5) pos = Vector2(767.f, 705.f);
		else if (index == 6) pos = Vector2(1157.f, 705.f);
		else if (index == 7) pos = Vector2(1542.f, 705.f);

		// Set Position & Size
		creditPeople[index]->GetTransform()->SetLocalPosition(pos);
		creditPeople[index]->GetTransform()->SetSize(Vector2(245.f, 280.f));

		/// Animator
		creditPeopleAnimator[index] = new Animator(ResourceManager::GetInstance()->LoadResource<Image>(L"CreditAnimation", L"/EndingCredit/CreditAnim.png")->GetImage());
		creditPeople[index]->AddComponent(creditPeopleAnimator[index]);

		/// Speech Bubble
		string CreditBubbleName = "CreditBubble" + to_string(index);
		creditBubble[index] = new GameObject(CreditBubbleName, OBJECT_TYPE::UI);
		creditBubble[index]->GetTransform()->SetLocalPosition(Vector2(-2.f, 230.f));
		creditBubble[index]->GetTransform()->SetSize(Vector2(216.f, 162.f));

		creditBubbleImage[index] = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"CreditBubbleImageNone", L"/EndingCredit/creditBubbleNone.png")->GetImage()
		);
		creditBubble[index]->AddComponent(creditBubbleImage[index]);
		creditPeople[index]->AddObjectChild(creditBubble[index]);

		/// Speech Bubble Text
		TextRenderer* text = new TextRenderer(
			Vector2(0.f, -10.f),
			L"",
			ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont(),
			COLOR::BLACK);
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		text->SetTextAlignMiddle();
		creditBubble[index]->AddComponent(text);

		CreditBubbleScript* cBubbleScript = new CreditBubbleScript;
		creditBubble[index]->AddComponent(cBubbleScript);

		wstring textdata = L"";
		if (index == 0) textdata = L"옥수수(玉수수, 학명:\nZea mays)는 벼과에\n속하는 한해살이 식물\n이다. 멕시코 남서부...";
		else if (index == 1) textdata = L"\"모두의\n결과물입니다.\"";
		else if (index == 2) textdata = L"\"집 \?\n어림도 없지\"";
		else if (index == 3) textdata = L"집 가고 싶어요";
		else if (index == 4) textdata = L"X_X...\n살..려....조..";
		else if (index == 5) textdata = L"new를 했으면\ndelete를 하자...";
		else if (index == 6) textdata = L"웃으면 福이 온데요~\n빵! 터지는 인재원생\n활 되세요~~~*^^*";
		else if (index == 7) textdata = L"\"당신의 참여로\n이루어진\n놀라운 여정입니다.\"";

		cBubbleScript->m_Text = textdata;
		cBubbleScript->m_TextRenderer = text;
		cBubbleScript->m_SpeechBubble = creditBubbleImage[index];

		/// Button Callback
		UI* creditPeopleButton = new Button([index, creditPeopleAnimator, text, creditBubbleImage, cBubbleScript](BUTTON_EVENT event) {
			if (event == BUTTON_EVENT::HOVER) {
				// Sound
				SoundManager::GetInstance()->PlaySoundSFX(
					ResourceManager::GetInstance()->LoadResource<Sound>(L"EndingCreditButtonHoverSound", L"/Sound/SFX/Farm/Digging_Dirt_With_Hand (2).mp3")->GetSound());
			}
			if (event == BUTTON_EVENT::CLICK) {

				// Animation Data
				wstring animationKey = L"";
				if		(index == 0) animationKey = L"예린-SHOW";
				else if (index == 1) animationKey = L"상혁-SHOW";
				else if (index == 2) animationKey = L"주현-SHOW";
				else if (index == 3) animationKey = L"채린-SHOW";
				else if (index == 4) animationKey = L"연하-SHOW";
				else if (index == 5) animationKey = L"윤서-SHOW";
				else if (index == 6) animationKey = L"창도-SHOW";
				else if (index == 7) animationKey = L"동일-SHOW";

				// Animation
				creditPeopleAnimator[index]->Play(animationKey, true);

				// Text
				cBubbleScript->BtnCallBackFunc();
				
				// Image
				creditBubbleImage[index]->SetImage(
					ResourceManager::GetInstance()->LoadResource<Image>(L"CreditBubbleImage", L"/EndingCredit/creditBubble.png")->GetImage()
				);
				
				// Sound
				SoundManager::GetInstance()->PlaySoundSFX(
					ResourceManager::GetInstance()->LoadResource<Sound>(L"EndingCreditButtonClickSound", L"/Sound/SFX/Interaction/Item_Pickup.mp3")->GetSound());
			}
			});
		creditPeople[index]->AddComponent(creditPeopleButton);

		AddGameObject(creditPeople[index]);
	}

	/// Animation Setting

	Vector2 offset = { 0.f, 0.f };
	Vector2 frameSize = { 245.f, 280.f };
	float startSliceSizeY = 280.f;
	Vector2 sliceSize = { 245.f, 0.f };
	float duration = 0.15f;
	int frameCount = 4;

	creditPeopleAnimator[0]->CreateAnimation(L"예린-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 0), sliceSize, duration, frameCount);
	creditPeopleAnimator[0]->CreateAnimation(L"예린-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 1), sliceSize, duration, frameCount);
	creditPeopleAnimator[0]->Play(L"예린-HIDE", true);

	creditPeopleAnimator[1]->CreateAnimation(L"상혁-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 2), sliceSize, duration, frameCount);
	creditPeopleAnimator[1]->CreateAnimation(L"상혁-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 3), sliceSize, duration, frameCount);
	creditPeopleAnimator[1]->Play(L"상혁-HIDE", true);

	creditPeopleAnimator[2]->CreateAnimation(L"주현-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 4), sliceSize, duration, frameCount);
	creditPeopleAnimator[2]->CreateAnimation(L"주현-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 5), sliceSize, duration, frameCount);
	creditPeopleAnimator[2]->Play(L"주현-HIDE", true);

	creditPeopleAnimator[3]->CreateAnimation(L"채린-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 6), sliceSize, duration, frameCount);
	creditPeopleAnimator[3]->CreateAnimation(L"채린-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 7), sliceSize, duration, frameCount);
	creditPeopleAnimator[3]->Play(L"채린-HIDE", true);

	creditPeopleAnimator[4]->CreateAnimation(L"연하-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 8), sliceSize, duration, frameCount);
	creditPeopleAnimator[4]->CreateAnimation(L"연하-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 9), sliceSize, duration, frameCount);
	creditPeopleAnimator[4]->Play(L"연하-HIDE", true);

	creditPeopleAnimator[5]->CreateAnimation(L"윤서-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 10), sliceSize, duration, frameCount);
	creditPeopleAnimator[5]->CreateAnimation(L"윤서-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 11), sliceSize, duration, frameCount);
	creditPeopleAnimator[5]->Play(L"윤서-HIDE", true);

	creditPeopleAnimator[6]->CreateAnimation(L"창도-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 12), sliceSize, duration, frameCount);
	creditPeopleAnimator[6]->CreateAnimation(L"창도-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 13), sliceSize, duration, frameCount);
	creditPeopleAnimator[6]->Play(L"창도-HIDE", true);

	creditPeopleAnimator[7]->CreateAnimation(L"동일-SHOW", offset, frameSize, Vector2(0, startSliceSizeY * 14), sliceSize, duration, frameCount);
	creditPeopleAnimator[7]->CreateAnimation(L"동일-HIDE", offset, frameSize, Vector2(0, startSliceSizeY * 15), sliceSize, duration, frameCount);
	creditPeopleAnimator[7]->Play(L"동일-HIDE", true);


}

