#pragma once

class CubeRecourse
{
public:
    CubeRecourse(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11Buffer* constantBuffer)
    {
        this->device = device;
        this->deviceContext = deviceContext;
        this->constantBuffer = constantBuffer;
        CreateVertexBuffer(device);
        CreateIndexBuffer(device);
    }
    void Draw(Matrix modelViewProj) const
    {
        UINT stride = 3 * sizeof(float);
        UINT offset = 0;
        deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
        UpdateConstantBuffer(modelViewProj);
        deviceContext->DrawIndexed(indexCount, 0, 0);
    }
private:
    UINT indexCount;
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    ID3D11Buffer* constantBuffer;
    void CreateVertexBuffer(ID3D11Device* device)
    {
        float vertexData[] =
        {
            -0.5f,-0.5f,-0.5f,
            -0.5f,-0.5f, 0.5f,
            -0.5f, 0.5f,-0.5f,
            -0.5f, 0.5f, 0.5f,
             0.5f,-0.5f,-0.5f,
             0.5f,-0.5f, 0.5f,
             0.5f, 0.5f,-0.5f,
             0.5f, 0.5f, 0.5f
        };

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = sizeof(vertexData);
        vertexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexSubresourceData = { };
        vertexSubresourceData.pSysMem = vertexData;

        HRESULT hResult = device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
        assert(SUCCEEDED(hResult));
    }
    void CreateIndexBuffer(ID3D11Device* device)
    {
        uint16_t indices[] =
        {
            0, 6, 4,
            0, 2, 6,
            0, 3, 2,
            0, 1, 3,
            2, 7, 6,
            2, 3, 7,
            4, 6, 7,
            4, 7, 5,
            0, 4, 5,
            0, 5, 1,
            1, 5, 7,
            1, 7, 3
        };

        indexCount = sizeof(indices) / sizeof(indices[0]);

        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(indices);
        indexBufferDesc.Usage     = D3D11_USAGE_IMMUTABLE;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA indexSubresourceData = { indices };

        HRESULT hResult = device->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
        assert(SUCCEEDED(hResult));
    }
    void UpdateConstantBuffer(Matrix modelViewProj) const
    {
        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
        Constants* constants = (Constants*)(mappedSubresource.pData);
        constants->modelViewProj = modelViewProj;
        deviceContext->Unmap(constantBuffer, 0);
    }
};