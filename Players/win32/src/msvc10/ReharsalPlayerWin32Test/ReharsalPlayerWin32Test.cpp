// ReharsalPlayerWin32Test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ReharsalPlayerWin32Test.h"
#include "mle/MleWin32Path.h"

#include <iostream>
#include <strstream>
using namespace std;

// AtlAxWinInit is implemented in Atl.dll.
//#pragma comment(lib, "atl.lib")
#include <atldef.h>
#define _ATL_DLL_IMPL
#include <atliface.h>
#include <atlwin.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// The top-level shell window.
HWND g_hWnd;
HWND g_hWndStage;
// The Rehearsal Player component.
IDispatch *g_pIDispatch;
// Path to title elements we are testing against.
char g_testHome[254];

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	//OLECHAR *cmds = L"-cwd M:\\projects\\MagicLantern\\titles\\mtea\\src";
    char cmdStr[1024];
	sprintf(cmdStr, "-cwd %s", g_testHome);
	USES_CONVERSION;
	OLECHAR *cmds = A2OLE(cmdStr);
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
	//OLECHAR *cmds = L"-cwd M:\\projects\\MagicLantern\\titles\\mtea\\src";
	char cmdStr[1024];
	sprintf(cmdStr, "-cwd %s", g_testHome);
	USES_CONVERSION;
	OLECHAR *cmds = A2OLE(cmdStr);
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

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

 	// Initialize ATL control containment code.
    AtlAxWinInit();

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_REHARSALPLAYERWIN32TEST, szWindowClass, MAX_LOADSTRING);

	// Initiialize and register the window class.
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (! InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REHARSALPLAYERWIN32TEST));

	// Initialize the player.
	InitPlayer();

	// Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REHARSALPLAYERWIN32TEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_REHARSALPLAYERWIN32TEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
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
    //HWND hWnd;
	HRESULT hr;

    hInst = hInstance; // Store instance handle in our global variable

	// Build the path to where we are testing the spinning teapot.
	char *mleHomePath = getenv("MLE_HOME");
	if (! mleHomePath)
    {
		sprintf(g_testHome, "C:\\Program Files\\WizzerWorks\\MagicLantern\\titles\\mtea\\src");
	} else
	{
		sprintf(g_testHome, "%s\\titles\\mtea\\src", mleHomePath);
	}

	// Figure the adjusted size of a window where the client area is 640x480.
	RECT adjustedSize;
	adjustedSize.bottom = 480;
	adjustedSize.right = 640;
	adjustedSize.left = 0;
	adjustedSize.top = 0;
	AdjustWindowRect(&adjustedSize, WS_OVERLAPPEDWINDOW, true);
	int width = adjustedSize.right - adjustedSize.left;
	int height = adjustedSize.bottom - adjustedSize.top;

	// Create the window.
	g_hWnd = ::CreateWindow(
		szWindowClass,				// Window class name.
		szTitle,					// Window caption.
		WS_OVERLAPPEDWINDOW,		// Window style.
		CW_USEDEFAULT,				// Initial x position.
		CW_USEDEFAULT,				// Initial y position.
		width,						// Initial x size,
		height,						// Initial y size,
		NULL,						// Parent window handle.
		NULL,						// Window menu handle.
		hInstance,					// Program instance handle.
		NULL);						// Creation parameters.
    if (! g_hWnd)
    {
        return FALSE;
    }

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

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
		//L"AtlAxWin80",
		CAxWindow::GetWndClassName(),
		L"RehearsalPlayer.AuStage",
        WS_CHILD | WS_VISIBLE,
		0, 0,
		640, 480,
		g_hWnd,
		NULL,
        ::GetModuleHandle(NULL),
		NULL);
	if (g_hWndStage == NULL)
	{
		DWORD dw = ::GetLastError();
		cout << "Unable to create ActiveX control" << endl;
		cout << "  Error: " << dw << endl;
		return FALSE;
	}

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
	//const MlChar *file = (const MlChar *)"M:\\projects\\MagicLantern\\Titles\\mtea\\src\\mtea.dwp";
	char file[1024];
	sprintf(file, "%s\\mtea.dwp", g_testHome);
	MleWin32Path *path = new MleWin32Path((const MlChar *)file, true);

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

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			::MoveWindow(g_hWndStage, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
