#pragma once
using namespace Microsoft::WRL;

ref class MeshObject abstract
{
internal:
	MeshObject();

	virtual void Render(ComPtr<ID3D12GraphicsCommandList> commandList);

protected private:
	Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
	UINT												m_vertexCount;
	UINT												m_indexCount;
	UINT												m_indexStart;
	D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;
};

