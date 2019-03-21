#include <windows.h>
#include "math.h"

//
// Math class implementation
//
// Constructors
Math::Math()
{
    m_lRef = 0;

    // Увеличить значение внешнего счетчика объектов
    InterlockedIncrement(&g_lObjs);
}

// The destructor
Math::~Math()
{
    // Уменьшить значение внешнего счетчика объектов
    InterlockedDecrement(&g_lObjs);
}

STDMETHODIMP Math::QueryInterface(REFIID riid, void** ppv)
{
    *ppv = nullptr;

    if (riid == IID_IUnknown || riid == IID_IMath)
        *ppv = this;

    if (*ppv)
    {
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) Math::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}

STDMETHODIMP_(ULONG) Math::Release()
{
    if (InterlockedDecrement(&m_lRef) == 0)
    {
        delete this;
        return 0;
    }

    return m_lRef;
}

STDMETHODIMP Math::Add(long lOp1, long lOp2, long* pResult)
{
    *pResult = lOp1 + lOp2;
    return S_OK;
}

STDMETHODIMP Math::Subtract(long lOp1, long lOp2, long* pResult)
{
    *pResult = lOp1 - lOp2;
    return S_OK;
}

STDMETHODIMP Math::Multiply(long lOp1, long lOp2, long* pResult)
{
    *pResult = lOp1 * lOp2;
    return S_OK;
}

STDMETHODIMP Math::Divide(long lOp1, long lOp2, long* pResult)
{
    *pResult = lOp1 / lOp2;
    return S_OK;
}

MathClassFactory::MathClassFactory()
{
    m_lRef = 0;
}

MathClassFactory::~MathClassFactory()
{
}

STDMETHODIMP MathClassFactory::QueryInterface(REFIID riid, void** ppv)
{
    *ppv = nullptr;

    if (riid == IID_IUnknown || riid == IID_IClassFactory)
        *ppv = this;

    if (*ppv)
    {
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) MathClassFactory::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}

STDMETHODIMP_(ULONG) MathClassFactory::Release()
{
    if (InterlockedDecrement(&m_lRef) == 0)
    {
        delete this;
        return 0;
    }

    return m_lRef;
}

STDMETHODIMP MathClassFactory::CreateInstance
(LPUNKNOWN pUnkOuter, REFIID riid, void** ppvObj)
{
    *ppvObj = nullptr;

    Math* pMath = new Math;

    if (pMath == nullptr)
        return E_OUTOFMEMORY;

    HRESULT hr = pMath->QueryInterface(riid, ppvObj);

    if (FAILED( hr ))
        delete pMath;

    return hr;
}

STDMETHODIMP MathClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        InterlockedIncrement(&g_lLocks);
    else
        InterlockedDecrement(&g_lLocks);

    return S_OK;
}
