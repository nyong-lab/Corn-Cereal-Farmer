#pragma once
#include "Resource.h"
#include "Fmod.hpp"
class Sound :
    public Resource
{
public:
	Sound();
	virtual ~Sound();

public:
	virtual bool Load(wstring filePath, wstring fileName, FLOAT size) override;
	virtual void UnLoad() override;

public:
	void SetSound(FMOD::Sound* sound) { m_Sound = sound; }
	FMOD::Sound* GetSound() { return m_Sound; }
private:
    FMOD::Sound* m_Sound = nullptr;
};

