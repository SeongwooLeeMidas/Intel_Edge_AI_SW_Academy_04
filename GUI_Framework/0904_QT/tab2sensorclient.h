#ifndef TAB2SENSORCLIENT_H
#define TAB2SENSORCLIENT_H

#include <QWidget>

namespace Ui {
class Tab2SensorClient;
}

class Tab2SensorClient : public QWidget
{
    Q_OBJECT

public:
    explicit Tab2SensorClient(QWidget *parent = nullptr);
    ~Tab2SensorClient();

private:
    Ui::Tab2SensorClient *ui;
};

#endif // TAB2SENSORCLIENT_H
