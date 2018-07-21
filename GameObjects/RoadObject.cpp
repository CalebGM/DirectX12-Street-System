#include "pch.h"
#include "RoadObject.h"


RoadObject::RoadObject()
{
	Initialize(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 0));
}

RoadObject::RoadObject(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target)
{
	Initialize(position, target);
}


void RoadObject::Initialize(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target)
{
	m_target = target;
	m_maxVelocity = 0.01;
	Position(position);
	XMMATRIX mat1 = XMMatrixIdentity();
	XMStoreFloat4x4(&m_rotationMatrix, mat1);
}


void RoadObject::Target(DirectX::XMFLOAT3 target)
{
	m_target = target;
}


DirectX::XMFLOAT3 RoadObject::Target()
{
	return m_target;
}


void RoadObject::SlowToStop()
{
	if (m_velocity.x >= 0.0001)
	{
		m_velocity.x -= 0.0001;
	}
	
}

void RoadObject::Stop()
{
	m_velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void RoadObject::AccelerateToMax()
{
	while (m_velocity.x <= m_maxVelocity - 0.0001)
	{
		m_velocity.x += 0.0001;
	}
}

void RoadObject::UpdatePosition()
{
	XMVECTOR direction = XMVector3Normalize(XMLoadFloat3(&m_target) - VectorPosition());
	float ans = XMVectorGetY(XMVector2AngleBetweenNormals(direction, XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)));
	m_angle = ans;

	if (XMVectorGetZ(direction) > 0)
	{
		m_angle *= -1;
	}

	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationY(m_angle) *XMMatrixTranslation(m_position.x, m_position.y, m_position.z)));
	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMLoadFloat4x4(&m_rotationMatrix) *XMMatrixTranslation(m_position.x, m_position.y, m_position.z));

}
