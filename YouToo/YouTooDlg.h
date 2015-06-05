// YouTooDlg.h : header file
//

#if !defined(AFX_YOUTOODLG_H__92ADE78E_3531_46CB_8A42_68E21327EFE3__INCLUDED_)
#define AFX_YOUTOODLG_H__92ADE78E_3531_46CB_8A42_68E21327EFE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CYouTooDlg dialog

class CYouTooDlg : public CDialog
{
// Construction
public:
	int codec_id;
	int rtp_port;
	int real_send_register(int expires);
	bool doing;								//事件检测开关
	bool calling;							//被叫状态
	bool picked;							//被叫接听开关
	bool dtmfing;

	int dialog_id;
	int call_id;

	CYouTooDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CYouTooDlg)
	enum { IDD = IDD_YOUTOO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYouTooDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnOk()
	{
		AfxMessageBox("ok");
		return;
	}
	
	void OnCancel()
	{
		//if(MessageBox("你确认要退出程序吗?","退出通话",MB_YESNO|MB_ICONQUESTION)==IDYES)
			CDialog::OnCancel();
	}
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CYouTooDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnReg();
	afx_msg void OnDial();
	afx_msg void OnHang();
	afx_msg void OnUnreg();
	afx_msg void OnAccept();
	afx_msg void OnDtmf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool sip_init();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YOUTOODLG_H__92ADE78E_3531_46CB_8A42_68E21327EFE3__INCLUDED_)
