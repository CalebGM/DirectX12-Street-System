#include "pch.h"
#include "GameObject.h"


GameObject::GameObject()
{
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_velocity = XMFLOAT3(0.01f, 0.0f, 0.0f);
	m_defaultXAxis = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_defaultYAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_defaultZAxis = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixIdentity());
}


void GameObject::Render(
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
	UINT8* mappedConstantBuffer,
	UINT objectOffset
)
{
	if (m_mesh == nullptr)
	{
		return;
	}

	memcpy(mappedConstantBuffer + objectOffset, &m_constantBufferData, sizeof(m_constantBufferData));
	m_mesh->Render(commandList);
}


void GameObject::UpdateViewProjection(XMFLOAT4X4 view, XMFLOAT4X4 projection)
{
	m_constantBufferData.view = view;
	m_constantBufferData.projection = projection;
}


void GameObject::Mesh(_In_ MeshObject^ mesh)
{
	m_mesh = mesh;
}


void GameObject::Position(XMFLOAT3 position)
{
	m_position = position;
	UpdatePosition();
}


void GameObject::Position(XMVECTOR position)
{
	XMStoreFloat3(&m_position, position);
	UpdatePosition();
}


void GameObject::Velocity(XMFLOAT3 velocity)
{
	m_velocity = velocity;
}


void GameObject::Velocity(XMVECTOR velocity)
{
	XMStoreFloat3(&m_velocity, velocity);
}


XMMATRIX GameObject::ModelMatrix()
{
	return XMLoadFloat4x4(&m_constantBufferData.model);
}


XMFLOAT3 GameObject::Position()
{
	return m_position;
}


XMVECTOR GameObject::VectorPosition()
{
	return XMLoadFloat3(&m_position);
}


XMVECTOR GameObject::VectorVelocity()
{
	return XMLoadFloat3(&m_velocity);
}


XMFLOAT3 GameObject::Velocity()
{
	return m_velocity;
}

