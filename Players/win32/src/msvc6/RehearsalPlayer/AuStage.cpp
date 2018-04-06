/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file AuStage.cpp
 * @ingroup MlePlayer
 *
 * This file implements the class CAuStage.
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

#include "stdafx.h"
#include "RehearsalPlayer.h"
#include "AuStage.h"

/////////////////////////////////////////////////////////////////////////////
// CAuStage


LRESULT CAuStage::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//__asm int 3h;
	OutputDebugString(_T("**** CAustage: OnCreate called.\n"));

	// Create PlayerWindow window.
	m_hWndPlayer = m_view.Create(m_hWnd, rcDefault);

	// Resize window.
	SIZEL sizel;
	RECT rect;
	m_view.GetIdealRect(&rect);
	sizel.cx = rect.right;
	sizel.cy = rect.bottom;
	SetExtent(DVASPECT_CONTENT, &sizel);

	return 0;
}

/*
LRESULT CAuStage::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_view.IsWindow())
	{
		//CRect rc;
		RECT rc;
		GetClientRect(&rc);
		m_view.MoveWindow(&rc, FALSE);
	}

	bHandled = FALSE;

	return 0;
}
*/

UINT WINAPI StartPlayerThread(void* pData)
{
	//DWORD waitStatus;
	int argc = 0;
	char **argv = NULL;

	ATLASSERT(pData);

	CAuStage *stage = (CAuStage *)pData;

	//__asm int 3h;

	// Set up the argument vector for initializing the player.
	char *v[2];
	argv = v;
	argc = 2;
	argv[0] = "CAuStage";

	USES_CONVERSION;
	LPTSTR path = OLE2T(stage->m_digitalWorkprint->m_str); // Convert a BSTR to a LPTSTR.
	argv[1] = (char *)path;

	// Initialize the player.
	stage->m_view.init(argc,argv);

	stage->m_running = TRUE;

	// Execute the player.
	stage->m_view.run();

	// Clean up after the player has stopped.
	stage->m_view.terminate();

	stage->m_running = FALSE;

	return 0;
}

void InitPlayer(CAuStage *stage)
{
	int argc = 0;
	char **argv = NULL;

	char *v[2];
	argv = v;
	argc = 2;
	argv[0] = "CAuStage";

	USES_CONVERSION;
	LPTSTR path = OLE2T(stage->m_digitalWorkprint->m_str); // Convert a BSTR to a LPTSTR.
	argv[1] = (char *)path;

	// Initialize the player.
	stage->m_view.init(argc,argv);
}


STDMETHODIMP CAuStage::setDigitalWorkprint(BSTR dwp)
{
	// XXX - Make sure that the DWP is in its canonical form.

	//__asm int 3h;
	//DebugBreak();

	if (m_digitalWorkprint)
		delete m_digitalWorkprint;
	m_digitalWorkprint = new CComBSTR(dwp);
	//m_digitalWorkprint = new CComVariant(dwp);

	return S_OK;
}

UINT g_uThreadId = 0;

STDMETHODIMP CAuStage::init(BSTR cmdline)
{
	HRESULT status = E_FAIL;
	LPCTSTR pCwd = NULL;

	//__asm int 3h;

	// Fail if the digital workprint has not been initialized.
	if (! m_digitalWorkprint)
	{
		// XXX - Return something useful using SetError()
		return status;
	}

	// Parse command line.
	USES_CONVERSION;
	LPCWSTR pCommand = OLE2W(cmdline); // Convert a BSTR to a LPCWSTR.

	int nArgs = 0;
	LPWSTR* pArgs = CommandLineToArgvW(pCommand, &nArgs);
	for (int i = 0; i < nArgs; i++)
	{
		if (wcsicmp(pArgs[i], L"-cwd") == 0)
		{
			pCwd = W2T(pArgs[i+1]);
		}
	}

	// Set the current working directory.
	::SetCurrentDirectory(pCwd);

	//_beginthreadex(NULL, 0, StartPlayerThread, (void*)this, 0, &g_uThreadId);
	InitPlayer(this);

	status = S_OK;

	return status;
}

STDMETHODIMP CAuStage::run()
{
	//__asm int 3h;

	// Execute the player.
	m_view.update();

	//UINT uThreadId = 0;
	//_beginthreadex(NULL, 0, StartPlayerThread, (void*)this, 0, &uThreadId);
	return S_OK;
}

STDMETHODIMP CAuStage::cleanup()
{
	// Clean up after the player has stopped.
	m_view.terminate();

	return S_OK;
}

STDMETHODIMP CAuStage::isRunning(BOOL* running)
{
	*running = m_running;

	return S_OK;
}

STDMETHODIMP CAuStage::startPlayer(BSTR cmdline)
{
	HRESULT status = E_FAIL;
	LPCTSTR pCwd = NULL;

	//__asm int 3h;

	// Fail if the digital workprint has not been initialized.
	if (! m_digitalWorkprint)
	{
		// XXX - Return something useful using SetError()
		return status;
	}

	// Parse command line.
	USES_CONVERSION;
	LPCWSTR pCommand = OLE2W(cmdline); // Convert a BSTR to a LPCWSTR.

	int nArgs = 0;
	LPWSTR* pArgs = CommandLineToArgvW(pCommand, &nArgs);
	for (int i = 0; i < nArgs; i++)
	{
		if (wcsicmp(pArgs[i], L"-cwd") == 0)
		{
			pCwd = W2T(pArgs[i+1]);
		}
	}

	// Set the current working directory.
	::SetCurrentDirectory(pCwd);

	_beginthreadex(NULL, 0, StartPlayerThread, (void*)this, 0, &g_uThreadId);

	status = S_OK;

	return status;
}
