#pragma once

#include "fmod.hpp"
#pragma comment(lib, "fmod_vc.lib")

class SoundManager
{
private:
	/// 생성자
	SoundManager();

	/// 소멸자
	~SoundManager();

	/// 복사생성자
	SoundManager(const SoundManager& rhs) = delete;

	/// 대입연산자
	SoundManager& operator=(const SoundManager& rhs) = delete;


public:
	/// 사운드 매니저의 인스턴스를 리턴
	static SoundManager* GetInstance();

	/// 사운드 매니저의 인스턴스를 반납
	static void ReleaseInstance();


	/// 매니저의 포인터를 이니셜라이즈에서 보냄
	void Initialize();

	/// 사운드매니저 종료
	void Finalize();

	void Update();

	/// resource-> sound 만들기
	void CreateSound(FMOD::Sound** sound, std::wstring filePath);

	void PlaySoundBGM(FMOD::Sound* sound);
	void PlaySoundSFX(FMOD::Sound* sound);

	void StopSoundBGM();
	void StopSoundSFX();

	void SetBGMVolume(float volume);
	void SetSFXVolume(float volume);

	float GetBGMVolume() { return m_BGMVolume; }
	float GetSFXVolume() { return m_SFXVolume; }
	void MuteOn();
	void MuteOff();

	bool GetIsMute() { return m_IsMute; }

private:
	/// 전역 객체
	static SoundManager* g_Instance;
	FMOD::System* m_System;
	FMOD::Channel* m_BGMChannel;
	FMOD::Channel* m_SFXChannel;
	unsigned int m_Version;
	void* m_Extradriverdata = nullptr;

	float m_BGMVolume;
	float m_SFXVolume;

	bool m_IsMute;

};