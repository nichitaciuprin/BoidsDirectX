#pragma once

class ModelOverlapingTriangles
{
public:
    ModelOverlapingTriangles()
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
        float vertexData[] =
        {
             2, 3, 1,
             3, 1, 1,
            -3, 1, 0,

            -3, 1, 1,
            -2, 3, 1,
             1,-3, 0,

             1,-3, 1,
            -1,-3, 1,
             2, 3, 0
        };

        for (size_t i = 0; i < ARRAYSIZE(vertexData); i++)
            vertexData[i] /= 4;

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = sizeof(vertexData);
        vertexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexSubresourceData = { };
        vertexSubresourceData.pSysMem = vertexData;

        auto device = DeviceRecources::GetInstance()->GetDevice();

        HRESULT hResult = device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
        assert(SUCCEEDED(hResult));
    }
    void CreateIndexBuffer()
    {
        uint16_t indices[] =
        {
            0, 1, 2,
            3, 4, 5,
            6, 7, 8
        };

        indexCount = ARRAYSIZE(indices);

        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(indices);
        indexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA indexSubresourceData = { indices };

        auto device = DeviceRecources::GetInstance()->GetDevice();

        HRESULT hResult = device->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
        assert(SUCCEEDED(hResult));
    }
};