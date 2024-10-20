#pragma once

#include <random>
/// <summary>
/// 2023.08.17
/// �ۼ��� : ��â��
/// 
/// ���� �Լ��� ������
/// 
/// </summary>
namespace Random
{	
	/// <summary>
	/// 0.0���� 1.0 ������ ������ �ε� �Ҽ��� ���� �����մϴ�.
	/// �Ϲ����� ������ �ش� ����� ���Ͽ� 0�� ������ ���� ������ ���ڷ� ��ȯ�ϴ� ���Դϴ�.
	/// </summary>
	/// <returns></returns>
	float Value();

	/// <summary>
	/// ����ڰ� ������ �ּڰ��� �ִ� ������ ������ ���ڸ� �����մϴ�. 
	/// ������ �ּڰ��� �ִ��� �������� �÷�Ʈ������ ���� ���� �Ǵ� �÷�Ʈ�� ��ȯ�մϴ�.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="min">�ּڰ� </param>
	/// <param name="max">�ִ� </param>
	/// <returns></returns>
	template <typename T>
	T Range(T min, T max);

	template <typename T>
	T Range(T min, T max)
	{
		return static_cast<T>(Value() * (max - min) + min);

	}

};
