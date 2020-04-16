#include "ComLib.h"
#include <shobjidl.h> // CoInitializeEx
#include <atlbase.h>  // Contains the declaration of CComPtr.


void ComLib::ShowFileOpenDialog()
{
    throw_if_fail(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE));

    CComPtr<IFileOpenDialog> pFileOpen;
    throw_if_fail(CoCreateInstance(__uuidof(FileOpenDialog), NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileOpen)));
    auto hrIsFileOpened = pFileOpen->Show(NULL);

    if (SUCCEEDED(hrIsFileOpened))
    {
        CComPtr<IShellItem> pItem;
        throw_if_fail(pFileOpen->GetResult(&pItem));

        PWSTR pszFilePath;
        throw_if_fail(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath));

        MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
        CoTaskMemFree(pszFilePath);
    }

    CoUninitialize();
}
