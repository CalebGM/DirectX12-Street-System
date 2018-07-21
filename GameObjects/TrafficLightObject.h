#pragma once
#include "GameObject.h"
#include "..\Meshes\TrafficLightMesh.h"


ref class TrafficLightObject : public GameObject
{
internal:
	TrafficLightObject();
	TrafficLightObject(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target, std::string color);
	void Initialize(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target, std::string color);
	void Target(DirectX::XMFLOAT3 target);
	DirectX::XMFLOAT3 Target();
	void UpdateTime(double elapsedTime);
	void ChangeColor(std::string color);
	std::string Color();
	double TimeToRed();

	void Mesh(_In_ TrafficLightMesh^ mesh);

	void Render(
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
		UINT8* mappedConstantBuffer,
		UINT objectOffset
	) override;

protected:
	void UpdatePosition() override;

private:
	DirectX::XMFLOAT4X4 m_rotationMatrix;
	DirectX::XMFLOAT3 m_target;
	float m_angle;
	std::string	m_color;
	TrafficLightMesh^	m_mesh;
	UINT m_colorIndex;
	double m_timer;
	const std::string Colors[3] = { "Green", "Yellow", "Red" };
};

