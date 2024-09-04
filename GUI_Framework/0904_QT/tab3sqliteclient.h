#ifndef TAB3SQLITECLIENT_H
#define TAB3SQLITECLIENT_H

#include <QWidget>

namespace Ui {
class Tab3SqliteClient;
}

class Tab3SqliteClient : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3SqliteClient(QWidget *parent = nullptr);
    ~Tab3SqliteClient();

private:
    Ui::Tab3SqliteClient *ui;
};

#endif // TAB3SQLITECLIENT_H
