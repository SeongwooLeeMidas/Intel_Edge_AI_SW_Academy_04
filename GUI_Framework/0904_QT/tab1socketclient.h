#ifndef TAB1SOCKECLIENT_H
#define TAB1SOCKECLIENT_H

#include <QWidget>
#include <QTime>
#include "socketclient.h"
#include "keyboard.h"
namespace Ui {
class Tab1SocketClient;
}

class Tab1SocketClient : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1SocketClient(QWidget *parent = nullptr);
    ~Tab1SocketClient();

private slots:
    void on_pPBServerConnect_clicked(bool checked);

private:
    Ui::Tab1SocketClient *ui;
    SocketClient *pSocketClient;
    Keyboard* pKeyBoard;

private slots:
    void socketRecvUpdateSlot(QString);
    void on_pPBSendButton_clicked();
    void keyboardSlot();

signals:
    void ledWriteSig(int);
};

#endif // TAB2SOCKECLIENT_H
