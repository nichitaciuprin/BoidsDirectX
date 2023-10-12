#pragma once

class ModelBird
{
public:
    ModelBird()
    {
        CreateVertexBuffer();
        CreateIndexBuffer();
    }

    void Draw()
    {
        UINT stride = sizeof(Vector3);
        UINT offset = 0;
        auto deviceRecources = DeviceRecources::GetInstance();
        auto deviceContext = deviceRecources->GetDeviceContext();
        deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        deviceContext->DrawIndexed(indexCount, 0, 0);
    }

private:
    UINT indexCount;
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;

    void CreateVertexBuffer()
    {
        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = sizeof(ModelStatic::Bird::VertexData);
        vertexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA subresourceData = {};
        subresourceData.pSysMem = ModelStatic::Bird::VertexData.data();

        auto device = DeviceRecources::GetInstance()->GetDevice();

        HRESULT hResult = device->CreateBuffer(&vertexBufferDesc, &subresourceData, &vertexBuffer);
        assert(SUCCEEDED(hResult));
    }
    void CreateIndexBuffer()
    {
        indexCount = (UINT)ModelStatic::Bird::IndexData.size();

        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(ModelStatic::Bird::IndexData);
        indexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA subresourceData = {};
        subresourceData.pSysMem = ModelStatic::Bird::IndexData.data();

        auto device = DeviceRecources::GetInstance()->GetDevice();

        HRESULT hResult = device->CreateBuffer(&indexBufferDesc, &subresourceData, &indexBuffer);
        assert(SUCCEEDED(hResult));
    }
};