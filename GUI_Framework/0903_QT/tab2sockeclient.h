#ifndef TAB2SOCKECLIENT_H
#define TAB2SOCKECLIENT_H

#include <QWidget>
#include <QTime>
#include "socketclient.h"
namespace Ui {
class Tab2SockeClient;
}

class Tab2SockeClient : public QWidget
{
    Q_OBJECT

public:
    explicit Tab2SockeClient(QWidget *parent = nullptr);
    ~Tab2SockeClient();

private slots:
    void on_pPBServerConnect_clicked(bool checked);

private:
    Ui::Tab2SockeClient *ui;
    SocketClient *pSocketClient;

private slots:
    void socketRecvUpdateSlot(QString);
    void on_pPBSendButton_clicked();

signals:
    void ledWriteSig(int);
};

#endif // TAB2SOCKECLIENT_H
