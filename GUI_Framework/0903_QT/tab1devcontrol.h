#ifndef TAB1DEVCONTROL_H
#define TAB1DEVCONTROL_H

#include <QWidget>
#include <QTimer>
#include <QButtonGroup>
#include <QDial>
#include "keyled.h"

namespace Ui {
class Tab1DevControl;
}

class Tab1DevControl : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1DevControl(QWidget *parent = nullptr);
    ~Tab1DevControl();
    QDial *getpDial();

private slots:
    void on_pPBQuit_clicked();
    void slotTimerStartButton(bool);
    void slotDialSetValue();
    void on_pCBtimerValue_currentIndexChanged(const QString &arg1);
    void slotKeyCheckBoxUpdate(int);
    void slotKeyCheckBoxUpdateMouse(int);

private:
    Ui::Tab1DevControl *ui;
    KeyLed *pKeyLed;
    QTimer *pQTimer;
    QButtonGroup *pQButtonGroup;
    QCheckBox *pQCheckBoxArray[8];

    int lcdData;
signals:
     void writeLedDataSig(int);
};

#endif // TAB1DEVCONTROL_H
