#include "qsip.h"
#include <QDebug>
#include <osipparser2/osip_message.h>
#include <osipparser2/osip_parser.h>
#include <osipparser2/osip_port.h>
#include <eXosip2/eXosip.h>
#include <eXosip2/eX_setup.h>
#include <eXosip2/eX_register.h>
#include <eXosip2/eX_options.h>
#include <eXosip2/eX_message.h>
#include <QString>

QSIP::QSIP(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	Sip_Monitor = new SipThread;
	Sip_Monitor->start();
	this->setWindowTitle(tr("QSIP Of kjcxlab"));
	/*Set the default args*/
	ui.lineEdit_Name->setText("105");
	ui.lineEdit_Pwd->setText(tr("105"));
	ui.lineEdit_Host->setText(tr("59.74.168.146"));
	ui.lineEdit_Port->setText(tr("5060"));
    ui.lineEdit_Callee->setText(tr("102"));

    ui.label_image->setPixmap(QPixmap(":/new/label.png")
                         .scaled(ui.label_image->width()-20,
                                 ui.label_image->height()-20,Qt::IgnoreAspectRatio));

    connect(ui.pushButton_Dial,SIGNAL(clicked()),this,SLOT(OnDial()));
	connect(ui.pushButton_Hang, SIGNAL(clicked()), this, SLOT(OnHang()));
	connect(ui.pushButton_Reg, SIGNAL(clicked()), this, SLOT(OnReg()));
	connect(ui.pushButton_Unreg, SIGNAL(clicked()), this, SLOT(OnUnreg()));

	connect(Sip_Monitor, SIGNAL(Button_Dial(bool)),ui.pushButton_Dial,SLOT(setEnabled(bool)));
	connect(Sip_Monitor, SIGNAL(Button_Hang(bool)), ui.pushButton_Hang, SLOT(setEnabled(bool)));
	connect(Sip_Monitor, SIGNAL(Button_Reg(bool)), ui.pushButton_Reg, SLOT(setEnabled(bool)));
	connect(Sip_Monitor, SIGNAL(Button_Unreg(bool)), ui.pushButton_Unreg, SLOT(setEnabled(bool)));
	connect(Sip_Monitor, SIGNAL(Label_Reg(const QString&)), ui.label_Reg_Status, SLOT(setText(const QString&)));
	connect(Sip_Monitor, SIGNAL(Label_Stauts(const QString&)), ui.label_Call_Status, SLOT(setText(const QString&)));

}

QSIP::~QSIP()
{
	Sip_Monitor->doing = false;
	Sip_Monitor->wait();
#ifdef WIN32
	Sleep(1000);
#else
    sleep(1);
#endif
	eXosip_quit();
}

