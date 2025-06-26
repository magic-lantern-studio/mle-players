/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file PlayerWindow.cxx
 * @ingroup MlePlayer
 *
 * This file implements the class CPlayerWindow.
 */

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


// Include player header files.
#include "StdAfx.h"
#include "PlayerWindow.h"

// Include Magic Lantern header files.
// #include "mle/mlTypes.h"
#include "mle/mlMalloc.h"
#include "mle/mlAssert.h"
#include "mle/mlDebug.h"
#include "mle/MleDirector.h"

// Declare external references.
extern MlBoolean InitEnv(int, char **);
extern MlBoolean InitRuntime();
extern MlBoolean InitRuntimePlayer(char *);
extern int MainLoop(void);
extern int UpdateFrame(void);
extern MlBoolean CleanupEnv(void);
extern HWND GetPlayerWindow(void);
extern void SizePlayerWindow(RECT *);

extern UINT g_uThreadId;


MleDebugMgrP *g_mlDebugMgr;


LPCTSTR CPlayerWindow::g_playerInitEvent = _T("PlayerInitCompleteEvent");
LPCTSTR CPlayerWindow::g_playerTermEvent = _T("PlayerTermCompleteEvent");

LRESULT CPlayerWindow::OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND window = GetPlayerWindow();
	if (window != NULL)
	{
		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = LOWORD(lParam);
		rc.bottom = HIWORD(lParam);
		::MoveWindow(window, rc.left, rc.top ,rc.right, rc.bottom, TRUE);
	}

	return 0;
}

void CPlayerWindow::init(int argc, char *argv[])
{
	// Create a new Rehearsal Player and initialize it. Note that
	// the handle to Window is obtained through inheritance
	// (from the ATL class CWindow).

	// Create a new title environment.
    g_theTitle = (MleDirector*)mlMalloc(sizeof(MleDirector));
    MLE_ASSERT(g_theTitle);

    // Initialize title environment.
	g_theTitle->m_platformData = m_hWnd;

	// Initialize the player.
	InitRuntime();
	InitRuntimePlayer(argv[1]);
    //InitEnv(argc,argv);

	// Signal that the player has been initialized.
	SetEvent(m_hPlayerInitEvent);
}

int CPlayerWindow::run()
{
	int retValue = 0;

	// Main execution loop.
	retValue = MainLoop();

	return retValue;
}

int CPlayerWindow::update()
{
	int retValue = 0;

	// Main execution loop.
	retValue = UpdateFrame();

	return retValue;
}

int CPlayerWindow::terminate()
{
	int retValue = 0;

	// Clean up title environment.
    retValue = CleanupEnv();

	// Signal that the player has been terminated.
	SetEvent(m_hPlayerTermEvent);

	return retValue;
}
