/** @defgroup MlePlayer Magic Lantern Rehearsal Player */

/**
 * @file AuStage.h
 * @ingroup MlePlayer
 *
 * This file declares the class CAuStage.
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

#ifndef __AUSTAGE_H_
#define __AUSTAGE_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "PlayerWindow.h"


/////////////////////////////////////////////////////////////////////////////
// CAuStage
class ATL_NO_VTABLE CAuStage : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IAuStage, &IID_IAuStage, &LIBID_REHEARSALPLAYERLib>,
	public CComControl<CAuStage>,
	public IPersistStreamInitImpl<CAuStage>,
	public IOleControlImpl<CAuStage>,
	public IOleObjectImpl<CAuStage>,
	public IOleInPlaceActiveObjectImpl<CAuStage>,
	public IViewObjectExImpl<CAuStage>,
	public IOleInPlaceObjectWindowlessImpl<CAuStage>,
	public IPersistStorageImpl<CAuStage>,
	public ISpecifyPropertyPagesImpl<CAuStage>,
	public IQuickActivateImpl<CAuStage>,
	public IDataObjectImpl<CAuStage>,
	public IProvideClassInfo2Impl<&CLSID_AuStage, NULL, &LIBID_REHEARSALPLAYERLib>,
	public CComCoClass<CAuStage, &CLSID_AuStage>
{
public:
	CAuStage()
	{
		m_digitalWorkprint = NULL;
		m_running = FALSE;
	}

	virtual ~CAuStage()
	{
		if (m_digitalWorkprint)
			delete m_digitalWorkprint;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AUSTAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAuStage)
	COM_INTERFACE_ENTRY(IAuStage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CAuStage)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CAuStage)
	CHAIN_MSG_MAP(CComControl<CAuStage>)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	//MESSAGE_HANDLER(WM_SIZE, OnSize)
	CHAIN_MSG_MAP_MEMBER(m_view)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IAuStage
public:
	STDMETHOD(setDigitalWorkprint)(BSTR dwp);
	STDMETHOD(isRunning)(BOOL *running);
	STDMETHOD(cleanup)();
	STDMETHOD(run)();
	STDMETHOD(init)(BSTR cmdline);
	STDMETHOD(startPlayer)(BSTR cmdline);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : AuStage");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	// The Rehearsal Player.
	CPlayerWindow m_view;

	// The Digital Workprint.
	CComBSTR *m_digitalWorkprint;
	//CComVariant *m_digitalWorkprint;

	// The window handle for the player.
	HWND m_hWndPlayer;

    // Flag indicating whether the player is running.
	BOOL m_running;
};

#endif //__AUSTAGE_H_
