/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri May 28 16:26:54 2010
 */
/* Compiler settings for M:\projects\MagicLantern\Players\MlePlayers\RehearsalPlayer\RehearsalPlayer.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


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

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAuStage_FWD_DEFINED__
#define __IAuStage_FWD_DEFINED__
typedef interface IAuStage IAuStage;
#endif 	/* __IAuStage_FWD_DEFINED__ */


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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAuStage_INTERFACE_DEFINED__
#define __IAuStage_INTERFACE_DEFINED__

/* interface IAuStage */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAuStage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("89CF893A-2A69-48A4-914C-A34229E3D160")
    IAuStage : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE init( 
            /* [in] */ BSTR cmdline) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE run( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE cleanup( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isRunning( 
            /* [out] */ BOOL __RPC_FAR *running) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setDigitalWorkprint( 
            /* [in] */ BSTR dwp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE startPlayer( 
            /* [in] */ BSTR cmdline) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAuStageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAuStage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAuStage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAuStage __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAuStage __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAuStage __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAuStage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAuStage __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IAuStage __RPC_FAR * This,
            /* [in] */ BSTR cmdline);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *run )( 
            IAuStage __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *cleanup )( 
            IAuStage __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isRunning )( 
            IAuStage __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *running);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setDigitalWorkprint )( 
            IAuStage __RPC_FAR * This,
            /* [in] */ BSTR dwp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *startPlayer )( 
            IAuStage __RPC_FAR * This,
            /* [in] */ BSTR cmdline);
        
        END_INTERFACE
    } IAuStageVtbl;

    interface IAuStage
    {
        CONST_VTBL struct IAuStageVtbl __RPC_FAR *lpVtbl;
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



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_init_Proxy( 
    IAuStage __RPC_FAR * This,
    /* [in] */ BSTR cmdline);


void __RPC_STUB IAuStage_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_run_Proxy( 
    IAuStage __RPC_FAR * This);


void __RPC_STUB IAuStage_run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_cleanup_Proxy( 
    IAuStage __RPC_FAR * This);


void __RPC_STUB IAuStage_cleanup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_isRunning_Proxy( 
    IAuStage __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *running);


void __RPC_STUB IAuStage_isRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_setDigitalWorkprint_Proxy( 
    IAuStage __RPC_FAR * This,
    /* [in] */ BSTR dwp);


void __RPC_STUB IAuStage_setDigitalWorkprint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAuStage_startPlayer_Proxy( 
    IAuStage __RPC_FAR * This,
    /* [in] */ BSTR cmdline);


void __RPC_STUB IAuStage_startPlayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAuStage_INTERFACE_DEFINED__ */



#ifndef __REHEARSALPLAYERLib_LIBRARY_DEFINED__
#define __REHEARSALPLAYERLib_LIBRARY_DEFINED__

/* library REHEARSALPLAYERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_REHEARSALPLAYERLib;

EXTERN_C const CLSID CLSID_AuStage;

#ifdef __cplusplus

class DECLSPEC_UUID("CBD3BD50-9710-4179-812F-4053E7BB3111")
AuStage;
#endif
#endif /* __REHEARSALPLAYERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
