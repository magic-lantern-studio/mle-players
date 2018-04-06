/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file RehearsalPlayerTest.cpp
 * @ingroup MlePlayer
 *
 * This file defines the entry point for the application.
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

// AtlAxWinInit is implemented in Atl.dll
#pragma comment(lib, "atl.lib")
#include <atldef.h>
#define _ATL_DLL_IMPL
#include <atliface.h> 

#include "mle/MleWin32Path.h"

#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL InitInstance(HINSTANCE, int);

// The top-level shell window.
HWND g_hWnd;
HWND g_hWndStage;
// The Rehearsal Player component.
IDispatch *g_pIDispatch;

/*
 * AnsiToUnicode converts the ANSI string pszA to a Unicode string
 * and returns the Unicode string through ppszW. Space for the
 * the converted string is allocated by AnsiToUnicode.
 */ 

HRESULT __fastcall AnsiToUnicode(LPCSTR pszA, LPOLESTR* ppszW)
{

    ULONG cCharacters;
    DWORD dwError;

    // If input is null then just return the same.
    if (NULL == pszA)
    {
        *ppszW = NULL;
        return NOERROR;
    }

    // Determine number of wide characters to be allocated for the
    // Unicode string.
    cCharacters =  strlen(pszA)+1;

    // Use of the OLE allocator is required if the resultant Unicode
    // string will be passed to another COM component and if that
    // component will free it. Otherwise you can use your own allocator.
    *ppszW = (LPOLESTR) CoTaskMemAlloc(cCharacters*2);
    if (NULL == *ppszW)
        return E_OUTOFMEMORY;

    // Covert to Unicode.
    if (0 == MultiByteToWideChar(CP_ACP, 0, pszA, cCharacters,
                  *ppszW, cCharacters))
    {
        dwError = GetLastError();
        CoTaskMemFree(*ppszW);
        *ppszW = NULL;
        return HRESULT_FROM_WIN32(dwError);
    }

    return NOERROR;
}

int InitPlayer()
{
	HRESULT hr;

	// Get the DISPID for the dispatch function "init".
	DISPID dispid;
	OLECHAR *initPlayer = L"init";
	hr = g_pIDispatch->GetIDsOfNames(
		IID_NULL,				// Must be IID_NULL.
		&initPlayer,			// Name of function.
		1,						// Number of names.
		GetUserDefaultLCID(),	// Localization info.
		&dispid);				// Dispatch ID.
	if (FAILED( hr ))
	{
		cout.setf( ios::hex, ios::basefield );
		cout << "Failed to find init(). HR = " << hr << endl;
		return FALSE;
	}

	// Prepare the arguments for "init".
	//OLECHAR *cmds = L"-cwd C:\\Users\\msm\\projects\\MagicLantern\\titles\\mtea\\src";
	OLECHAR *cmds = L"-cwd M:\\projects\\MagicLantern\\titles\\mtea\\src";
	BSTR cmdline = ::SysAllocString(cmds);

	// Allocate and initialize a VARIANT argument.
	VARIANTARG varg;
	::VariantInit(&varg);
	varg.vt = VT_BSTR;
	varg.bstrVal = cmdline;

	// Fill in the DISPPARAMS structure.
	DISPPARAMS initArgs = {
		&varg,					// Array of arguments.
		NULL,					// DISPIDs of named arguments.
		1,						// Number of arguments.
		0						// Number of named arguments.
	};

	// Invoke "init".
	EXCEPINFO excepinfo;
	hr = g_pIDispatch->Invoke(
		dispid,					// DISPID.
		IID_NULL,				// Must be IID_NULL.
		GetUserDefaultLCID(),	// Localization info.
		DISPATCH_METHOD,		// Method.
		&initArgs,				// Method arguments.
		NULL,					// Results.
		&excepinfo,				// Exception.
		NULL);					// ARg error.
	if (FAILED( hr ))
	{
		// Invoke failed.
		if (hr == DISP_E_EXCEPTION)
		{
			// Method raised an exception.

			// Server can defer filling EXCEPINFO, so fill it in.
			if (excepinfo.pfnDeferredFillIn != NULL)
			{
				// Fill the EXCEPINFO structure.
				(*(excepinfo.pfnDeferredFillIn))(&excepinfo);
			}
			strstream sout;
			sout << "Exception information from component:"    << endl
				 << "  Source:       " << excepinfo.bstrSource << endl
				 << "  Description:  " << excepinfo.bstrDescription
				 << ends;
			//trace(sout.str());
		}
	}

	::VariantClear(&varg);

	return TRUE;
}

