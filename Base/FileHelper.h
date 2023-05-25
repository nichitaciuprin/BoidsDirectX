#pragma once

wstring GetCurentDirectoryPath()
{
    wchar_t buffer[MAX_PATH] = {};
    GetCurrentDirectory(MAX_PATH, (LPWSTR)buffer);
    return wstring(buffer,sizeof(buffer));
}
wstring GetExeFilePath()
{
    wchar_t buffer[MAX_PATH] = {};
    GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);
    return wstring(buffer,sizeof(buffer));
}
void ShowMessageBox(LPCSTR lpText)
{
    MessageBoxA(nullptr, lpText, nullptr, MB_OK);
}
bool FileExists(LPCWSTR file)
{
    return GetFileAttributes(file) != INVALID_FILE_ATTRIBUTES;
}