#pragma once

class ComException : public std::exception
{
public:
    ComException(HRESULT hr) noexcept : result(hr) {}

    const char* what() const noexcept override
    {
        static char s_str[64] = {};
        sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
        return s_str;
    }

private:
    HRESULT result;
};

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw ComException(hr);
    }
}