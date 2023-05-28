#pragma once

struct Constants
{
    Matrix modelViewProj;
};

class DeviceRecources
{
public:
    static DeviceRecources* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new DeviceRecources();
        }
        return instance;
    }
    ID3D11Device* GetDevice()
    {
        return device;
    }
    ID3D11DeviceContext* GetDeviceContext()
    {
        return deviceContext;
    }
    ID3D11Buffer* GetConstantBuffer()
    {
        return constantBuffer;
    }
    void UpdateConstantBuffer(Matrix modelViewProj)
    {
        D3D11_MAPPED_SUBRESOURCE mappedSubresource;
        deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
        Constants* constants = (Constants*)(mappedSubresource.pData);
        constants->modelViewProj = modelViewProj;
        deviceContext->Unmap(constantBuffer, 0);
    }
private:
    static DeviceRecources*   instance;
    ID3D11Device*             device;
    ID3D11DeviceContext*      deviceContext;
    ID3D11InputLayout*        inputLayout;
    ID3D11VertexShader*       vertexShader;
    ID3D11PixelShader*        pixelShader;
    ID3D11Buffer*             constantBuffer;
    ID3D11RasterizerState*    rasterizerState;
    ID3D11DepthStencilState*  depthStencilState;
    DeviceRecources()
    {
        CreateDeviceAndDeviceContext();
        #ifdef DEBUG_BUILD
        EnableDebug();
        #endif
        CompileShadersAndInputs();
        CreateConstantBuffer();
        CreateRasterizerState();
        CreateDepthStencilState();

        deviceContext->RSSetState(rasterizerState);
        deviceContext->OMSetDepthStencilState(depthStencilState, 0);
        deviceContext->VSSetShader(vertexShader, nullptr, 0);
        deviceContext->PSSetShader(pixelShader, nullptr, 0);
        deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        deviceContext->IASetInputLayout(inputLayout);
    }
    void CreateDeviceAndDeviceContext()
    {
        D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
        UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

        #if defined(DEBUG_BUILD)
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif

        HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
                                            0, creationFlags,
                                            featureLevels, ARRAYSIZE(featureLevels),
                                            D3D11_SDK_VERSION, &device, 0, &deviceContext);
        assert(SUCCEEDED(hResult));
    }
    void EnableDebug()
    {
        ID3D11Debug *d3dDebug = nullptr;
        device->QueryInterface(__uuidof(ID3D11Debug), (void**)&d3dDebug);
        if (d3dDebug)
        {
            ID3D11InfoQueue *d3dInfoQueue = nullptr;
            if (SUCCEEDED(d3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue)))
            {
                d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
                d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
                d3dInfoQueue->Release();
            }
            d3dDebug->Release();
        }
    }
    void CompileShadersAndInputs()
    {
        UINT shaderCompileFlags = 0;
        // Compiling with this flag allows debugging shaders with Visual Studio
        #if defined(DEBUG_BUILD)
        shaderCompileFlags |= D3DCOMPILE_DEBUG;
        #endif

        ID3DBlob* vsBlob;
        ID3DBlob* psBlob;
        ID3DBlob* shaderCompileErrorsBlob;

        auto fileName = L"shaders.hlsl";

        assert(FileExists(fileName));

        {
            HRESULT hResult = D3DCompileFromFile(fileName, nullptr, nullptr, "vs_main", "vs_5_0", shaderCompileFlags, 0, &vsBlob, &shaderCompileErrorsBlob);
            if(FAILED(hResult))
            {
                const char* errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                shaderCompileErrorsBlob->Release();
                ShowMessageBox(errorString);
                assert(false);
            }

            hResult = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
            assert(SUCCEEDED(hResult));
        }

        {
            HRESULT hResult = D3DCompileFromFile(fileName, nullptr, nullptr, "ps_main", "ps_5_0", shaderCompileFlags, 0, &psBlob, &shaderCompileErrorsBlob);
            if(FAILED(hResult))
            {
                const char* errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                shaderCompileErrorsBlob->Release();
                ShowMessageBox(errorString);
                assert(false);
            }

            hResult = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
            assert(SUCCEEDED(hResult));
        }

        {
            // D3D11_INPUT_ELEMENT_DESC inputElementDesc;
            // inputElementDesc.SemanticName = "POS";
            // inputElementDesc.SemanticIndex = 0;
            // inputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            // inputElementDesc.InputSlot = 0;
            // inputElementDesc.AlignedByteOffset = 0;
            // inputElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            // inputElementDesc.InstanceDataStepRate = 0;
            D3D11_INPUT_ELEMENT_DESC inputElementDescArray[] =
            {
                { "POS",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
            };

            HRESULT hResult = device->CreateInputLayout(inputElementDescArray, ARRAYSIZE(inputElementDescArray), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
            assert(SUCCEEDED(hResult));
        }

        vsBlob->Release();
        psBlob->Release();
    }
    void CreateConstantBuffer()
    {
        D3D11_BUFFER_DESC constantBufferDesc = {};
        // ByteWidth must be a multiple of 16, per the docs
        constantBufferDesc.ByteWidth      = sizeof(Constants) + 0xf & 0xfffffff0;
        // constantBufferDesc.ByteWidth      = sizeof(Constants);
        constantBufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
        constantBufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hResult = device->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
        assert(SUCCEEDED(hResult));
    }
    void CreateRasterizerState()
    {
        D3D11_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.CullMode = D3D11_CULL_BACK;
        rasterizerDesc.FrontCounterClockwise = TRUE;
        device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
    }
    void CreateDepthStencilState()
    {
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
        depthStencilDesc.DepthEnable    = TRUE;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc      = D3D11_COMPARISON_LESS;
        device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
    }
};
DeviceRecources* DeviceRecources::instance = nullptr;