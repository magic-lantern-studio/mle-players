// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2000-2025 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  For information concerning this source file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

// AuStage.cpp : Implementation of CAuStage
#include "stdafx.h"
#include "AuStage.h"

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
	argv[1] = T2A(path); // Use ATL T2A to convert to char *.

	// Initialize the player.
	stage->m_view.init(argc,argv);
}

// CAuStage

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

STDMETHODIMP CAuStage::run(void)
{
	//__asm int 3h;

	// Execute the player.
	m_view.update();

	//UINT uThreadId = 0;
	//_beginthreadex(NULL, 0, StartPlayerThread, (void*)this, 0, &uThreadId);
	return S_OK;
}

STDMETHODIMP CAuStage::cleanup(void)
{
	// Clean up after the player has stopped.
	m_view.terminate();

	return S_OK;
}

STDMETHODIMP CAuStage::isRunning(BOOL * running)
{
	*running = m_running;

	return S_OK;
}

STDMETHODIMP CAuStage::setDigitalWorkprint(BSTR dwp)
{
	// XXX - Make sure that the DWP is in its canonical form.

	//__asm int 3h;
	//DebugBreak();

	if (m_digitalWorkprint)
		delete m_digitalWorkprint;
	m_digitalWorkprint = new CComBSTR(dwp);

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

LRESULT CAuStage::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
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
