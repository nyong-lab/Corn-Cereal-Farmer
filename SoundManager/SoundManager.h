#pragma once

#include "fmod.hpp"
#pragma comment(lib, "fmod_vc.lib")

class SoundManager
{
private:
	/// ������
	SoundManager();

	/// �Ҹ���
	~SoundManager();

	/// ���������
	SoundManager(const SoundManager& rhs) = delete;

	/// ���Կ�����
	SoundManager& operator=(const SoundManager& rhs) = delete;


public:
	/// ���� �Ŵ����� �ν��Ͻ��� ����
	static SoundManager* GetInstance();

	/// ���� �Ŵ����� �ν��Ͻ��� �ݳ�
	static void ReleaseInstance();


	/// �Ŵ����� �����͸� �̴ϼȶ������ ����
	void Initialize();

	/// ����Ŵ��� ����
	void Finalize();

	void Update();

	/// resource-> sound �����
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
	/// ���� ��ü
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