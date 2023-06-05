#pragma once

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

private:
    static DeviceRecources*   instance;

    ID3D11Device*             device;
    ID3D11DeviceContext*      deviceContext;

    DeviceRecources()
    {
        CreateDeviceAndDeviceContext();
        #ifdef DEBUG_BUILD
        EnableDebug();
        #endif
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
};
DeviceRecources* DeviceRecources::instance = nullptr;