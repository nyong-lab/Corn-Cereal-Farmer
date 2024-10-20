#include "pch.h"
#include "Sound.h"
#include "SoundManager.h"
#include "PathManager.h"

Sound::Sound() :
	Resource(),
	m_Sound()
{

}

Sound::~Sound()
{

}


bool Sound::Load(wstring filePath, wstring fileName, FLOAT size)
{
	SetFilePath(Path::MakeFilePath(filePath));

	SoundManager::GetInstance()->CreateSound(
		&m_Sound,
		GetFilePath().c_str()
	);

	return true;
}

void Sound::UnLoad()
{
	if (m_Sound != nullptr)
	{
		m_Sound->release();
		m_Sound = nullptr;
	}
}
