
#include "pch.h"
#include "SoundManager.h"


SoundManager* SoundManager::g_Instance;



SoundManager::SoundManager()
	: m_System(nullptr)
	, m_BGMChannel(nullptr)
	, m_SFXChannel(nullptr)
	, m_Version()
	, m_SFXVolume(1.f)
	, m_BGMVolume(1.f)
	, m_IsMute(false)
{
}

SoundManager::~SoundManager()
{
}


SoundManager* SoundManager::GetInstance()
{
	if (!g_Instance) {
		g_Instance = new SoundManager;
		atexit(ReleaseInstance);
	}
	return g_Instance;
}

void SoundManager::ReleaseInstance()
{
	if (g_Instance) {
		delete g_Instance;
		g_Instance = nullptr;
	}
}

void SoundManager::Initialize()
{
	FMOD_RESULT result = FMOD::System_Create(&m_System);
	if (result != FMOD_OK) return;                  // 첫번째로 꼭 꼭 !! 시스템 객체를 먼저 생성시켜야 한다.

	result; result = m_System->getVersion(&m_Version);
	result = m_System->init(32, FMOD_INIT_NORMAL, m_Extradriverdata);  // 시스템 초기화 : chaneel 32개까지 사용하겠다.
	
}

void SoundManager::Finalize()
{
	m_System->release();
}

void SoundManager::Update()
{
	m_System->update();
}

void SoundManager::CreateSound(FMOD::Sound** sound, std::wstring filePath)
{
	std::string strFilePath; 
	strFilePath.assign(filePath.begin(), filePath.end());
	FMOD_RESULT result = m_System->createSound(strFilePath.c_str(), FMOD_LOOP_OFF, 0, sound); // wav 파일로부터 sound 생성
}

void SoundManager::PlaySoundBGM(FMOD::Sound* sound)
{
	if (m_IsMute) return;
	m_System->playSound(sound, 0, false, &m_BGMChannel);
}

void SoundManager::PlaySoundSFX(FMOD::Sound* sound)
{
	if (m_IsMute) return;
	m_System->playSound(sound, 0, false, &m_SFXChannel);
}

void SoundManager::StopSoundBGM()
{
	m_BGMChannel->stop();
}

void SoundManager::StopSoundSFX()
{
	m_SFXChannel->stop();
}

void SoundManager::SetBGMVolume(float volume)
{
	if (m_IsMute) return;
	m_BGMVolume = volume;
	m_BGMChannel->setVolume(m_BGMVolume);
}

void SoundManager::SetSFXVolume(float volume)
{
	if (m_IsMute) return;
	m_SFXVolume = volume;
	m_SFXChannel->setVolume(m_SFXVolume);
}

void SoundManager::MuteOn()
{
	m_BGMChannel->setVolume(0.f);
	m_SFXChannel->setVolume(0.f);
	m_IsMute = true;
}

void SoundManager::MuteOff()
{
	m_BGMChannel->setVolume(m_BGMVolume);
	m_SFXChannel->setVolume(m_SFXVolume);
	m_IsMute = false;
}
