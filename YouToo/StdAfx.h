// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5C78AD2C_AEC0_4982_9B7A_DA26FE954F30__INCLUDED_)
#define AFX_STDAFX_H__5C78AD2C_AEC0_4982_9B7A_DA26FE954F30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <Winsock2.h>		/*　解决winsock中结构重复定义的问题 */
#include <afxsock.h>		// MFC socket extensions

#include <eXosip2/eXosip.h>
#include <mediastreamer2/mediastream.h>


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5C78AD2C_AEC0_4982_9B7A_DA26FE954F30__INCLUDED_)
