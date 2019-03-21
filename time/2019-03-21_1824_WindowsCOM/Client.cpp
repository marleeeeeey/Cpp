#include <windows.h>
#include <tchar.h>
#include <iostream>

#include <initguid.h>
#include "IMath.h"

void exit_program(int value)
{
    std::cin.get();
    exit(value);
}

int main(int argc, char* argv[])
{
    using namespace std;

    cout << "Initializing COM" << endl;

    if (FAILED( CoInitialize( NULL )))
    {
        cout << "Unable to initialize COM" << endl;
        exit_program(-1);
    }

    auto szProgID = "Math.Component.1";
    WCHAR szWideProgID[128];
    CLSID clsid;
    long lLen = MultiByteToWideChar(CP_ACP,
                                    0,
                                    szProgID,
                                    strlen(szProgID),
                                    szWideProgID,
                                    sizeof szWideProgID);

    szWideProgID[lLen] = '\0';
    HRESULT hr = CLSIDFromProgID(szWideProgID, &clsid);
    if (FAILED( hr ))
    {
        cout.setf(ios::hex, ios::basefield);
        cout << "Unable to get CLSID from ProgID. HR = " << hr << endl;
        exit_program(-1);
    }

    IClassFactory* pCF;
    // Получить фабрику классов для класса Math
    hr = CoGetClassObject(clsid,
                          CLSCTX_INPROC,
                          nullptr,
                          IID_IClassFactory,
                          (void**)&pCF);
    if (FAILED( hr ))
    {
        cout.setf(ios::hex, ios::basefield);
        cout << "Failed to GetClassObject server instance. HR = " << hr << endl;
        exit_program(-1);
    }

    // с помощью фабрики классов создать экземпляр
    // компонента и получить интерфейс IUnknown.
    IUnknown* pUnk;
    hr = pCF->CreateInstance(nullptr, IID_IUnknown, (void**)&pUnk);

    // Release the class factory
    pCF->Release();

    if (FAILED( hr ))
    {
        cout.setf(ios::hex, ios::basefield);
        cout << "Failed to create server instance. HR = " << hr << endl;
        exit_program(-1);
    }

    cout << "Instance created" << endl;

    IMath* pMath = nullptr;
    hr = pUnk->QueryInterface(IID_IMath, (LPVOID*)&pMath);
    pUnk->Release();
    if (FAILED( hr ))
    {
        cout << "QueryInterface() for IMath failed" << endl;
        exit_program(-1);
    }

    long result;
    pMath->Multiply(100, 8, &result);
    cout << "100 * 8 is " << result << endl;

    pMath->Subtract(1000, 333, &result);
    cout << "1000 - 333 is " << result << endl;

    cout << "Releasing instance" << endl;
    pMath->Release();

    cout << "Shuting down COM" << endl;
    CoUninitialize();

    exit_program(0);
}
