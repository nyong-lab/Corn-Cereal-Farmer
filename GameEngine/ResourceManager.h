/// [2023/7/31] 박연하
/// --------------------------
/// 이미지, 사운드 등 게임에서 필요한 리소스를
/// 모두 가지고있는 리소스 매니저를 만들어 보자
/// 
/// 구조는 계속 고민중. 
/// 일단 템플릿을 쓰고, 하나의 맵에 리소스를 관리하되
/// 다이나믹 캐스트를 이용해 리소스를 Get할 수 있게 해봐야겠다
#pragma once

#include <assert.h>
#include <windows.h>
#include <string>
using std::wstring;
#include <map>
using std::map;
using std::pair;
using std::make_pair;
// 전방선언
class Resource;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

public:
	void Initialize();
	void Finalize();

	static ResourceManager* GetInstance() {
		if (!g_Instance) {
			g_Instance = new ResourceManager;
			atexit(ReleaseInstance);
		}
		return g_Instance;
	}

	static void ReleaseInstance() {
		if (g_Instance) {
			delete g_Instance;
			g_Instance = nullptr;
		}
	}

	/// <summary>
	/// 리소스가 있으면 리턴, 없으면 새로 불러와서 리소스 컨테이너에 넣는다
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="key"> 저장하고 불러올때 사용하는 키값 </param>
	/// <param name="filePath"> 리소스 불러올 때 필요한 파일 경로 </param>
	/// <param name="fileName"> 폰트 이름 </param>
	/// <param name="size"> 폰트 사이즈 </param>
	/// <returns></returns>
	template<typename T>
	T* LoadResource(
		LPCWSTR key,
		LPCWSTR filePath = L"",
		wstring fileName = L"",
		FLOAT size = 0.f
	);


private:
	static ResourceManager* g_Instance;
	map<wstring, Resource*> m_Resources;
};



#include "ResourceManager.hpp"
