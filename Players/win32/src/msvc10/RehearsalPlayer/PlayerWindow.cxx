/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file PlayerWindow.cxx
 * @ingroup MlePlayer
 *
 * This file implements the class CPlayerWindow.
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
