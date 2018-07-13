#include "pch.h"
#include "CarObject.h"


CarObject::CarObject()
{
	Initialize(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 0));
}

CarObject::CarObject(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target)
{
	Initialize(position, target);
}
void CarObject::Initialize(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target)
{
	m_target = target;
	Position(position);
	XMMATRIX mat1 = XMMatrixIdentity();
	XMStoreFloat4x4(&m_rotationMatrix, mat1);
}
void CarObject::Target(DirectX::XMFLOAT3 target)
{
	m_target = target;
}
DirectX::XMFLOAT3 CarObject::Target()
{
	return m_target;
}
void CarObject::UpdatePosition()
{
	XMVECTOR direction = XMVector3Normalize(XMLoadFloat3(&m_target) - VectorPosition());
	float ans = XMVectorGetY(XMVector2AngleBetweenNormals(direction, XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)));
	m_angle = ans;

	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationY(m_angle) *XMMatrixTranslation(m_position.x, m_position.y, m_position.z)));
	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMLoadFloat4x4(&m_rotationMatrix) *XMMatrixTranslation(m_position.x, m_position.y, m_position.z));

}
