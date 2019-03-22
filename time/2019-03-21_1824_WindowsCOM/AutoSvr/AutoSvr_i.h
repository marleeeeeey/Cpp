

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for AutoSvr.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AutoSvr_i_h__
#define __AutoSvr_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMathATL_FWD_DEFINED__
#define __IMathATL_FWD_DEFINED__
typedef interface IMathATL IMathATL;

#endif 	/* __IMathATL_FWD_DEFINED__ */


#ifndef __MathCoClass_FWD_DEFINED__
#define __MathCoClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class MathCoClass MathCoClass;
#else
typedef struct MathCoClass MathCoClass;
#endif /* __cplusplus */

#endif 	/* __MathCoClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IMathATL_INTERFACE_DEFINED__
#define __IMathATL_INTERFACE_DEFINED__

/* interface IMathATL */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IMathATL;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0584da83-b7dc-4e1e-b425-2654cc6e342a")
    IMathATL : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ long __MIDL__IMathATL0000,
            /* [in] */ long __MIDL__IMathATL0001,
            /* [retval][out] */ long *pResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Subtract( 
            /* [in] */ long __MIDL__IMathATL0002,
            /* [in] */ long __MIDL__IMathATL0003,
            /* [retval][out] */ long *pResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Multiply( 
            /* [in] */ long __MIDL__IMathATL0004,
            /* [in] */ long __MIDL__IMathATL0005,
            /* [retval][out] */ long *pResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Divide( 
            /* [in] */ long __MIDL__IMathATL0006,
            /* [in] */ long __MIDL__IMathATL0007,
            /* [retval][out] */ long *pResult) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMathATLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMathATL * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMathATL * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMathATL * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMathATL * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMathATL * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMathATL * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMathATL * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            IMathATL * This,
            /* [in] */ long __MIDL__IMathATL0000,
            /* [in] */ long __MIDL__IMathATL0001,
            /* [retval][out] */ long *pResult);
        
        HRESULT ( STDMETHODCALLTYPE *Subtract )( 
            IMathATL * This,
            /* [in] */ long __MIDL__IMathATL0002,
            /* [in] */ long __MIDL__IMathATL0003,
            /* [retval][out] */ long *pResult);
        
        HRESULT ( STDMETHODCALLTYPE *Multiply )( 
            IMathATL * This,
            /* [in] */ long __MIDL__IMathATL0004,
            /* [in] */ long __MIDL__IMathATL0005,
            /* [retval][out] */ long *pResult);
        
        HRESULT ( STDMETHODCALLTYPE *Divide )( 
            IMathATL * This,
            /* [in] */ long __MIDL__IMathATL0006,
            /* [in] */ long __MIDL__IMathATL0007,
            /* [retval][out] */ long *pResult);
        
        END_INTERFACE
    } IMathATLVtbl;

    interface IMathATL
    {
        CONST_VTBL struct IMathATLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMathATL_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMathATL_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMathATL_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMathATL_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMathATL_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMathATL_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMathATL_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMathATL_Add(This,__MIDL__IMathATL0000,__MIDL__IMathATL0001,pResult)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IMathATL0000,__MIDL__IMathATL0001,pResult) ) 

#define IMathATL_Subtract(This,__MIDL__IMathATL0002,__MIDL__IMathATL0003,pResult)	\
    ( (This)->lpVtbl -> Subtract(This,__MIDL__IMathATL0002,__MIDL__IMathATL0003,pResult) ) 

#define IMathATL_Multiply(This,__MIDL__IMathATL0004,__MIDL__IMathATL0005,pResult)	\
    ( (This)->lpVtbl -> Multiply(This,__MIDL__IMathATL0004,__MIDL__IMathATL0005,pResult) ) 

#define IMathATL_Divide(This,__MIDL__IMathATL0006,__MIDL__IMathATL0007,pResult)	\
    ( (This)->lpVtbl -> Divide(This,__MIDL__IMathATL0006,__MIDL__IMathATL0007,pResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMathATL_INTERFACE_DEFINED__ */



#ifndef __AutoSvrLib_LIBRARY_DEFINED__
#define __AutoSvrLib_LIBRARY_DEFINED__

/* library AutoSvrLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AutoSvrLib;

EXTERN_C const CLSID CLSID_MathCoClass;

#ifdef __cplusplus

class DECLSPEC_UUID("fb3ab377-0c68-4752-94e9-603b028a8858")
MathCoClass;
#endif
#endif /* __AutoSvrLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


