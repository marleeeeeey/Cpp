#include <windows.h>
#include <tchar.h>
#include <iostream>

#include <initguid.h>
#include "../AutoSvr/AutoSvr_i.h" // better to import tlb files here

void exit_program(int value)
{
    std::cin.get();
    exit(value);
}

int main(int argc, char* argv[])
{
    using namespace std;

    cout << "Initializing COM" << endl;

    if(FAILED(CoInitialize(NULL)))
    {
        cout << "Unable to initialize COM" << endl;
        exit_program(-1);
    }
    
    IClassFactory* pCF;
    HRESULT hr = CoGetClassObject(CLSID_MathCoClass,
        CLSCTX_INPROC,
        nullptr,
        IID_IClassFactory,
        (void**)&pCF);
    if(FAILED(hr))
    {
        cout.setf(ios::hex, ios::basefield);
        cout << "Failed to GetClassObject server instance. HR = " << hr << endl;
        exit_program(-1);
    }
        
    IMathATL* pMath;
    hr = pCF->CreateInstance(nullptr, IID_IMathATL, (void**)&pMath);
    pCF->Release();
    if(FAILED(hr))
    {
        cout.setf(ios::hex, ios::basefield);
        cout << "Failed to create server instance. HR = " << hr << endl;
        exit_program(-1);
    }
    cout << "Instance created" << endl;

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
