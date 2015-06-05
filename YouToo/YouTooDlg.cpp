// YouTooDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YouToo.h"
#include "YouTooDlg.h"
#include "stdio.h"
#include <iostream>

#define WAIT_TIMER 200			//事件检测时间间隔ms
#define REG_TIMER  30*1000	    //注册时间间隔ms

bool build_media(int local_port, const char *remote_ip, 
				 int remote_port, int payload, const char *fmtp, int jitter, bool ec, int bitrate);

CYouTooDlg *dlg_wnd = NULL;

AudioStream *audio = NULL;
RtpProfile *profile = NULL;
RtpSession *session = NULL;
OrtpEvQueue *q = NULL;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEBUG_INFO debug_info->AddString

UINT sip_ua_monitor(void *pArg)
{
	bool ret = false;
	char *payload_str;					/* 服务器优先编码值 */
	char localip[128];
	char tmp[4096];	

	CString dtmf_str;
	char dtmf[50] = {0};
	
	int reg_remain = REG_TIMER;
	
	CYouTooDlg *pMainWnd = (CYouTooDlg *)pArg;
	CListBox *debug_info = ((CListBox *)pMainWnd->GetDlgItem(IDC_INFO));

	DEBUG_INFO("Event monitor for ua[c|s] start!");

	eXosip_event_t *uac_e;				/* 事件处理 */
	osip_message_t *ack = NULL;	        /* 响应消息 */
	osip_message_t *answer = NULL;	    /* 请求消息的回应 */

	/* 响应SDP(用于UAC) */
	sdp_message_t * msg_rsp = NULL;
	sdp_connection_t * con_rsp = NULL;
	sdp_media_t * md_rsp = NULL;

	/* 请求SDP(用于UAS) */
	sdp_message_t * msg_req = NULL;
	sdp_connection_t * con_req = NULL;  
	sdp_media_t * md_req = NULL;
	
	char out_str[100] = {0};
	
	eXosip_lock ();
	eXosip_automatic_action();
	eXosip_unlock ();
	pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(开始监听进程)");
	while(pMainWnd->doing)
	{
		eXosip_lock ();
		uac_e = eXosip_event_wait (0, WAIT_TIMER);
		eXosip_unlock ();

		reg_remain = reg_remain - WAIT_TIMER;
		if(reg_remain < 0)
		{
			//超时，重新注册
			eXosip_lock ();
			eXosip_automatic_refresh();
			eXosip_unlock ();
			reg_remain = REG_TIMER;
			DEBUG_INFO("register timeout,retry!");
			pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("register timeout,retry!");
		}

		if(pMainWnd->dtmfing)
		{		
			((CEdit *)pMainWnd->GetDlgItem(IDC_DTMF_STR))->GetWindowText(dtmf_str);
			strcpy(dtmf, dtmf_str.GetBuffer(dtmf_str.GetLength()));
			
			for(int index=0; index<50; index++)
			{
				//依次读取字符
				if(dtmf[index] == '\0') break;
				
				/* 发送DTMF */
				eXosip_lock();
				audio_stream_send_dtmf(audio, dtmf[index]);
				eXosip_unlock();

				sprintf(out_str, "DTMF send <%c> OK!", dtmf[index]);
				DEBUG_INFO(out_str);
				Sleep(500);
			}

			pMainWnd->dtmfing = false;
		}

		if (uac_e == NULL)
		{
			//DEBUG_INFO("nothing");
			continue;
		}

		eXosip_lock ();
		eXosip_default_action(uac_e);	/* 处理407加入鉴权信息 */
		eXosip_unlock ();

		if(NULL != uac_e->response)
		{
			//UAC 消息处理前检查
			sprintf(out_str, "%d %s", uac_e->response->status_code, uac_e->response->reason_phrase);
			DEBUG_INFO(out_str);

			if(487 == uac_e->response->status_code)
			{
				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(取消呼叫成功)");
				pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(true);				
				pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(false);
				continue;
			}

			if(480 == uac_e->response->status_code)
			{
				//480 无应答
				pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(true);	
				pMainWnd->GetDlgItem(IDC_ACCEPT)->EnableWindow(true);	
				pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(false);				
				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(无应答)");
				
				//隐藏接通按钮显示呼叫按钮
				((CButton *)pMainWnd->GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
				((CButton *)pMainWnd->GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
				
				pMainWnd->picked = false;
				pMainWnd->calling = false;
				pMainWnd->call_id = 0;
				pMainWnd->dialog_id = 0;				
				continue;
			}
		}

		if(NULL != uac_e->request)
		{
		}

		if(NULL != uac_e->ack)
		{
		}
		
		switch (uac_e->type)
		{
			case EXOSIP_CALL_SERVERFAILURE:
			case EXOSIP_CALL_RELEASED:
				/* 服务器错误或对方忙 */
				pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(true);	
				pMainWnd->GetDlgItem(IDC_ACCEPT)->EnableWindow(true);	
				pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(false);				
				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(对方或服务器正忙!)");
				
				//隐藏接通按钮显示呼叫按钮
				((CButton *)pMainWnd->GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
				((CButton *)pMainWnd->GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
				
				pMainWnd->call_id = 0;
				pMainWnd->dialog_id = 0;
				pMainWnd->picked = false;
				pMainWnd->calling = false;
				
				DEBUG_INFO("Dest or Server Busy!");
				break;

			/* UAS 处理事件 */
			case EXOSIP_CALL_INVITE:
				sprintf(out_str, "收到来自 %s 的呼叫!",uac_e->request->from->url->string);
				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText(out_str);

				eXosip_lock ();
				eXosip_call_send_answer(uac_e->tid, 180, NULL);
				if(0 != eXosip_call_build_answer(uac_e->tid, 200, &answer))
				{
					eXosip_call_send_answer(uac_e->tid, 603, NULL);
					AfxMessageBox("error build answer!");
					continue;
				}
				eXosip_unlock ();
				
				pMainWnd->call_id = uac_e->cid;					//供挂断电话上下文操作
				pMainWnd->dialog_id = uac_e->did;

				/* 构建本地SDP消息供媒体建立 */
				eXosip_guess_localip(AF_INET, localip, 128);
				snprintf (tmp, 4096,
					"v=0\r\n"
					"o=youtoo 1 1 IN IP4 %s\r\n"
					"s=##youtoo demo\r\n"
					"c=IN IP4 %s\r\n"
					"t=0 0\r\n"
					"m=audio %d RTP/AVP 0 8 101\r\n"
					"a=rtpmap:0 PCMU/8000\r\n"
					"a=rtpmap:8 PCMA/8000\r\n"
					"a=rtpmap:101 telephone-event/8000\r\n"
					"a=fmtp:101 0-15\r\n", localip, localip, pMainWnd->rtp_port);
				
				//设置回复的SDP消息体,下一步计划分析消息体
				eXosip_lock ();
				osip_message_set_body(answer, tmp, strlen(tmp));
				osip_message_set_content_type(answer, "application/sdp");
				
				/* 解析SDP */
				msg_req = eXosip_get_remote_sdp(uac_e->did);
				con_req = eXosip_get_audio_connection(msg_req);
				md_req = eXosip_get_audio_media(msg_req);
				eXosip_unlock ();
				
				/*
				payload_str = (char *)osip_list_get(&md_req->m_payloads, 0);	//取主叫媒体能力编码
				//暂时只支持0/8 711u/711a
				*/
				
				//隐藏呼叫按钮显示接听按钮
				((CButton *)pMainWnd->GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_SHOWNORMAL);
				((CButton *)pMainWnd->GetDlgItem(IDC_DIAL))->ShowWindow(SW_HIDE);
				pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(true);

				pMainWnd->calling = true;

				while(!pMainWnd->picked)
				{
					//未接通进入循环检测
					Sleep(200);
				}

				eXosip_unlock ();
				eXosip_call_send_answer(uac_e->tid, 200, answer);
				eXosip_unlock ();

				DEBUG_INFO("200 ok 发送");
				break;

			case EXOSIP_CALL_CANCELLED:
				/* 拒绝接听 */
				//隐藏接通按钮显示呼叫按钮
				((CButton *)pMainWnd->GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
				((CButton *)pMainWnd->GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
				
				pMainWnd->call_id = 0;
				pMainWnd->dialog_id = 0;				
				pMainWnd->picked = false;
				pMainWnd->calling = false;
				pMainWnd->GetDlgItem(IDC_REG_STATUS)->SetWindowText("(已拒绝)");
				break;

			case EXOSIP_CALL_ACK:
				/* 返回200后收到ack才建立媒体 */
				if(pMainWnd->calling)
				{
					/* 建立RTP连接 */
					ret = build_media(pMainWnd->rtp_port, con_req->c_addr, atoi(md_req->m_port), 0, NULL, 0, 0, 0);
					if(!ret)
					{
						AfxMessageBox("媒体建立失败，无法创建通话，请挂断！");
						//pMainWnd->OnHang();
					}				
				}
				break;

			/* UAC 处理事件 */
			case EXOSIP_REGISTRATION_SUCCESS:
				if(0 < uac_e->response->contacts.nb_elt)	/*bind 数大于0表示注册，否则为注销*/
				{
					pMainWnd->GetDlgItem(IDC_REG_STATUS)->SetWindowText("(已登录)");
					pMainWnd->GetDlgItem(IDC_REG)->EnableWindow(false);
					pMainWnd->GetDlgItem(IDC_UNREG)->EnableWindow(true);

					if(0 == pMainWnd->call_id)
					{
						//第一次手动注册成功时
						pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(true);
					}
				}
				else
				{
					pMainWnd->GetDlgItem(IDC_REG_STATUS)->SetWindowText("(已注销)");
					pMainWnd->GetDlgItem(IDC_REG)->EnableWindow(true);
					pMainWnd->GetDlgItem(IDC_UNREG)->EnableWindow(false);
					pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(false);
					pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(false);
				}
				break;

			case EXOSIP_CALL_CLOSED:
				if(audio) 
				{
					//被动关闭媒体连接(远端触发)
					eXosip_lock ();
					audio_stream_stop(audio);
					
					ortp_ev_queue_destroy(q);
					rtp_profile_destroy(profile);
					eXosip_unlock ();

					audio = NULL;
					q = NULL;
					profile = NULL;
					DEBUG_INFO("audio stream stoped!");
				}

				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(对方已挂断)");
				pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(true);	
				pMainWnd->GetDlgItem(IDC_ACCEPT)->EnableWindow(true);	
				pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(false);				

				//隐藏接通按钮显示呼叫按钮
				((CButton *)pMainWnd->GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
				((CButton *)pMainWnd->GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
				
				pMainWnd->call_id = 0;
				pMainWnd->dialog_id = 0;				
				pMainWnd->picked = false;
				pMainWnd->calling = false;
				break;
				
			case EXOSIP_CALL_PROCEEDING:
				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(查找连接中..)");
				pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(false);				
				break;

			case EXOSIP_CALL_RINGING:
				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(对方振铃)");
				pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(true);			
				pMainWnd->call_id = uac_e->cid;
				pMainWnd->dialog_id = uac_e->did;

				/*
				RingStream *r;
				MSSndCard *sc;
				sc=ms_snd_card_manager_get_default_card(ms_snd_card_manager_get());
				r=ring_start("D:\\mbstudio\\vcwork\\YouToo\\dial.wav",2000,sc);
				
				Sleep(10);
				ring_stop(r);
				*/
				break;
				
			case EXOSIP_CALL_ANSWERED:
				//ring_stop(ring_p);				
				pMainWnd->GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(对方已接听)");
				pMainWnd->GetDlgItem(IDC_DIAL)->EnableWindow(false);				
				pMainWnd->GetDlgItem(IDC_HANG)->EnableWindow(true);		
				
				pMainWnd->call_id = uac_e->cid;
				pMainWnd->dialog_id = uac_e->did;
				
				eXosip_lock ();
				eXosip_call_build_ack (uac_e->did, &ack);
				eXosip_call_send_ack (uac_e->did, ack);

				/* 响应SIP消息中SDP分析 */
				msg_rsp = eXosip_get_sdp_info(uac_e->response);
				con_rsp = eXosip_get_audio_connection(msg_rsp);
				md_rsp = eXosip_get_audio_media(msg_rsp);

				/* 取服务器支持的最优先的编码方式 */
				payload_str = (char *)osip_list_get(&md_rsp->m_payloads, 0);
				eXosip_unlock ();

				/* 建立RTP连接 */
				ret = build_media(pMainWnd->rtp_port, con_rsp->c_addr, atoi(md_rsp->m_port), atoi(payload_str), NULL, 0, 0, 0);
				if(!ret)
				{
					AfxMessageBox("媒体建立失败，无法创建通话，请挂断！");
					//pMainWnd->OnHang();
				}
				break;

			default:
				break;
		}
		
		eXosip_event_free (uac_e);

		/* 调试信息刷新 */
		debug_info->SetCurSel(debug_info->GetCount()-1);
	}
	
	return 0;
}		


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYouTooDlg dialog

CYouTooDlg::CYouTooDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYouTooDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYouTooDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYouTooDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYouTooDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CYouTooDlg, CDialog)
	//{{AFX_MSG_MAP(CYouTooDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_REG, OnReg)
	ON_BN_CLICKED(IDC_DIAL, OnDial)
	ON_BN_CLICKED(IDC_HANG, OnHang)
	ON_BN_CLICKED(IDC_UNREG, OnUnreg)
	ON_BN_CLICKED(IDC_ACCEPT, OnAccept)
	ON_BN_CLICKED(IDC_DTMF, OnDtmf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYouTooDlg message handlers

BOOL CYouTooDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if(!sip_init())
	{
		/* 初始化SIP失败则直接退出 */
		OnOK();
	}

	GetDlgItem(IDC_NAME)->SetWindowText("103");
	GetDlgItem(IDC_PWD)->SetWindowText("103");
	GetDlgItem(IDC_HOST)->SetWindowText("59.74.168.146");
	GetDlgItem(IDC_PORT)->SetWindowText("5060");
	GetDlgItem(IDC_CALLEE)->SetWindowText("102");
	
	rtp_port = 9900;		//rtp　媒体本地端口
	codec_id = 0;		//编码 G711uLaw 0

	dlg_wnd = this;

	call_id = 0;
	dialog_id = 0;

	doing = true;					/* 事件循环开关 */
	calling = false;				/* 是否正在被叫(判断ack类型) */
	picked = false;
	dtmfing = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CYouTooDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CYouTooDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CYouTooDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/***********SIP服务初始化**************/
bool CYouTooDlg::sip_init()
{
	int ret = 0;

	ret = eXosip_init ();
	eXosip_set_user_agent("##YouToo0.1");

	if(0 != ret)
	{
		AfxMessageBox("Couldn't initialize eXosip!\n");
		return false;
	}

	ret = eXosip_listen_addr (IPPROTO_UDP, NULL, 0, AF_INET, 0);
	if(0 != ret)
	{
		eXosip_quit ();
		AfxMessageBox("Couldn't initialize transport layer!\n");
		return false;
	}

	AfxBeginThread(sip_ua_monitor,(void *)this);

	/* rtp */
	ortp_init();
	//ortp_set_log_level_mask(ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR|ORTP_FATAL);

	/* media */
	ms_init();
	return true;
}
/**************销毁对话框************/
void CYouTooDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	doing = false;
	Sleep(1000);				//保证事件线程能退出(线程循环检测时间毫秒级<1000)

	eXosip_quit ();	
}
/**************向服务器注册****************/
void CYouTooDlg::OnReg() 
{
	/* 先清除鉴权信息，再应用新输入的鉴权信息 */
	char uname[100] = {0};
	char upwd[100] = {0};
	
	GetDlgItem(IDC_NAME)->GetWindowText(uname,100);
	GetDlgItem(IDC_PWD)->GetWindowText(upwd,100);

	eXosip_clear_authentication_info();
	eXosip_add_authentication_info(uname, uname, upwd, "md5", NULL);  
	
	real_send_register(30);
}

void CYouTooDlg::OnUnreg() 
{
	real_send_register(0);	
}

/****************************
****当发起呼叫时：
****************************/
void CYouTooDlg::OnDial() 
{
	osip_message_t *invite = NULL;  /* 呼叫发起消息体 */

	char source_call[100];
	char dest_call[100];

	char uname[100] = {0};
	char host[100] = {0};
	char callee[100] = {0};
	char port[100] = {0};

	/*在这里获取用户的编辑框里输入的账户密码主机端口等信息*/
	GetDlgItem(IDC_NAME)->GetWindowText(uname,100);
	GetDlgItem(IDC_HOST)->GetWindowText(host,100);
	GetDlgItem(IDC_CALLEE)->GetWindowText(callee,100);
	GetDlgItem(IDC_PORT)->GetWindowText(port,100);
	/*将信息格式化到两个缓存中*/
	sprintf(source_call, "sip:%s@%s:%s", uname, host, port);
	sprintf(dest_call,   "sip:%s@%s:%s", callee,host, port);	
	
	char tmp[4096];	
	/*试图建立会话*/
	int i = eXosip_call_build_initial_invite (&invite, dest_call, source_call, NULL, "## YouToo test demo!");
	if (i != 0)
	{
		AfxMessageBox("Intial INVITE failed!\n");
	}
	
	char localip[128];
				
	eXosip_guess_localip (AF_INET, localip, 128);
	snprintf (tmp, 4096,
		"v=0\r\n"
		"o=youtoo 1 1 IN IP4 %s\r\n"
		"s=##youtoo demo\r\n"
		"c=IN IP4 %s\r\n"
		"t=0 0\r\n"
		"m=audio %d RTP/AVP 0 8 101\r\n"
		"a=rtpmap:0 PCMU/8000\r\n"
		"a=rtpmap:8 PCMA/8000\r\n"
		"a=rtpmap:101 telephone-event/8000\r\n"
		"a=fmtp:101 0-15\r\n", localip, localip, rtp_port);
				
	osip_message_set_body (invite, tmp, strlen(tmp));
	osip_message_set_content_type (invite, "application/sdp");
				
	eXosip_lock ();
	i = eXosip_call_send_initial_invite (invite);
	eXosip_unlock ();				
}

/****************************
****当挂起时：
****************************/
void CYouTooDlg::OnHang() 
{
	int ret;

	if(audio) 
	{
		//主动关闭媒体连接(本地端)
		 
		audio_stream_stop(audio);

		ortp_ev_queue_destroy(q);
		rtp_profile_destroy(profile);
		eXosip_unlock ();
		
		((CListBox *)GetDlgItem(IDC_INFO))->AddString("audio stream stoped!");
		((CListBox *)GetDlgItem(IDC_INFO))->SetCurSel(((CListBox *)GetDlgItem(IDC_INFO))->GetCount()-1);
		audio = NULL;
		q = NULL;
		profile = NULL;
	}
				
	eXosip_lock ();

	/*断开连接*/
	ret = eXosip_call_terminate(call_id, dialog_id);  
	eXosip_unlock ();
	if(0 != ret)
	{
		AfxMessageBox("hangup/terminate Failed!");
	}
	/*使能对应按键的状态*/
	GetDlgItem(IDC_DIAL)->EnableWindow(true);	
	GetDlgItem(IDC_ACCEPT)->EnableWindow(true);	
	GetDlgItem(IDC_HANG)->EnableWindow(false);				
	GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(已挂断)");
	
	//隐藏接通按钮显示呼叫按钮
	((CButton *)GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);

	call_id = 0;
	dialog_id = 0;
	picked = false;
	calling = false;
}

int CYouTooDlg::real_send_register(int expires)
{
	char from[100];
	char proxy[100];
	
	char uname[100] = {0};
	char host[100] = {0};
	char port[100] = {0};
	
	GetDlgItem(IDC_NAME)->GetWindowText(uname,100);
	GetDlgItem(IDC_HOST)->GetWindowText(host,100);
	GetDlgItem(IDC_PORT)->GetWindowText(port,100);
	
	sprintf(from, "<sip:%s@%s:%s>", uname, host, port);
	sprintf(proxy, "sip:%s:%s", host, port);	
	//sprintf(from, "<sip:%s@%s:%s>", "105", "59.74.168.146", "5060");
	//sprintf(proxy, "sip:%s:%s", "59.74.168.146", "5060");	
	osip_message_t *reg = NULL;
	
	char localip[128];
	eXosip_guess_localip (AF_INET, localip, 128);	
	
	//eXosip_lock ();
	int ret = eXosip_register_build_initial_register(from, proxy, NULL, expires, &reg);	
	//eXosip_unlock ();
	if(0 > ret)
	{
		AfxMessageBox("register init Failed!");
		return 1;
	}
	
//	eXosip_lock ();
	ret = eXosip_register_send_register(ret, reg);
//	eXosip_unlock ();
	if(0 != ret)
	{
		AfxMessageBox("register send Failed!");
		return 1;
	}
	
	return 0;	
}
/**建立语音连接**/
bool build_media(int local_port, const char *remote_ip, int remote_port, int payload, const char *fmtp, int jitter, bool ec, int bitrate)
{
	if(payload != 0 && payload != 8)
	{
		/* 目前仅支持0,8 711ulaw,711alaw */
		return false;
	}

	PayloadType *pt;
	
	profile = rtp_profile_clone_full(&av_profile);
	q = ortp_ev_queue_new();	

	pt = rtp_profile_get_payload(profile, payload);
	if (pt==NULL)
	{
		AfxMessageBox("codec error!");
		return false;
	}

	if (fmtp != NULL) payload_type_set_send_fmtp(pt, fmtp);
	if (bitrate > 0) pt->normal_bitrate = bitrate;

	if (pt->type != PAYLOAD_VIDEO)
	{
		((CListBox *)dlg_wnd->GetDlgItem(IDC_INFO))->AddString("audio stream start!");
		audio = audio_stream_start(profile, local_port, remote_ip, remote_port, payload, jitter, ec);
		if (audio) 
		{
			session = audio->session;
		}
		else
		{
			AfxMessageBox("session error!");
			return false;
		}
	}
	else
	{
		AfxMessageBox("codec select error!");
		return false;
	}

	rtp_session_register_event_queue(session, q);	
	return true;
}
/**********接受通话请求**********/
void CYouTooDlg::OnAccept() 
{
	/* 置接通电话变量为真 */
	picked = true;

	GetDlgItem(IDC_ACCEPT)->EnableWindow(false);	
	GetDlgItem(IDC_HANG)->EnableWindow(true);				
	GetDlgItem(IDC_CALL_STATUS)->SetWindowText("(已接听)");
}


void CYouTooDlg::OnDtmf() 
{
	dtmfing = true;
}
