struct DeviceRecources // Singleton
{
    ID3D11Device*             device;
    ID3D11DeviceContext*      deviceContext;
    ID3D11InputLayout*        inputLayout;
    ID3D11VertexShader*       vertexShader;
    ID3D11PixelShader*        pixelShader;
    ID3D11Buffer*             constantBuffer;
    ID3D11RasterizerState*    rasterizerState;
    ID3D11DepthStencilState*  depthStencilState;
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
struct PrimitiveModel
{
    UINT indexCount;
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
};