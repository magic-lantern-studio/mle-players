

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAuStage,0x86DAA0D2,0x477F,0x4A02,0x9B,0xB2,0x8D,0x4C,0x41,0x2F,0xE2,0xC9);


MIDL_DEFINE_GUID(IID, LIBID_RehearsalPlayerLib,0xD2A024F0,0x2F7C,0x47EB,0x96,0xC0,0x4E,0xEA,0x28,0xDB,0x85,0x15);


MIDL_DEFINE_GUID(IID, DIID__IAuStageEvents,0xD5DA5D83,0xBB73,0x423F,0x87,0x39,0x37,0xAF,0x9B,0x6D,0x71,0x3C);


MIDL_DEFINE_GUID(CLSID, CLSID_AuStage,0x65C00DBE,0xB4E9,0x442E,0xAF,0x68,0x51,0x38,0x87,0xFD,0xDA,0x90);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



