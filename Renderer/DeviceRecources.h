#pragma once

class DeviceRecources
{
public:
    static DeviceRecources* GetInstance()
    {
        if (instance == nullptr)
            instance = new DeviceRecources();

        return instance;
    }

    ID3D11Device* GetDevice()
    {
        return device.Get();
    }
    ID3D11DeviceContext* GetDeviceContext()
    {
        return deviceContext.Get();
    }

private:
    static DeviceRecources* instance;

    ComPtr<ID3D11Device>         device;
    ComPtr<ID3D11DeviceContext>  deviceContext;

    DeviceRecources()
    {
        CreateDeviceAndDeviceContext();
        #ifdef DEBUG_BUILD
        try { EnableDebug(); } catch (...) { }
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
                                            D3D11_SDK_VERSION, device.GetAddressOf(), 0, deviceContext.GetAddressOf());

        ThrowIfFailed(hResult);
    }
    void EnableDebug()
    {
        ComPtr<ID3D11Debug> d3dDebug = nullptr;
        ThrowIfFailed(device.As(&d3dDebug));

        ComPtr<ID3D11InfoQueue> d3dInfoQueue = nullptr;
        ThrowIfFailed(d3dDebug.As(&d3dInfoQueue));

        ThrowIfFailed(d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true));
        ThrowIfFailed(d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true));
    }
};
DeviceRecources* DeviceRecources::instance = nullptr;