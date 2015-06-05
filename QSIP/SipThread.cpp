#include "SipThread.h"

#define WITH_MEDIA

#define WAIT_TIMER 200			//时间时间间隔ms
#define REG_TIMER  30*1000	    //注册时间间隔ms


SipThread::SipThread(QObject *parent) :
    QThread(parent)
{
    /*If  Sip protocol init faild */
    if (!sip_init())
    {
        /*are you sure to exit*/
        //OnOK();
    }
    qDebug() << tr("sip init success !");

    audio = NULL;
    profile = NULL;
    session = NULL;
    q = NULL;

    rtp_port = 9900;
    codec_id = 0;
    call_id = 0;
    dialog_id = 0;

    doing = true;
    calling = false;
    picked = false;
    dtmfing = false;
}


SipThread::~SipThread()
{


}

bool SipThread::sip_init()
{
    int ret = 0;

    ret = eXosip_init();
    eXosip_set_user_agent("##YouToo0.1");

    if (0 != ret)
    {
        qDebug() << tr("Couldn't initialize eXosip!\n");
        return false;
    }

    ret = eXosip_listen_addr(IPPROTO_UDP, NULL, 0, AF_INET, 0);
    if (0 != ret)
    {
        eXosip_quit();
        qDebug() << tr("Couldn't initialize transport layer!\n");
        return false;
    }

    /*Create a background Thread to deal the sip message*/
    //this->start();

#ifdef WITH_MEDIA
    /* rtp */
    ortp_init();
    /* media */
    ms_init();
#endif
    return true;
}

