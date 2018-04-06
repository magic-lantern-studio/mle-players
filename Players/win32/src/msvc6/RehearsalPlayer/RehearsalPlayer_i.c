/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri May 28 16:26:54 2010
 */
/* Compiler settings for M:\projects\MagicLantern\Players\MlePlayers\RehearsalPlayer\RehearsalPlayer.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID IID_IAuStage = {0x89CF893A,0x2A69,0x48A4,{0x91,0x4C,0xA3,0x42,0x29,0xE3,0xD1,0x60}};


const IID LIBID_REHEARSALPLAYERLib = {0x28D12139,0x7BDC,0x4D94,{0x93,0x86,0xF8,0x27,0x8A,0xA0,0xAF,0x7A}};


const CLSID CLSID_AuStage = {0xCBD3BD50,0x9710,0x4179,{0x81,0x2F,0x40,0x53,0xE7,0xBB,0x31,0x11}};


#ifdef __cplusplus
}
#endif

