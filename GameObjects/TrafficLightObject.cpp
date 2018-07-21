#include "pch.h"
#include "TrafficLightObject.h"


TrafficLightObject::TrafficLightObject()
{
	Initialize(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 0), "Green");
}

TrafficLightObject::TrafficLightObject(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target, std::string color)
{
	Initialize(position, target, color);
}
void TrafficLightObject::Initialize(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 target, std::string color)
{
	m_target = target;
	m_color = color;
	if (color == "Green")
	{
		m_colorIndex = 0;
	}
	else if (color == "Yellow")
	{
		m_colorIndex = 1;
	}
	else
	{
		m_colorIndex = 2;
	}
	m_timer = 0.0;
	Position(position);
	XMMATRIX mat1 = XMMatrixIdentity();
	XMStoreFloat4x4(&m_rotationMatrix, mat1);
}
void TrafficLightObject::Target(DirectX::XMFLOAT3 target)
{
	m_target = target;
}
DirectX::XMFLOAT3 TrafficLightObject::Target()
{
	return m_target;
}

void TrafficLightObject::UpdateTime(double elapsedTime)
{
	m_timer += elapsedTime;

	if (m_colorIndex == 1)
	{
		if (m_timer > 2.0)
		{
			m_colorIndex++;
			m_color = Colors[m_colorIndex];
			m_timer = 0.0;
		}
	}
	else if (m_timer > 8.0)
	{
		if (m_colorIndex >= 2)
		{
			m_colorIndex = 0;
		}
		else
		{
			m_colorIndex++;
		}
		m_color = Colors[m_colorIndex];
		m_timer = 0.0;
	}
}

void TrafficLightObject::ChangeColor(std::string color)
{
	m_color = color;
}

std::string TrafficLightObject::Color()
{
	return m_color;
}

double TrafficLightObject::TimeToRed()
{
	return (2.0 - m_timer);
}

void TrafficLightObject::UpdatePosition()
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


void TrafficLightObject::Mesh(_In_ TrafficLightMesh^ mesh)
{
	m_mesh = mesh;
}

void TrafficLightObject::Render(
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
	m_mesh->Render(commandList, m_color);
}