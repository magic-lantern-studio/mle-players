/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file BaseWnd.h
 * @ingroup MlePlayer
 *
 * This file declares the interface for the CBaseWnd class.
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

#if !defined(AFX_BASEWND_H__D0B94810_A19B_42C7_BA7A_7D8491C70BA9__INCLUDED_)
#define AFX_BASEWND_H__D0B94810_A19B_42C7_BA7A_7D8491C70BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBaseWnd : public CWindowImpl<CBaseWnd>
{
  public:

	typedef CWindowImpl<CBaseWnd> baseWnd;

	DECLARE_WND_CLASS(NULL)

	BEGIN_MSG_MAP(CBaseWnd)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
//		CHAIN_MSG_MAP(baseWnd)
	END_MSG_MAP()

	CBaseWnd()
	{
		m_bVisible = FALSE;
		SetRectEmpty(&m_rcIdeal);
	}

	HWND Create(HWND hWndParent, RECT rcPos, LPCTSTR lpstrTitle = NULL,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		DWORD dwExStyle = 0, UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		if (dwExStyle & WS_EX_MDICHILD)
		{
			m_pfnSuperWindowProc = ::DefMDIChildProc;
		}
		return baseWnd::Create(hWndParent, rcPos, lpstrTitle, dwStyle, dwExStyle, nID, lpCreateParam);
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bVisible = !ShowWindow(!m_bVisible);
		return 0;
	}

	BOOL Toggle()
	{
		// ID_PANE_CLOSE == 0xE152
		return ::PostMessage(GetParent(), WM_COMMAND, 0xE152, (LPARAM)m_hWnd);
	}

	BOOL GetIdealRect(LPRECT pRect)
	{
		ATLASSERT(pRect);
		memcpy(pRect, &m_rcIdeal, sizeof(RECT));
		return (pRect != NULL);
	}

	BOOL IsVisible()
	{
		return m_bVisible;
	}

	//HWND m_hWndStatusBar;
	//HWND m_hWndClient;
	RECT m_rcIdeal;
	BOOL m_bVisible;

};

#endif // !defined(AFX_BASEWND_H__D0B94810_A19B_42C7_BA7A_7D8491C70BA9__INCLUDED_)
