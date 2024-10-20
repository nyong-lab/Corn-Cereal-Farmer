#include "Random.h"

float Random::Value()
{
	static std::random_device rd;
	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	static std::mt19937 gen(rd());

	static std::uniform_real_distribution<float> dis(0.0, 1.0);

	return dis(gen);
}
