#pragma once
#include "..\Common\DeviceResources.h"
#include "..\Common\DirectXHelper.h"
#include "MeshObject.h"

ref class TrafficLightMesh : public MeshObject
{
internal:
	TrafficLightMesh(std::shared_ptr<DX::DeviceResources> deviceResources,
		ComPtr<ID3D12GraphicsCommandList> commandList,
		ComPtr<ID3D12PipelineState> pipelineState);
	virtual void Render(ComPtr<ID3D12GraphicsCommandList> commandList, std::string color);
};