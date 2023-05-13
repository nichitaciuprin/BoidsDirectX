
cbuffer constants : register(b0)
{
    float4x4 modelViewProj;
};

struct VS_Input
{
    float3 vertexPosition : POS;
};

struct PS_Input
{
    float4 screenSpace : SV_POSITION;
    float3 color : COLOR;
};

float4 ToScreenSpace(float3 vertexPosition, float4x4 modelViewProj)
{
    return mul(float4(vertexPosition, 1.0f), modelViewProj);
}

PS_Input vs_main(VS_Input input)
{
    PS_Input output;
    output.screenSpace = ToScreenSpace(input.vertexPosition,modelViewProj);
    output.color = input.vertexPosition;
    output.color += float3(0.5f, 0.5f, 0.5f);
    output.color = abs(output.color);
    return output;
}

float4 ps_main(PS_Input input) : SV_Target
{
    return float4(input.color, 1.0);
}
