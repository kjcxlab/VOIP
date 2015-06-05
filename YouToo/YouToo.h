// YouToo.h : main header file for the YOUTOO application
//

#if !defined(AFX_YOUTOO_H__423DD58D_B0B1_426A_AD67_A000CCFD7755__INCLUDED_)
#define AFX_YOUTOO_H__423DD58D_B0B1_426A_AD67_A000CCFD7755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CYouTooApp:
// See YouToo.cpp for the implementation of this class
//

class CYouTooApp : public CWinApp
{
public:
	CYouTooApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYouTooApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CYouTooApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YOUTOO_H__423DD58D_B0B1_426A_AD67_A000CCFD7755__INCLUDED_)
