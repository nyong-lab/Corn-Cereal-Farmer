/// [2023/8/11] �ڿ���
/// --------------------------
/// Image UI�� ����� progressBar
/// ���°��� �ܺο��� �ٲٰ� ����ϴ� �Լ��� �߰��Ѵ�
/// ���� ��ġ �����ߴ� (���� ���� -> �»�� ����)
/// 
/// [2023/8/12] �ڿ���
/// --------------------------
/// Component�� �������� �ʰ� �������� ����� ������ �籸���ؾ��Ѵ�
/// ���� ��ġ�� �������� �������� ��� �ؾ�����?? ���� �� �ȿ´�
/// �̹��� ��� �Լ��� �� ��� ���ľ��ϳ�
/// �ٵ� �׷��� �ִϸ��̼� ��º��� ��... ���ľ��ϴµ�...
/// ��¿ �� ���� �׷��Ƚ����� ���� ���߰ڴ�

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

