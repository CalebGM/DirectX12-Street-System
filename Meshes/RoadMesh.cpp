#include "pch.h"
#include "RoadMesh.h"
#include "..\Content\ShaderStructures.h"
using namespace _3DGraphicsTest;
using namespace DirectX;
using namespace Microsoft::WRL;

RoadMesh::RoadMesh(
	std::shared_ptr<DX::DeviceResources> deviceResources, 
	ComPtr<ID3D12GraphicsCommandList> commandList, 
	ComPtr<ID3D12PipelineState> pipelineState
)
{
	ID3D12Device* device = deviceResources->GetD3DDevice();
	DX::ThrowIfFailed(deviceResources->GetCommandAllocator()->Reset());
	DX::ThrowIfFailed(commandList->Reset(deviceResources->GetCommandAllocator(), pipelineState.Get()));

	VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT3(-25.0f,  0.0f, -0.7f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-25.0f,  0.0f,  0.7f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3( 25.0f,  0.0f, -0.7f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3( 25.0f,  0.0f,  0.7f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
	};

	const UINT vertexBufferSize = sizeof(cubeVertices);
	ComPtr<ID3D12Resource> vertexBufferUpload;

	CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
	DX::ThrowIfFailed(device->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexBufferDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_vertexBuffer)));

	CD3DX12_HEAP_PROPERTIES uploadHeapProperties(D3D12_HEAP_TYPE_UPLOAD);
	DX::ThrowIfFailed(device->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBufferUpload)));

	NAME_D3D12_OBJECT(m_vertexBuffer);
	m_vertexBuffer->SetName(L"Vertex Buffer Resource Heap");
	vertexBufferUpload->SetName(L"Vertex Buffer Upload Resource Heap");

	D3D12_SUBRESOURCE_DATA vertexData = {};
	vertexData.pData = reinterpret_cast<BYTE*>(cubeVertices);
	vertexData.RowPitch = vertexBufferSize;
	vertexData.SlicePitch = vertexData.RowPitch;

	UpdateSubresources(commandList.Get(), m_vertexBuffer.Get(), vertexBufferUpload.Get(), 0, 0, 1, &vertexData);
	CD3DX12_RESOURCE_BARRIER vertexBufferResourceBarrier =
		CD3DX12_RESOURCE_BARRIER::Transition(m_vertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	commandList->ResourceBarrier(1, &vertexBufferResourceBarrier);


	unsigned short cubeIndices[] =
	{
		0, 2, 1,
		1, 2, 3,
	};

	const UINT indexBufferSize = sizeof(cubeIndices);
	m_indexCount = indexBufferSize / sizeof(cubeIndices[0]);

	ComPtr<ID3D12Resource> indexBufferUpload;

	CD3DX12_RESOURCE_DESC indexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
	DX::ThrowIfFailed(device->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&indexBufferDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_indexBuffer)));

	DX::ThrowIfFailed(device->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&indexBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBufferUpload)));

	NAME_D3D12_OBJECT(m_indexBuffer);
	m_indexBuffer->SetName(L"Index Buffer Resource Heap");
	indexBufferUpload->SetName(L"Index Buffer Upload Resource Heap");

	D3D12_SUBRESOURCE_DATA indexData = {};
	indexData.pData = reinterpret_cast<BYTE*>(cubeIndices);
	indexData.RowPitch = indexBufferSize;
	indexData.SlicePitch = indexData.RowPitch;

	UpdateSubresources(commandList.Get(), m_indexBuffer.Get(), indexBufferUpload.Get(), 0, 0, 1, &indexData);

	CD3DX12_RESOURCE_BARRIER indexBufferResourceBarrier =
		CD3DX12_RESOURCE_BARRIER::Transition(m_indexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
	commandList->ResourceBarrier(1, &indexBufferResourceBarrier);

	DX::ThrowIfFailed(commandList->Close());
	ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
	deviceResources->GetCommandQueue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.StrideInBytes = sizeof(VertexPositionColor);
	m_vertexBufferView.SizeInBytes = sizeof(cubeVertices);

	m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
	m_indexBufferView.SizeInBytes = sizeof(cubeIndices);
	m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;

	deviceResources->WaitForGpu();
}