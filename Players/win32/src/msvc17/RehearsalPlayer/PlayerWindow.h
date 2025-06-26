/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file PlayerWindow.h
 * @ingroup MlePlayer
 *
 * This file declares the class CPlayerWindow.
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

		// Set a default resolution for the ideal size.
		m_rcIdeal.right = 640;
		m_rcIdeal.bottom = 480;

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
