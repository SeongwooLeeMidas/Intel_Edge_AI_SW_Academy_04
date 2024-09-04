#ifndef KEYLED_H
#define KEYLED_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QSocketNotifier>
#include <QDebug>

class KeyLed : public QWidget
{
    Q_OBJECT

public:
    explicit KeyLed(QWidget *parent = nullptr);
    ~KeyLed();

private:
    QFile * pFile;
    int keyledFd;
    QSocketNotifier * pKeyLedNotifier;
private slots:
    void readKeyData(int);
    void writeLedData(int);
signals:
    void updateKeydataSig(int);
};

#endif // KEYLED_H
