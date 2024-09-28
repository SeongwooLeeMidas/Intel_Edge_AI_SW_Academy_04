#ifndef TESTWEBVIEW_H
#define TESTWEBVIEW_H

#include <QWidget>
#include <QWebEngineView>
QT_BEGIN_NAMESPACE
namespace Ui { class TestWebView; }
QT_END_NAMESPACE

class TestWebView : public QWidget
{
    Q_OBJECT

public:
    TestWebView(QWidget *parent = nullptr);
    ~TestWebView();

private:
    Ui::TestWebView *ui;
    QWebEngineView *pWebView1_1;
    QWebEngineView *pWebView1_2;
    QWebEngineView *pWebView2_1;
    QWebEngineView *pWebView2_2;
    QWebEngineView *pWebView2;

};
#endif // TESTWEBVIEW_H
