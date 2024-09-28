#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    CustomWidget(QWidget *parent = nullptr);
    ~CustomWidget();

signals:
        void widgetClicked();
public slots:
        void processClick();

};
#endif // CUSTOMWIDGET_H
