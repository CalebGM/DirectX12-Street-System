#include "pch.h"
#include "TrafficLightMesh.h"
#include "..\Content\ShaderStructures.h"
using namespace _3DGraphicsTest;
using namespace DirectX;
using namespace Microsoft::WRL;

TrafficLightMesh::TrafficLightMesh(
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
		// Green Light
		{ XMFLOAT3(-1.5f, 1.0f, -0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 0
		{ XMFLOAT3(-1.5f, 1.0f,  0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 1

		{ XMFLOAT3(-1.5f, 0.8f, -0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 2
		{ XMFLOAT3(-1.5f, 0.8f,  0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 3

		{ XMFLOAT3(1.3f,  0.8f, -0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 4
		{ XMFLOAT3(1.3f,  0.8f,  0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 5

		{ XMFLOAT3(1.3f,  1.0f, -0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 6
		{ XMFLOAT3(1.3f,  1.0f,  0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 7

		{ XMFLOAT3(1.5f,  1.0f, -0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 8
		{ XMFLOAT3(1.5f,  1.0f,  0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 9

		{ XMFLOAT3(1.3f, -1.0f, -0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 10
		{ XMFLOAT3(1.3f, -1.0f,  0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 11

		{ XMFLOAT3(1.5f, -1.0f, -0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 12
		{ XMFLOAT3(1.5f, -1.0f,  0.2f), XMFLOAT3(0.0f, 0.9f, 0.0f) }, // 13


		// Yellow Light
		{ XMFLOAT3(-1.5f, 1.0f, -0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 0
		{ XMFLOAT3(-1.5f, 1.0f,  0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 1

		{ XMFLOAT3(-1.5f, 0.8f, -0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 2
		{ XMFLOAT3(-1.5f, 0.8f,  0.2f), XMFLOAT3(0.9f, 0.9f, 0.3f) }, // 3

		{ XMFLOAT3(1.3f,  0.8f, -0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 4
		{ XMFLOAT3(1.3f,  0.8f,  0.2f), XMFLOAT3(0.9f, 0.9f, 0.3f) }, // 5

		{ XMFLOAT3(1.3f,  1.0f, -0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 6
		{ XMFLOAT3(1.3f,  1.0f,  0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 7

		{ XMFLOAT3(1.5f,  1.0f, -0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 8
		{ XMFLOAT3(1.5f,  1.0f,  0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 9

		{ XMFLOAT3(1.3f, -1.0f, -0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 10
		{ XMFLOAT3(1.3f, -1.0f,  0.2f), XMFLOAT3(0.9f, 0.9f, 0.3f) }, // 11

		{ XMFLOAT3(1.5f, -1.0f, -0.2f), XMFLOAT3(0.9f, 1.0f, 0.0f) }, // 12
		{ XMFLOAT3(1.5f, -1.0f,  0.2f), XMFLOAT3(0.9f, 0.9f, 0.3f) }, // 13


		// Red Light
		{ XMFLOAT3(-1.5f, 1.0f, -0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 0
		{ XMFLOAT3(-1.5f, 1.0f,  0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 1

		{ XMFLOAT3(-1.5f, 0.8f, -0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 2
		{ XMFLOAT3(-1.5f, 0.8f,  0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 3

		{ XMFLOAT3(1.3f,  0.8f, -0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 4
		{ XMFLOAT3(1.3f,  0.8f,  0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 5

		{ XMFLOAT3(1.3f,  1.0f, -0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 6
		{ XMFLOAT3(1.3f,  1.0f,  0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 7

		{ XMFLOAT3(1.5f,  1.0f, -0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 8
		{ XMFLOAT3(1.5f,  1.0f,  0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 9

		{ XMFLOAT3(1.3f, -1.0f, -0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 10
		{ XMFLOAT3(1.3f, -1.0f,  0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 11

		{ XMFLOAT3(1.5f, -1.0f, -0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 12
		{ XMFLOAT3(1.5f, -1.0f,  0.2f), XMFLOAT3(0.9f, 0.0f, 0.0f) }, // 13
	};
	//0.0f, 0.0f, 0.0f
	//	0.0f, 0.0f, 1.0f
	//
	//	0.0f, 1.0f, 0.0f
	//	0.0f, 1.0f, 1.0f
	//
	//	1.0f, 0.0f, 0.0f
	//	1.0f, 0.0f, 1.0f
	//
	//	1.0f, 1.0f, 0.0f
	//	1.0f, 1.0f, 1.0f
	//
	//	0.0f, 1.0f, 0.0f
	//	0.0f, 1.0f, 1.0f
	//
	//	1.0f, 0.0f, 0.0f
	//	1.0f, 0.0f, 1.0f
	//
	//	1.0f, 1.0f, 0.0f
	//	1.0f, 1.0f, 1.0f

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
		// Horizontal Piece
		0, 3, 2, // -x
		3, 0, 1,

		0, 6, 7, // +y
		7, 1, 0,
				 
		2, 4, 5, // -y
		5, 3, 2,

		6, 0, 4, // -z
		0, 2, 4,

		3, 1, 7, // +z
		7, 5, 3,

		// Vertical Piece
		10, 6, 7, // -x
		7, 11, 10,

		13, 9, 8, // +x
		8, 12, 13,

		7, 6, 8, // +y
		8, 9, 7,

		11, 13, 12, // -y
		12, 10, 11,

		11, 7, 9, // +z
		9, 13, 11,

		8, 6, 10, // -z
		10, 12, 8,


		// Horizontal Piece
		14, 17, 16, // -x
		17, 14, 15,

		14, 20, 21, // +y
		21, 15, 14,

		16, 18, 19, // -y
		19, 17, 16,

		20, 14, 18, // -z
		14, 16, 18,

		17, 15, 21, // +z
		21, 19, 17,

		// Vertical Piece
		24, 20, 21, // -x
		21, 25, 24,

		27, 23, 22, // +x
		22, 26, 27,

		21, 20, 22, // +y
		22, 23, 21,

		25, 27, 26, // -y
		26, 24, 25,

		25, 21, 23, // +z
		23, 27, 25,

		22, 20, 24, // -z
		24, 26, 22,


		// Horizontal Piece
		28, 31, 30, // -x
		31, 28, 29,

		28, 34, 35, // +y
		35, 29, 28,

		30, 32, 33, // -y
		33, 31, 30,

		34, 28, 32, // -z
		28, 30, 32,

		31, 29, 35, // +z
		35, 33, 31,

		// Vertical Piece
		38, 34, 35, // -x
		35, 39, 38,

		41, 37, 36, // +x
		36, 40, 41,

		35, 34, 36, // +y
		36, 37, 35,

		39, 41, 40, // -y
		40, 38, 39,

		39, 35, 37, // +z
		37, 41, 39,

		36, 34, 38, // -z
		38, 40, 36,
	};

	const UINT indexBufferSize = sizeof(cubeIndices);
	m_indexCount = indexBufferSize / sizeof(cubeIndices[0]) / 3;

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


void TrafficLightMesh::Render(ComPtr<ID3D12GraphicsCommandList> commandList, std::string color)
{
	if (color == "Green") {
		m_indexStart = 0;
	}
	else if (color == "Yellow") {
		m_indexStart = m_indexCount;
	}
	else if (color == "Red") {
		m_indexStart = m_indexCount * 2;
	}

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	commandList->IASetIndexBuffer(&m_indexBufferView);
	commandList->DrawIndexedInstanced(m_indexCount, 1, m_indexStart, 0, 0);
}