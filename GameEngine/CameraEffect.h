#pragma once

class Camera;

/// <summary>
/// 최초 작성일 : 2023.08.11 
/// 작성자 : 김동일
/// 
/// 카메라 이펙트 관리
/// </summary>
enum class CAMERA_EFFECT_TYPE
{
	FADE_IN,
	FADE_OUT,

	END
};

class CameraEffect
{
public:
	CameraEffect();
	~CameraEffect();

public:
	// Get - Set
	CAMERA_EFFECT_TYPE GetEffectType() const { return m_Type; }
	const Camera* GetCamera() const { return m_Camera; }
	float GetDuration() const { return m_Duration; }
	float GetElaspedTime() const { return m_ElaspedTime; }
	bool IsFinish() const { return m_IsFinish; }

	void SetCamera(Camera* camera) { m_Camera = camera; }
	float SetDuration(float val) { m_Duration = val; }
	float SetElaspedTime(float val) { m_ElaspedTime = val; }
	void SetFinish(bool val) { m_IsFinish = val; }

private:
	const Camera* m_Camera = nullptr;
	CAMERA_EFFECT_TYPE m_Type = CAMERA_EFFECT_TYPE::END; // 카메라 효과 타입
	float m_Duration = 0.f; 
	float m_ElaspedTime = 0.f;
	bool m_IsFinish = false; // 끝났는지
};