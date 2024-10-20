#pragma once

#include <random>
/// <summary>
/// 2023.08.17
/// 작성자 : 정창도
/// 
/// 랜덤 함수를 만들자
/// 
/// </summary>
namespace Random
{	
	/// <summary>
	/// 0.0에서 1.0 사이의 임의의 부동 소수점 수를 제공합니다.
	/// 일반적인 사용법은 해당 결과를 곱하여 0과 선택한 범위 사이의 숫자로 변환하는 것입니다.
	/// </summary>
	/// <returns></returns>
	float Value();

	/// <summary>
	/// 사용자가 제공한 최솟값과 최댓값 사이의 임의의 숫자를 제공합니다. 
	/// 제공된 최솟값과 최댓값이 정수인지 플로트인지에 따라 정수 또는 플로트를 반환합니다.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="min">최솟값 </param>
	/// <param name="max">최댓값 </param>
	/// <returns></returns>
	template <typename T>
	T Range(T min, T max);

	template <typename T>
	T Range(T min, T max)
	{
		return static_cast<T>(Value() * (max - min) + min);

	}

};
