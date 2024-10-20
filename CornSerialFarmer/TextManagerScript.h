#pragma once
#include "MonoBehaviour.h"
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::wstring;

/// <summary>
/// 작성일 : 2023.08.21
/// 작성자 : 고윤서
/// 
/// 캐릭터별 대화를 출력하기 위한 데이터를 저장해두는 script
/// </summary>


class TextManagerScript :
    public MonoBehaviour
{

public:
    TextManagerScript();
    ~TextManagerScript();

public:
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Finalize();

public:
	map<string, vector<wstring>> ScriptMap;		//데이터를 저장해둘 map 생성 key : NPC 이름, value : 몇번째 대사
	map<string, vector<wstring>> explainMap;	//상호작용이 가능한 물건들에 대해 설명 데이터를 저장해둘 map key : 상호작용 가능 물건들 이름, value 대사

	
};

