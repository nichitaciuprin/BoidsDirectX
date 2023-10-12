#pragma once

class Model
{
public:
    Model()
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

    virtual const vector<float>& VertexData() = 0;
    virtual const vector<uint16_t>& IndexData() = 0;

    void CreateVertexBuffer()
    {
        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = sizeof(VertexData());
        vertexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexSubresourceData = { };
        vertexSubresourceData.pSysMem = VertexData().data();

        auto device = DeviceRecources::GetInstance()->GetDevice();

        HRESULT hResult = device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
        assert(SUCCEEDED(hResult));
    }
    void CreateIndexBuffer()
    {
        indexCount = (UINT)IndexData().size();

        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(IndexData());
        indexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
        indexSubresourceData.pSysMem = IndexData().data();

        auto device = DeviceRecources::GetInstance()->GetDevice();

        HRESULT hResult = device->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
        assert(SUCCEEDED(hResult));
    }
};

class ModelBird2 : Model
{
};