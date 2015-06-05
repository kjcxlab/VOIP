#ifndef QSIP_H
#define QSIP_H

#include <QtWidgets/QWidget>
#include <eXosip2/eXosip.h>
#include "ui_qsip.h"
#include "SipThread.h"
#include <Winsock2.h>

typedef unsigned int UINT;

class QSIP : public QWidget
{
	Q_OBJECT

public:
	QSIP(QWidget *parent = 0);
	~QSIP();
	int real_send_register(int expires);
private:
	Ui::QSIPClass ui;
	SipThread *Sip_Monitor;
private slots:
	void OnReg();
	void OnDial();
	void OnHang();
	void OnUnreg();
	void OnAccept();
	void OnDtmf();
};

#endif // QSIP_H
