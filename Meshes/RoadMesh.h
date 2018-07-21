#pragma once
#include "..\Common\DeviceResources.h"
#include "..\Common\DirectXHelper.h"
#include "MeshObject.h"

ref class RoadMesh : public MeshObject
{
internal:
	RoadMesh(std::shared_ptr<DX::DeviceResources> deviceResources,
		ComPtr<ID3D12GraphicsCommandList> commandList,
		ComPtr<ID3D12PipelineState> pipelineState);
};