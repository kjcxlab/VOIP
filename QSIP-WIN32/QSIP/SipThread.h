#pragma once
#pragma execution_character_set("utf-8")
#include "qthread.h"
#include <qDebug>
#include <osipparser2/osip_message.h>
#include <osipparser2/osip_parser.h>
#include <osipparser2/osip_port.h>
#include <eXosip2/eXosip.h>
#include <eXosip2/eX_setup.h>
#include <eXosip2/eX_register.h>
#include <eXosip2/eX_options.h>
#include <eXosip2/eX_message.h>
#include <mediastreamer2/mediastream.h>
#include <QString>
#include <Winsock2.h>

#define WITH_MEDIA

class SipThread :
	public QThread
{
	Q_OBJECT
public:
	SipThread(QObject *parent = 0);
	~SipThread();
	bool sip_init();
	int codec_id;
	int rtp_port;
	bool doing;
	bool calling;
	bool picked;
	bool dtmfing;
	int dialog_id;
	int call_id;

#ifdef WITH_MEDIA
	AudioStream *audio = NULL;
	RtpProfile *profile = NULL;
	RtpSession *session = NULL;
	OrtpEvQueue *q = NULL;
	bool build_media(int local_port, const char *remote_ip, 
		int remote_port, int payload, const char *fmtp, int jitter, bool ec, int bitrate);
#endif

protected:
	virtual void run();
private:

signals:
	void Label_Stauts(const QString& str);
	void Label_Reg(const QString& str);
	void Button_Dial(bool);
	void Button_Reg(bool);
	void Button_Unreg(bool);
	void Button_Hang(bool);
};

