#pragma once
#include "MonoBehaviour.h"
/// <summary>
/// 작성일 : 2023.08.21
/// 작성자 : 고윤서
/// 
/// 캐릭터별 대화를 출력하기 위한 데이터를 저장해두는 script
/// </summary>

class ScriptManager :
    public MonoBehaviour
{

public:
    ScriptManager();
    ~ScriptManager();

public:
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Finalize();

};

