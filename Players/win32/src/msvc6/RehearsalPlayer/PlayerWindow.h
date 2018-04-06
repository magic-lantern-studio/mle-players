/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file PlayerWindow.h
 * @ingroup MlePlayer
 *
 * This file declares the class CPlayerWindow.
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

#pragma once

// Include ATL header files.
#include <atlbase.h>
#include <atlwin.h>
#include <stdio.h>

#include "BaseWnd.h"

class CPlayerWindow : public CBaseWnd
{
  public:

   // Specify name of the new Windows class.
   DECLARE_WND_CLASS(_T("MlePlayerWindow")) 

   BEGIN_MSG_MAP(CPlayerWindow)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
	  MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	  MESSAGE_HANDLER(WM_SIZE, OnSize)
	  CHAIN_MSG_MAP(CBaseWnd)
   END_MSG_MAP()

   CPlayerWindow()
   {
		// Create an event to monitor player initialization.
		m_hPlayerInitEvent = CreateEvent(NULL, FALSE, FALSE, CPlayerWindow::g_playerInitEvent);
		// Create an event to monitor player termination.
		m_hPlayerTermEvent = CreateEvent(NULL, FALSE, FALSE, CPlayerWindow::g_playerTermEvent);
   }

   LRESULT OnCreate(UINT nMsg, WPARAM wParam, 
       LPARAM lParam, BOOL& bHandled)
   {
	    printf("***** PlayerWindow OnCreate() called. *****\n");
        return 0;
   }

   LRESULT OnDestroy(UINT nMsg, WPARAM wParam, 
       LPARAM lParam, BOOL& bHandled)
   {
	    printf("***** PlayerWindow OnDestroy() called. *****\n");
        PostQuitMessage( 0 );
        return 0;
   }

   LRESULT OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

   /**
    * @brief Initialize the player.
	*
	* @param argc The argument count.
	* @param argv The argument vector.
    */
   void init(int argc, char *argv[]);

   /**
    * @brief Execute the player.
	*
	* @return If the player successfully runs, then 0 will be returned.
	* Otherwise, a non-zero value will be returned.
    */
   int run();

   int update();

   /**
    * @brief Terminate the player and clean up.
	*
	* @return If the player successfully terminates, then 0 will be returned.
	* Otherwise, a non-zero value will be returned.
    */
   int terminate();

  public:

   static LPCTSTR g_playerInitEvent; // "PlayerInitCompleteEvent"
   static LPCTSTR g_playerTermEvent; // "PlayerTermCompleteEvent"
   
   HANDLE m_hPlayerInitEvent;
   HANDLE m_hPlayerTermEvent;

};
