#include "CornSerialFarmer.h"
#include "GameProcess.h"
#include "SceneManager.h"

/// 똑같이 여기에 신 헤더 추가하고
#include "TestScene.h"
#include "NextScene.h"
#include "ChangdoScene.h"
#include "Yeonha.h"
#include "YoonsuScene.h"
#include "DongilScene.h"
#include "MainScene.h"
#include "StartScene.h"
#include "BloodStartScene.h"
#include "YoonseoTestScene.h"
#include "OpeningScene.h"
#include "ArrestedEnding.h"
#include "EndingCredit.h"
#include "TrueEnding.h"
#include "GameOver.h"

CornSerialFarmer::CornSerialFarmer(GameProcess* gameProcess) :
	m_GameProcess(gameProcess)
{

}

CornSerialFarmer::~CornSerialFarmer()
{

}

void CornSerialFarmer::InitializeGame()
{
	/// 여기에 이렇게 애드씬해주자..
	m_GameProcess->GetSceneManager()->AddScene(new StartScene("StartScene"));
	m_GameProcess->GetSceneManager()->AddScene(new BloodStartScene("BloodStartScene"));
	m_GameProcess->GetSceneManager()->AddScene(new OpeningScene("OpeningScene"));
	m_GameProcess->GetSceneManager()->AddScene(new MainScene("MainScene"));
	m_GameProcess->GetSceneManager()->AddScene(new EndingCredit("EndingCredit"));
	m_GameProcess->GetSceneManager()->AddScene(new TrueEnding("TrueEnding"));
	m_GameProcess->GetSceneManager()->AddScene(new ArrestedEnding("ArrestedEnding"));

	/// Set Start Scene

	m_GameProcess->GetSceneManager()->SetStartScene("StartScene");
	m_GameProcess->Initialize();
}