int ExecutePlayerCycle()
{
	HRESULT hr;

	// Get the DISPID for the dispatch function "run".
	DISPID dispid;
	OLECHAR *runPlayer = L"run";
	hr = g_pIDispatch->GetIDsOfNames(
		IID_NULL,				// Must be IID_NULL.
		&runPlayer,			// Name of function.
		1,						// Number of names.
		GetUserDefaultLCID(),	// Localization info.
		&dispid);				// Dispatch ID.
	if (FAILED( hr ))
	{
		cout.setf( ios::hex, ios::basefield );
		cout << "Failed to find run(). HR = " << hr << endl;
		return FALSE;
	}

	// Fill in the DISPPARAMS structure.
	DISPPARAMS runArgs = {
		NULL,					// Array of arguments.
		NULL,					// DISPIDs of named arguments.
		0,						// Number of arguments.
		0						// Number of named arguments.
	};

	// Invoke "run".
	EXCEPINFO excepinfo;
	hr = g_pIDispatch->Invoke(
		dispid,					// DISPID.
		IID_NULL,				// Must be IID_NULL.
		GetUserDefaultLCID(),	// Localization info.
		DISPATCH_METHOD,		// Method.
		&runArgs,				// Method arguments.
		NULL,					// Results.
		&excepinfo,				// Exception.
		NULL);					// ARg error.
	if (FAILED( hr ))
	{
		// Invoke failed.
		if (hr == DISP_E_EXCEPTION)
		{
			// Method raised an exception.

			// Server can defer filling EXCEPINFO, so fill it in.
			if (excepinfo.pfnDeferredFillIn != NULL)
			{
				// Fill the EXCEPINFO structure.
				(*(excepinfo.pfnDeferredFillIn))(&excepinfo);
			}
			strstream sout;
			sout << "Exception information from component:"    << endl
				 << "  Source:       " << excepinfo.bstrSource << endl
				 << "  Description:  " << excepinfo.bstrDescription
				 << ends;
			//trace(sout.str());
		}
	}

	return TRUE;
}

int CleanupPlayer()
{
	HRESULT hr;

	// Get the DISPID for the dispatch function "terminate".
	DISPID dispid;
	OLECHAR *cleanupPlayer = L"cleanup";
	hr = g_pIDispatch->GetIDsOfNames(
		IID_NULL,				// Must be IID_NULL.
		&cleanupPlayer,			// Name of function.
		1,						// Number of names.
		GetUserDefaultLCID(),	// Localization info.
		&dispid);				// Dispatch ID.
	if (FAILED( hr ))
	{
		cout.setf( ios::hex, ios::basefield );
		cout << "Failed to find run(). HR = " << hr << endl;
		return FALSE;
	}

	// Fill in the DISPPARAMS structure.
	DISPPARAMS terminateArgs = {
		NULL,					// Array of arguments.
		NULL,					// DISPIDs of named arguments.
		0,						// Number of arguments.
		0						// Number of named arguments.
	};

	// Invoke "run".
	EXCEPINFO excepinfo;
	hr = g_pIDispatch->Invoke(
		dispid,					// DISPID.
		IID_NULL,				// Must be IID_NULL.
		GetUserDefaultLCID(),	// Localization info.
		DISPATCH_METHOD,		// Method.
		&terminateArgs,			// Method arguments.
		NULL,					// Results.
		&excepinfo,				// Exception.
		NULL);					// ARg error.
	if (FAILED( hr ))
	{
		// Invoke failed.
		if (hr == DISP_E_EXCEPTION)
		{
			// Method raised an exception.

			// Server can defer filling EXCEPINFO, so fill it in.
			if (excepinfo.pfnDeferredFillIn != NULL)
			{
				// Fill the EXCEPINFO structure.
				(*(excepinfo.pfnDeferredFillIn))(&excepinfo);
			}
			strstream sout;
			sout << "Exception information from component:"    << endl
				 << "  Source:       " << excepinfo.bstrSource << endl
				 << "  Description:  " << excepinfo.bstrDescription
				 << ends;
			//trace(sout.str());
		}
	}

	return TRUE;
}

