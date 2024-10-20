///
/// 2023.08.09 
/// 작성자 : 정창도
/// dll을 떼면서 구조를 어떻게 해야하지 싶었다.
/// 그냥 파머 게임에 게임엔진 넣어서 돌리는식으로 햇다.
///
#pragma once

class GameProcess;

class CornSerialFarmer
{
public:
	CornSerialFarmer(GameProcess* gameProcess);
	~CornSerialFarmer();

	void InitializeGame();

private:
	GameProcess* m_GameProcess;
};

