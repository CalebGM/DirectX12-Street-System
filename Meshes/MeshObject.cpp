#include "pch.h"
#include "MeshObject.h"


MeshObject::MeshObject() :
	m_vertexCount(0), m_indexCount(0)
{
}

void MeshObject::Render(ComPtr<ID3D12GraphicsCommandList> commandList)
{
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	commandList->IASetIndexBuffer(&m_indexBufferView);
	commandList->DrawIndexedInstanced(36, 1, 0, 0, 0);
}