void QSIP::OnReg()
{
	char *uname="00000000000000000000";
	char *upwd="0000000000000000000";
	QByteArray unameA = ui.lineEdit_Name->text().toLatin1();
	QByteArray upwdA = ui.lineEdit_Name->text().toLatin1();

	uname = unameA.data();
	upwd = upwdA.data();

	eXosip_clear_authentication_info();
	//eXosip_add_authentication_info(uname, uname, upwd, "md5", NULL);
	eXosip_add_authentication_info("105", "105", "105", "md5", NULL);
	real_send_register(30);
}
void QSIP::OnDial()
{
	osip_message_t *invite = NULL;

	char source_call[100];
	char dest_call[100];

	char *uname = "00000000000000000000";
	char *host = "0000000000000000000";
	char *callee = "00000000000000000000";
	char *port = "0000000000000000000";

	QByteArray unameA = ui.lineEdit_Name->text().toLatin1();
	QByteArray hostA = ui.lineEdit_Host->text().toLatin1();
	QByteArray calleeA = ui.lineEdit_Callee->text().toLatin1();
	QByteArray portA = ui.lineEdit_Port->text().toLatin1();

	uname = unameA.data();
	host = hostA.data();
	callee = calleeA.data();
	port = portA.data();

	sprintf(source_call, "sip:%s@%s:%s", uname, host, port);
	sprintf(dest_call, "sip:%s@%s:%s", callee, host, port);

	char tmp[4096];

	int i = eXosip_call_build_initial_invite(&invite, dest_call, source_call, NULL, "## YouToo test demo!");
	if (i != 0)
	{
		qDebug()<<tr("Intial INVITE failed!\n");
	}

	char localip[128];

	eXosip_guess_localip(AF_INET, localip, 128);
	snprintf(tmp, 4096,
		"v=0\r\n"
		"o=youtoo 1 1 IN IP4 %s\r\n"
		"s=##youtoo demo\r\n"
		"c=IN IP4 %s\r\n"
		"t=0 0\r\n"
		"m=audio %d RTP/AVP 0 8 101\r\n"
		"a=rtpmap:0 PCMU/8000\r\n"
		"a=rtpmap:8 PCMA/8000\r\n"
		"a=rtpmap:101 telephone-event/8000\r\n"
		"a=fmtp:101 0-15\r\n", localip, localip, Sip_Monitor->rtp_port);

	osip_message_set_body(invite, tmp, strlen(tmp));
	osip_message_set_content_type(invite, "application/sdp");

	eXosip_lock();
	i = eXosip_call_send_initial_invite(invite);
	eXosip_unlock();
}
void QSIP::OnHang()
{
	int ret;
	#ifdef WITH_MEDIA
	if (Sip_Monitor->audio)
	{
		eXosip_lock();
		audio_stream_stop(Sip_Monitor->audio);

		ortp_ev_queue_destroy(Sip_Monitor->q);
		rtp_profile_destroy(Sip_Monitor->profile);
		eXosip_unlock();

		Sip_Monitor->audio = NULL;
		Sip_Monitor->q = NULL;
		Sip_Monitor->profile = NULL;
	}
	#endif // WITH_MEDIA

	eXosip_lock();
	ret = eXosip_call_terminate(Sip_Monitor->call_id, Sip_Monitor->dialog_id);
	eXosip_unlock();
	if (0 != ret)
	{
		qDebug()<<tr("hangup/terminate Failed!");
	}

	//GetDlgItem(IDC_ACCEPT)->EnableWindow(true);

	ui.pushButton_Dial->setEnabled(true);
	ui.pushButton_Hang->setEnabled(false);
    ui.label_Call_Status->setText(tr("Hang up"));
	/*
	((CButton *)GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
	*/
	Sip_Monitor->call_id = 0;
	Sip_Monitor->dialog_id = 0;
	Sip_Monitor->picked = false;
	Sip_Monitor->calling = false;
}
void QSIP::OnUnreg()
{
	real_send_register(0);
}
int QSIP::real_send_register(int expires)
{
	char from[100];
	char proxy[100];

	char *uname = "00000000000000000000";
	char *host = "00000000000000000000";
	char *port = "0000000000000000000";

	QByteArray unameA = ui.lineEdit_Name->text().toLatin1();
	QByteArray hostA = ui.lineEdit_Host->text().toLatin1();
	QByteArray portA = ui.lineEdit_Port->text().toLatin1();

	uname = unameA.data();
	host = hostA.data();
	port = portA.data();

	//sprintf(from, "<sip:%s@%s:%s>", uname, host, port);
	//sprintf(proxy, "sip:%s:%s", host, port);

	sprintf(from, "<sip:%s@%s:%s>", "105", "59.74.168.146", "5060");
	sprintf(proxy, "sip:%s:%s", "59.74.168.146", "5060");	

	osip_message_t *reg = NULL;

	char localip[128];
	eXosip_guess_localip(AF_INET, localip, 128);
	/*Add lock by me*/
	//eXosip_lock ();
	int ret = eXosip_register_build_initial_register(from, proxy, NULL, expires, &reg);
	//eXosip_unlock ();

	qDebug() << localip;
	qDebug() << from;
	qDebug() << proxy;

	if (0 > ret)
	{
		qDebug()<<tr("register init Failed!");
		return 1;
	}

	//	eXosip_lock ();
	ret = eXosip_register_send_register(ret, reg);
	//	eXosip_unlock ();
	if (0 != ret)
	{
		qDebug()<<tr("register send Failed!");
		return 1;
	}
	qDebug() << tr("register send Success!");
	return 0;
}
void QSIP::OnAccept()
{

}
void QSIP::OnDtmf()
{

}
