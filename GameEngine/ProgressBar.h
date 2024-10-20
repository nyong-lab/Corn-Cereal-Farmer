/// [2023/8/11] 박연하
/// --------------------------
/// Image UI를 상속한 progressBar
/// 상태값을 외부에서 바꾸고 출력하는 함수만 추가한다
/// 렌더 위치 조정했다 (원점 기준 -> 좌상단 기준)
/// 
/// [2023/8/12] 박연하
/// --------------------------
/// Component를 변경하지 않고 프리팹을 만드는 식으로 재구성해야한다
/// 렌더 위치를 조정하지 않으려면 어떻게 해야하지?? 감이 잘 안온다
/// 이미지 출력 함수를 싹 뜯어 고쳐야하나
/// 근데 그러면 애니메이션 출력부터 싹... 고쳐야하는데...
/// 어쩔 수 없당 그래픽스엔진 공사 들어가야겠다

#pragma once

#include "GameObject.h"

class ProgressBar : public GameObject
{
public:
	// Getter & Setter
	void SetValue(float value)
	{
		if (m_BarMaxLength >= value)
			m_Value = value;
		else m_Value = m_BarMaxLength;
	}

private:
	float m_Value;
	float m_BarLength;
	float m_BarMaxLength;
};