int StartPlayer()
{
	HRESULT hr;

	// Get the DISPID for the dispatch function "startPlayer".
	DISPID dispid;
	OLECHAR *startPlayer = L"startPlayer";
	hr = g_pIDispatch->GetIDsOfNames(
		IID_NULL,				// Must be IID_NULL.
		&startPlayer,			// Name of function.
		1,						// Number of names.
		GetUserDefaultLCID(),	// Localization info.
		&dispid);				// Dispatch ID.
	if (FAILED( hr ))
	{
		cout.setf( ios::hex, ios::basefield );
		cout << "Failed to find init(). HR = " << hr << endl;
		return FALSE;
	}

	// Prepare the arguments for "init".
	//OLECHAR *cmds = L"-cwd C:\\Users\\msm\\projects\\MagicLantern\\titles\\mtea\\src";
	OLECHAR *cmds = L"-cwd M:\\projects\\MagicLantern\\titles\\mtea\\src";
	BSTR cmdline = ::SysAllocString(cmds);

	// Allocate and initialize a VARIANT argument.
	VARIANTARG varg;
	::VariantInit(&varg);
	varg.vt = VT_BSTR;
	varg.bstrVal = cmdline;

	// Fill in the DISPPARAMS structure.
	DISPPARAMS startPlayerArgs = {
		&varg,					// Array of arguments.
		NULL,					// DISPIDs of named arguments.
		1,						// Number of arguments.
		0						// Number of named arguments.
	};

	// Invoke "init".
	EXCEPINFO excepinfo;
	hr = g_pIDispatch->Invoke(
		dispid,					// DISPID.
		IID_NULL,				// Must be IID_NULL.
		GetUserDefaultLCID(),	// Localization info.
		DISPATCH_METHOD,		// Method.
		&startPlayerArgs,		// Method arguments.
		NULL,					// Results.
		&excepinfo,				// Exception.
		NULL);					// ARg error.
	if (FAILED( hr ))
	{
		// Invoke failed.
		if (hr == DISP_E_EXCEPTION)
		{
			// Method raised an exception.

			// Server can defer filling EXCEPINFO, so fill it in.
			if (excepinfo.pfnDeferredFillIn != NULL)
			{
				// Fill the EXCEPINFO structure.
				(*(excepinfo.pfnDeferredFillIn))(&excepinfo);
			}
			strstream sout;
			sout << "Exception information from component:"    << endl
				 << "  Source:       " << excepinfo.bstrSource << endl
				 << "  Description:  " << excepinfo.bstrDescription
				 << ends;
			//trace(sout.str());
		}
	}

	::VariantClear(&varg);

	return TRUE;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	//Initialize ATL control containment code.
    AtlAxWinInit(); 

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_REHEARSALPLAYERTEST, szWindowClass, MAX_LOADSTRING);

	// Initialize and register the window class.
	WNDCLASSEX wndclass;

	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szWindowClass;
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	// Create the window.
	g_hWnd = CreateWindow(
		szWindowClass,				// Window class name.
		szTitle,					// Window caption.
		WS_OVERLAPPEDWINDOW,		// Window style.
		CW_USEDEFAULT,				// Initial x position.
		CW_USEDEFAULT,				// Initial y position.
		640,						// Initial x size,
		480,						// Initial y size,
		NULL,						// Parent window handle.
		NULL,						// Window menu handle.
		hInstance,					// Program instance handle.
		NULL);						// Creation parameters.

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDR_REHEARSALPLAYERTEST);

	// Initialize the player.
	InitPlayer();

	// Main message loop.
	for(;;)
	{
		while ((PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) != 0))
		{
			if (GetMessage(&msg, NULL, 0, 0)) 
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			} else goto quit;
		}

		// Execute one cycle of the player.
		ExecutePlayerCycle();
	}