void SipThread::run()
{
    bool ret = false;
    char *payload_str;		/*服务器优先编码值*/
    char localip[128];
    char tmp[4096];

    QString dtmf_str;
    char dtmf[50] = { 0 };

    int reg_remain = REG_TIMER;

    qDebug() << tr("Event monitor for ua[c|s] start!");

    eXosip_event_t *uac_e;
    osip_message_t *ack = NULL;
    osip_message_t *answer = NULL;

    sdp_message_t * msg_rsp = NULL;
    sdp_connection_t * con_rsp = NULL;
    sdp_media_t * md_rsp = NULL;

    sdp_message_t * msg_req = NULL;
    sdp_connection_t * con_req = NULL;
    sdp_media_t * md_req = NULL;

    char out_str[100] = { 0 };

    eXosip_lock();
    eXosip_automatic_action();
    eXosip_unlock();
    while (doing)
    {
        eXosip_lock();
        uac_e = eXosip_event_wait(0, WAIT_TIMER);
        eXosip_unlock();

        reg_remain = reg_remain - WAIT_TIMER;
        if (reg_remain < 0)
        {
            eXosip_lock();
            eXosip_automatic_refresh();
            eXosip_unlock();
            reg_remain = REG_TIMER;
            qDebug() << tr("register timeout,retry!");
        }
        /*
            if (dtmfing)
            {
            dtmf_str = ui.lineEdit_Dtmf->text();
            strcpy(dtmf, dtmf_str.to);

            for (int index = 0; index<50; index++)
            {
            if (dtmf[index] == '\0') break;

            eXosip_lock();
            audio_stream_send_dtmf(audio, dtmf[index]);
            eXosip_unlock();

            sprintf(out_str, "DTMF send <%c> OK!", dtmf[index]);
            DEBUG_INFO(out_str);
            Sleep(500);
            }

            dtmfing = false;
            }
            */
        if (uac_e == NULL)
        {
            //DEBUG_INFO("nothing");
            continue;
        }

        eXosip_lock();
        eXosip_default_action(uac_e);	/**/
        eXosip_unlock();

        if (NULL != uac_e->response)
        {
            sprintf(out_str, "%d %s", uac_e->response->status_code, uac_e->response->reason_phrase);
            qDebug() << out_str;

            if (487 == uac_e->response->status_code)
            {
                emit Label_Stauts(tr("Cancel the call"));
                emit Button_Dial(true);
                emit Button_Hang(false);
                continue;
            }

            if (480 == uac_e->response->status_code)
            {
                emit Button_Dial(true);
                //GetDlgItem(IDC_ACCEPT)->EnableWindow(true);
                emit Button_Hang(false);
                emit Label_Stauts(tr("No answer"));
                /*
                    ((CButton *)GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
                    ((CButton *)GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
                    */
                picked = false;
                calling = false;
                call_id = 0;
                dialog_id = 0;
                continue;
            }
        }

        if (NULL != uac_e->request)
        {
        }

        if (NULL != uac_e->ack)
        {
        }

        switch (uac_e->type)
        {
        case EXOSIP_CALL_SERVERFAILURE:
        case EXOSIP_CALL_RELEASED:

            emit Button_Dial(true);
            //GetDlgItem(IDC_ACCEPT)->EnableWindow(true);
            emit Button_Hang(false);
            emit Label_Stauts(tr("server or dest is busy"));
            /*
                ((CButton *)GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
                ((CButton *)GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
                */
            call_id = 0;
            dialog_id = 0;
            picked = false;
            calling = false;

            qDebug() << tr("Dest or Server Busy!");
            break;

        case EXOSIP_CALL_INVITE:
            sprintf(out_str,"recive %s call!", uac_e->request->from->url->string);
            emit Label_Stauts(tr(out_str));
            eXosip_lock();
            eXosip_call_send_answer(uac_e->tid, 180, NULL);
            if (0 != eXosip_call_build_answer(uac_e->tid, 200, &answer))
            {
                eXosip_call_send_answer(uac_e->tid, 603, NULL);
                qDebug() << tr("error build answer!");
                continue;
            }
            eXosip_unlock();

            call_id = uac_e->cid;
            dialog_id = uac_e->did;


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
                     "a=fmtp:101 0-15\r\n"
                     "m=video 53000 RTP/AVP 100\r\n"
                     "a=rtpmap:32 MPV/90000\r\n",
                     localip, localip, rtp_port);

            eXosip_lock();
            osip_message_set_body(answer, tmp, strlen(tmp));
            osip_message_set_content_type(answer, "application/sdp");

            msg_req = eXosip_get_remote_sdp(uac_e->did);
            con_req = eXosip_get_audio_connection(msg_req);
            md_req = eXosip_get_audio_media(msg_req);
            eXosip_unlock();

            /*
                payload_str = (char *)osip_list_get(&md_req->m_payloads, 0);
                */

            /*
                ((CButton *)GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_SHOWNORMAL);
                ((CButton *)GetDlgItem(IDC_DIAL))->ShowWindow(SW_HIDE);
                */
            emit Button_Hang(true);

            calling = true;

            while (!picked)
            {
#ifdef WIN32
                Sleep(200);
#else
                sleep(1);
#endif
            }

            eXosip_unlock();
            eXosip_call_send_answer(uac_e->tid, 200, answer);
            eXosip_unlock();

            qDebug() << tr("200 ok");
            break;

        case EXOSIP_CALL_CANCELLED:
            /*
                ((CButton *)GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
                ((CButton *)GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
                */
            call_id = 0;
            dialog_id = 0;
            picked = false;
            calling = false;
            emit Label_Reg(tr("refused"));
            break;

        case EXOSIP_CALL_ACK:
            if (calling)
            {
#ifdef WITH_MEDIA
                ret = build_media(rtp_port, con_req->c_addr, atoi(md_req->m_port), 0, NULL, 0, 0, 0);
                if (!ret)
                {
                    qDebug() << tr("message");
                    //OnHang();
                }
#endif
            }
            break;

        case EXOSIP_REGISTRATION_SUCCESS:
            if (0 < uac_e->response->contacts.nb_elt)
            {
                emit Label_Reg(tr("login success"));
                emit Button_Reg(false);
                emit Button_Unreg(true);

                if (0 == call_id)
                {
                    emit Button_Dial(true);
                }
            }
            else
            {
                emit Label_Reg(tr("logout success"));
                emit Button_Reg(true);
                emit Button_Unreg(false);
                emit Button_Dial(false);
                emit Button_Hang(false);

            }
            break;

        case EXOSIP_CALL_CLOSED:
#ifdef WITH_MEDIA
            if (audio)
            {
                eXosip_lock();
                audio_stream_stop(audio);

                ortp_ev_queue_destroy(q);
                rtp_profile_destroy(profile);
                eXosip_unlock();

                audio = NULL;
                q = NULL;
                profile = NULL;
                qDebug() << tr("audio stream stoped!");
            }
#endif // WITH_MEDIA

            emit Label_Stauts(tr("Dest hang up"));
            emit Button_Dial(true);
            /*
                GetDlgItem(IDC_ACCEPT)->EnableWindow(true);
                GetDlgItem(IDC_HANG)->EnableWindow(false);
                ((CButton *)GetDlgItem(IDC_ACCEPT))->ShowWindow(SW_HIDE);
                ((CButton *)GetDlgItem(IDC_DIAL))->ShowWindow(SW_SHOWNORMAL);
                */
            call_id = 0;
            dialog_id = 0;
            picked = false;
            calling = false;
            break;

        case EXOSIP_CALL_PROCEEDING:
            emit Label_Stauts(tr("searching connection"));
            emit Button_Dial(false);
            break;

        case EXOSIP_CALL_RINGING:
            emit Label_Stauts(tr("Dest ringing"));
            emit Button_Hang(true);
            call_id = uac_e->cid;
            dialog_id = uac_e->did;

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
            emit Label_Stauts(tr("Dest has been answered"));
            emit Button_Dial(false);
            emit Button_Hang(true);

            call_id = uac_e->cid;
            dialog_id = uac_e->did;

            eXosip_lock();
            eXosip_call_build_ack(uac_e->did, &ack);
            eXosip_call_send_ack(uac_e->did, ack);

            msg_rsp = eXosip_get_sdp_info(uac_e->response);
            con_rsp = eXosip_get_audio_connection(msg_rsp);
            md_rsp = eXosip_get_audio_media(msg_rsp);

            payload_str = (char *)osip_list_get(&md_rsp->m_payloads, 0);
            eXosip_unlock();

#ifdef WITH_MEDIA
            ret = build_media(rtp_port, con_rsp->c_addr, atoi(md_rsp->m_port), atoi(payload_str), NULL, 0, 0, 0);
            if (!ret)
            {
                qDebug() << tr("The media to establish failure, end call, please");
                //OnHang();
            }
#endif // WITH_MEDIA

            break;

        default:
            break;
        }

        eXosip_event_free(uac_e);
    }
    qDebug() << (tr("monitor dead"));
}

