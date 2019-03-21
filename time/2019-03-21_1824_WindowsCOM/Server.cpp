#include <windows.h>

#include "math.h"

long g_lObjs = 0;
long g_lLocks = 0;

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
    MathClassFactory* pCF = nullptr;

    // Make sure the CLSID is for our Expression component
    if (rclsid != CLSID_Math)
        return E_FAIL;

    pCF = new MathClassFactory;

    if (pCF == nullptr)
        return E_OUTOFMEMORY;

    HRESULT hr = pCF->QueryInterface(riid, ppv);

    // Check for failure of QueryInterface
    if (FAILED( hr ))
    {
        delete pCF;
        pCF = nullptr;
    }

    return hr;
}

STDAPI DllCanUnloadNow(void)
{
    if (g_lObjs || g_lLocks)
        return S_FALSE;
    return S_OK;
}
