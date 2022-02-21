/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file StdAfx.h
 * @ingroup MlePlayer
 *
 * This is the include file for standard system include files,
 * or project specific include files that are used frequently,
 * but are changed infrequently.
 *
 * @author Mark S. Millard
 * @date May 5, 2003
 */

// COPYRIGHT_BEGIN
//
//  Copyright (C) 2000-2007  Wizzer Works
//
//  Wizzer Works makes available all content in this file ("Content").
//  Unless otherwise indicated below, the Content is provided to you
//  under the terms and conditions of the Common Public License Version 1.0
//  ("CPL"). A copy of the CPL is available at
//
//      http://opensource.org/licenses/cpl1.0.php
//
//  For purposes of the CPL, "Program" will mean the Content.
//
//  For information concerning this Makefile, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

#if !defined(AFX_STDAFX_H__AFDCEA0B_5868_47DE_B6EC_EAECAB26EC74__INCLUDED_)
#define AFX_STDAFX_H__AFDCEA0B_5868_47DE_B6EC_EAECAB26EC74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
#include <atlapp.h>
// You may derive a class from CComModule and use it if you want to override
// something, but do not change the name of _Module
class CExeModule : public CAppModule
{
public:
	LONG Unlock();
	DWORD dwThreadID;
	HANDLE hEventShutdown;
	void MonitorShutdown();
	bool StartMonitor();
	bool bActivity;
};
extern CExeModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <process.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AFDCEA0B_5868_47DE_B6EC_EAECAB26EC74__INCLUDED)