quit:

	// Clean up.
	CleanupPlayer();

	return (int) msg.wParam;
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT hr;

	// Initialize the OLE  library.
	cout << "Initializing OLE" << endl;
	if (FAILED(::OleInitialize( NULL )))
	{
		cout << "Unable to initialize OLE" << endl;
		return FALSE;
	}

	// Create the ActiveX control specifying the ProgID.
    // Make sure the module handle you pass to CreateWindow is the same
    // module handle where AtlAxWinInit() was called from.
    g_hWndStage = ::CreateWindow(
		"AtlAxWin",
		"RehearsalPlayer.AuStage",
        WS_CHILD | WS_VISIBLE,
		0, 0,
		640, 480,
		g_hWnd,
		NULL,
        ::GetModuleHandle(NULL),
		NULL);

	ShowWindow(g_hWndStage,nCmdShow);
	UpdateWindow(g_hWndStage);

	// Retrieve the IUnknown from the window.
	IUnknown *control;
	AtlAxGetControl(g_hWndStage, &control);

	// Retrieve the IDispatch from the control.
	hr = control->QueryInterface(IID_IDispatch,(void**) &g_pIDispatch);

	// Get the DISPID for the dispatch function "setDigitalWorkprint".
	DISPID dispid;
	OLECHAR *setDigitalWorkprint = L"setDigitalWorkprint";
	hr = g_pIDispatch->GetIDsOfNames(
		IID_NULL,				// Must be IID_NULL.
		&setDigitalWorkprint,	// Name of function.
		1,						// Number of names.
		GetUserDefaultLCID(),	// Localization info.
		&dispid);				// Dispatch ID.
	if (FAILED( hr ))
	{
		cout.setf( ios::hex, ios::basefield );
		cout << "Failed to find setDigitalWorkprint(). HR = " << hr << endl;
		return FALSE;
	}

	// Define the DWP in its canonical form.
	//const MlChar *file = (const MlChar *)"C:\\Users\\msm\\projects\\MagicLantern\\Titles\\mtea\\src\\mtea.dwp";
	const MlChar *file = (const MlChar *)"M:\\projects\\MagicLantern\\Titles\\mtea\\src\\mtea.dwp";
	MleWin32Path *path = new MleWin32Path(file,true);

	LPOLESTR workprint;
	AnsiToUnicode((LPCSTR)path->getPath(),&workprint);
	BSTR dwp = ::SysAllocString(workprint);

	// Prepare the arguments for "setDigitalWorkprint".

	// Allocate and initialize a VARIANT argument.
	VARIANTARG varg;
	::VariantInit(&varg);
	varg.vt = VT_BSTR;
	varg.bstrVal = dwp;

	// Fill in the DISPPARAMS structure.
	DISPPARAMS setDigitalWorkprintArgs = {
		&varg,						// Array of arguments.
		NULL,						// DISPIDs of named arguments.
		1,							// Number of arguments.
		0							// Number of named arguments.
	};

	// Invoke "setDigitalWorkprint".
	EXCEPINFO excepinfo;
	hr = g_pIDispatch->Invoke(
		dispid,						// DISPID.
		IID_NULL,					// Must be IID_NULL.
		GetUserDefaultLCID(),		// Localization info.
		DISPATCH_METHOD,			// Method.
		&setDigitalWorkprintArgs,	// Methd arguments.
		NULL,						// Results.
		&excepinfo,					// Exception.
		NULL);						// ARg error.
	if (FAILED( hr ))
	{
		// Invoke failed.
		if (hr == DISP_E_EXCEPTION)
		{
			// Method raised an exception.

			// Server can defer filling EXCEPINFO, so fill it in.
			if (excepinfo.pfnDeferredFillIn != NULL)
			{
				// Fill the EXCEPINFO structure.
				(*(excepinfo.pfnDeferredFillIn))(&excepinfo);
			}
			strstream sout;
			sout << "Exception information from component:"    << endl
				 << "  Source:       " << excepinfo.bstrSource << endl
				 << "  Description:  " << excepinfo.bstrDescription
				 << ends;
			//trace(sout.str());
		}
		return FALSE;
	}

	// Clean up.
	::VariantClear(&varg);

	return TRUE;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			::MoveWindow(g_hWndStage, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
			return 0;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
