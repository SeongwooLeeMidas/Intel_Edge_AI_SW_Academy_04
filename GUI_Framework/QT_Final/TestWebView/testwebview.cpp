#include "testwebview.h"
#include "ui_testwebview.h"

TestWebView::TestWebView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWebView)
{
    ui->setupUi(this);
    pWebView1_1 = new QWebEngineView(this);
    pWebView1_1->load(QUrl(QStringLiteral("http://10.10.141.30:8080/?action=stream")));
    ui->pQVBoxLayout1_1->addWidget(pWebView1_1);

    pWebView1_2 = new QWebEngineView(this);
    pWebView1_2->load(QUrl(QStringLiteral("http://10.10.141.30:8080/?action=stream")));
    ui->pQVBoxLayout1_2->addWidget(pWebView1_2);


    pWebView2_1 = new QWebEngineView(this);
    pWebView2_1->load(QUrl(QStringLiteral("http://10.10.141.30:8080/?action=stream")));
    ui->pQVBoxLayout2_1->addWidget(pWebView2_1);

    pWebView2_2 = new QWebEngineView(this);
    pWebView2_2->load(QUrl(QStringLiteral("http://10.10.141.30:8080/?action=stream")));
    ui->pQVBoxLayout2_2->addWidget(pWebView2_2);

    pWebView2 = new QWebEngineView(this);
    pWebView2->load(QUrl(QStringLiteral("http://www.google.com")));
    ui->pQVBoxLayout2->addWidget(pWebView2);
}

TestWebView::~TestWebView()
{
    delete ui;
}

