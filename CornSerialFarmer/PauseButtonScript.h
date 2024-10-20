#pragma once
#include <MonoBehaviour.h>

class PauseButtonScript : public MonoBehaviour
{
public:
	PauseButtonScript();
	~PauseButtonScript();

	void ResumeGame(std::any);

public:
	virtual void Start() override;


public:
	bool m_IsClicked = false;
};

