struct DeviceRecources // Singleton
{
    ID3D11Device*             device;
    ID3D11DeviceContext*      deviceContext;
    ID3D11InputLayout*        inputLayout;
    ID3D11VertexShader*       vertexShader;
    ID3D11PixelShader*        pixelShader;
    ID3D11RasterizerState*    rasterizerState;
    ID3D11DepthStencilState*  depthStencilState;

    UINT                      indexCountCube;
    ID3D11Buffer*             vertexBufferCube;
    ID3D11Buffer*             indexBufferCube;

    ID3D11Buffer*             constantBuffer;
};
struct Window
{
    HWND hwnd;
    int width;
    int height;
    bool windowClosed;
    IDXGISwapChain1* swapChain;
    ID3D11RenderTargetView* renderTargetView;
    ID3D11DepthStencilView* depthStencilView;
};
