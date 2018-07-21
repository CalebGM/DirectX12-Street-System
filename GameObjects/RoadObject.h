#pragma once
#include "GameObject.h"

ref class RoadObject : public GameObject
{
internal:
	RoadObject();
	RoadObject(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target);
	void Initialize(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target);
	void Target(DirectX::XMFLOAT3 target);
	DirectX::XMFLOAT3 Target();
	void SlowToStop();
	void Stop();
	void AccelerateToMax();

protected:
	void UpdatePosition() override;

private:
	DirectX::XMFLOAT4X4 m_rotationMatrix;
	DirectX::XMFLOAT3 m_target;
	float m_angle;
	double m_maxVelocity;
};