#ifdef WITH_MEDIA
bool SipThread::build_media(int local_port, const char *remote_ip, int remote_port, int payload, const char *fmtp, int jitter, bool ec, int bitrate)
{
    if (payload != 0 && payload != 8)
    {
        return false;
    }

    PayloadType *pt;

    profile = rtp_profile_clone_full(&av_profile);
    q = ortp_ev_queue_new();

    pt = rtp_profile_get_payload(profile, payload);
    if (pt == NULL)
    {
        qDebug() << tr("codec error!");
        return false;
    }

    if (fmtp != NULL) payload_type_set_send_fmtp(pt, fmtp);
    if (bitrate > 0) pt->normal_bitrate = bitrate;

    if (pt->type != PAYLOAD_VIDEO)
    {
        //((CListBox *)dlg_wnd->GetDlgItem(IDC_INFO))->AddString("audio stream start!");
        audio = audio_stream_start(profile, local_port, remote_ip, remote_port, payload, jitter, ec);
        if (audio)
        {
            session = audio_stream_get_rtp_session(audio);
        }
        else
        {
            qDebug() << tr("session error!");
            return false;
        }
        //video_stream_start(video,&av_profile,remote_ip,remote_port, remote_ip, remote_port,0,"/dev/video0");
    }
    else
    {
        qDebug() << tr("codec select error!");
        return false;
    }

    rtp_session_register_event_queue(session, q);
    return true;
}
#endif // WITH_MEDIA
