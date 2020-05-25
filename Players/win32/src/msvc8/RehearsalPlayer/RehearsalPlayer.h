

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Aug 31 13:33:20 2012
 */
/* Compiler settings for .\RehearsalPlayer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RehearsalPlayer_h__
#define __RehearsalPlayer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAuStage_FWD_DEFINED__
#define __IAuStage_FWD_DEFINED__
typedef interface IAuStage IAuStage;
#endif 	/* __IAuStage_FWD_DEFINED__ */


#ifndef ___IAuStageEvents_FWD_DEFINED__
#define ___IAuStageEvents_FWD_DEFINED__
typedef interface _IAuStageEvents _IAuStageEvents;
#endif 	/* ___IAuStageEvents_FWD_DEFINED__ */


#ifndef __AuStage_FWD_DEFINED__
#define __AuStage_FWD_DEFINED__

#ifdef __cplusplus
typedef class AuStage AuStage;
#else
typedef struct AuStage AuStage;
#endif /* __cplusplus */

#endif 	/* __AuStage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IAuStage_INTERFACE_DEFINED__
#define __IAuStage_INTERFACE_DEFINED__

/* interface IAuStage */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAuStage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86DAA0D2-477F-4A02-9BB2-8D4C412FE2C9")
    IAuStage : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_HWND( 
            /* [retval][out] */ LONG_PTR *pHWND) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE init( 
            /* [in] */ BSTR cmdline) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE run( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE cleanup( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isRunning( 
            /* [out] */ BOOL *running) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setDigitalWorkprint( 
            /* [in] */ BSTR dwp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE startPlayer( 
            /* [in] */ BSTR cmdline) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAuStageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAuStage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAuStage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAuStage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAuStage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAuStage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAuStage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAuStage * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HWND )( 
            IAuStage * This,
            /* [retval][out] */ LONG_PTR *pHWND);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *init )( 
            IAuStage * This,
            /* [in] */ BSTR cmdline);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *run )( 
            IAuStage * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *cleanup )( 
            IAuStage * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isRunning )( 
            IAuStage * This,
            /* [out] */ BOOL *running);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setDigitalWorkprint )( 
            IAuStage * This,
            /* [in] */ BSTR dwp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *startPlayer )( 
            IAuStage * This,
            /* [in] */ BSTR cmdline);
        
        END_INTERFACE
    } IAuStageVtbl;

    interface IAuStage
    {
        CONST_VTBL struct IAuStageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAuStage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAuStage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAuStage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAuStage_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAuStage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAuStage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAuStage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAuStage_get_HWND(This,pHWND)	\
    (This)->lpVtbl -> get_HWND(This,pHWND)

#define IAuStage_init(This,cmdline)	\
    (This)->lpVtbl -> init(This,cmdline)

#define IAuStage_run(This)	\
    (This)->lpVtbl -> run(This)

#define IAuStage_cleanup(This)	\
    (This)->lpVtbl -> cleanup(This)

#define IAuStage_isRunning(This,running)	\
    (This)->lpVtbl -> isRunning(This,running)

#define IAuStage_setDigitalWorkprint(This,dwp)	\
    (This)->lpVtbl -> setDigitalWorkprint(This,dwp)

#define IAuStage_startPlayer(This,cmdline)	\
    (This)->lpVtbl -> startPlayer(This,cmdline)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IAuStage_get_HWND_Proxy( 
    IAuStage * This,
    /* [retval][out] */ LONG_PTR *pHWND);


void __RPC_STUB IAuStage_get_HWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_init_Proxy( 
    IAuStage * This,
    /* [in] */ BSTR cmdline);


void __RPC_STUB IAuStage_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_run_Proxy( 
    IAuStage * This);


void __RPC_STUB IAuStage_run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_cleanup_Proxy( 
    IAuStage * This);


void __RPC_STUB IAuStage_cleanup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_isRunning_Proxy( 
    IAuStage * This,
    /* [out] */ BOOL *running);


void __RPC_STUB IAuStage_isRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_setDigitalWorkprint_Proxy( 
    IAuStage * This,
    /* [in] */ BSTR dwp);


void __RPC_STUB IAuStage_setDigitalWorkprint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_startPlayer_Proxy( 
    IAuStage * This,
    /* [in] */ BSTR cmdline);


void __RPC_STUB IAuStage_startPlayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAuStage_INTERFACE_DEFINED__ */



#ifndef __RehearsalPlayerLib_LIBRARY_DEFINED__
#define __RehearsalPlayerLib_LIBRARY_DEFINED__

/* library RehearsalPlayerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RehearsalPlayerLib;

#ifndef ___IAuStageEvents_DISPINTERFACE_DEFINED__
#define ___IAuStageEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAuStageEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAuStageEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D5DA5D83-BB73-423F-8739-37AF9B6D713C")
    _IAuStageEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAuStageEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAuStageEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAuStageEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAuStageEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAuStageEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAuStageEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAuStageEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAuStageEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IAuStageEventsVtbl;

    interface _IAuStageEvents
    {
        CONST_VTBL struct _IAuStageEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAuStageEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IAuStageEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IAuStageEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IAuStageEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IAuStageEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IAuStageEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IAuStageEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAuStageEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AuStage;

#ifdef __cplusplus

class DECLSPEC_UUID("65C00DBE-B4E9-442E-AF68-513887FDDA90")
AuStage;
#endif
#endif /* __RehearsalPlayerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


