#include "tab2sockeclient.h"
#include "ui_tab2sockeclient.h"
#include "socketclient.h"

Tab2SockeClient::Tab2SockeClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab2SockeClient)
{
    ui->setupUi(this);
    pSocketClient = new SocketClient(this);
    connect(pSocketClient,SIGNAL(sigSocketRecv(QString)),this,SLOT(socketRecvUpdateSlot(QString)));
    ui->pPBSendButton->setEnabled(false);
}

Tab2SockeClient::~Tab2SockeClient()
{
    delete ui;
}

void Tab2SockeClient::on_pPBServerConnect_clicked(bool checked)
{
    bool bOk;
    if(checked)
    {
        pSocketClient->slotConnectToServer(bOk);
        if(bOk)
        {
            ui->pPBServerConnect->setText("서버 해제");
            ui->pPBSendButton->setEnabled(true);
        }
    }
    else
    {
        pSocketClient->slotClosedByServer();
        ui->pPBServerConnect->setText("서버 연결");
        ui->pPBSendButton->setEnabled(false);
    }
}

void Tab2SockeClient::socketRecvUpdateSlot(QString strRecvData)
{
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
    strRecvData.chop(1);    //"\n" 제거
    strTime = strTime + " " + strRecvData;

    ui->pTERecvData->append(strTime);
    //[KSH_QT]LED@0xff ==> @KSH_QT@LED@0xff
    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList qList = strRecvData.split("@");

    if(qList[2].indexOf("LED") == 0)
    {
       bool bOk;
       int ledNo =qList[3].toInt(&bOk,16);
       if(bOk)
           emit ledWriteSig(ledNo);
    }
}

void Tab2SockeClient::on_pPBSendButton_clicked()
{
    QString strRecvId = ui->pLERecvId->text();
    QString strSendData = ui->pLESendData->text();
    if(!strSendData.isEmpty())
    {
        if(strRecvId.isEmpty())
           strSendData = "[ALLMSG]"+ strSendData;
        else
           strSendData = "["+strRecvId+"]"+strSendData;

        pSocketClient->slotSocketSendData(strSendData);
        ui->pLESendData->clear();
    }
}
