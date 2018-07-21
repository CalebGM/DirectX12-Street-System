#pragma once
#include "..\Meshes\MeshObject.h"
#include "..\Content\ShaderStructures.h"
using namespace _3DGraphicsTest;
using namespace DirectX;

ref class GameObject
{
internal:
	GameObject();

	virtual void Render(
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
		UINT8* mappedConstantBuffer,
		UINT objectOffset
	);

	virtual void Mesh(_In_ MeshObject^ mesh);

	void Position(XMFLOAT3 position);
	void Position(XMVECTOR position);
	void Velocity(XMFLOAT3 velocity);
	void Velocity(XMVECTOR velocity);

	void UpdateViewProjection(XMFLOAT4X4 view, XMFLOAT4X4 projection);

	XMMATRIX ModelMatrix();
	XMFLOAT3 Position();
	XMVECTOR VectorPosition();
	XMVECTOR VectorVelocity();
	XMFLOAT3 Velocity();

protected private:
	virtual void UpdatePosition() {};

	XMFLOAT3 m_position;
	XMFLOAT3 m_velocity;
	XMFLOAT4X4 m_modelMatrix;
	ModelViewProjectionConstantBuffer m_constantBufferData;
	XMFLOAT3 m_defaultXAxis;
	XMFLOAT3 m_defaultYAxis;
	XMFLOAT3 m_defaultZAxis;

	MeshObject^ m_mesh;
};

