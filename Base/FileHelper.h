#pragma once
// void GetCurentDirectoryPath(char* result)
// {
//     wchar_t buffer[MAX_PATH] = {};
//     GetCurrentDirectoryW(MAX_PATH, (LPWSTR)buffer);

//     int i = 0;
//     while (buffer[i*2] != '\0')
//     {
//         result[i] = buffer[i*2];
//         i++;
//     }
// }
// void GetExeFilePath(char* result)
// {
//     wchar_t buffer[MAX_PATH] = {};
//     GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);

//     int i = 0;
//     while (buffer[i*2] != '\0')
//     {
//         result[i] = buffer[i*2];
//         i++;
//     }
// }
void ShowMessageBox(LPCSTR lpText)
{
    MessageBoxA(nullptr, lpText, nullptr, MB_OK);
}
bool FileExists(LPCWSTR file)
{
    return GetFileAttributes(file) != INVALID_FILE_ATTRIBUTES;
}