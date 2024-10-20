#include "Random.h"

float Random::Value()
{
	static std::random_device rd;
	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	static std::mt19937 gen(rd());

	static std::uniform_real_distribution<float> dis(0.0, 1.0);

	return dis(gen);
}
