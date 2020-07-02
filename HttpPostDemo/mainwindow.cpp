#include "mainwindow.h"
#include <QDebug>
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString testData = ui->textEdit->toPlainText();
    qDebug() << "PostData:" << testData;

    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

    request.setUrl(QUrl("http://192.168.0.14/ediservices/packready.action"));
    //request.setUrl(QUrl("http://www.baidu.com"));
    //request.setRawHeader("User-Agent", "TG6000 1.0");
    request.setHeader(QNetworkRequest::UserAgentHeader,"TG6000 1.0");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QNetworkReply* reply = naManager->post(request, testData.toUtf8());
}

void MainWindow::requestFinished(QNetworkReply* reply)
{
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
    qDebug() << "2status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
    qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError)
    {
        qDebug() << "Failed: " << err << reply->errorString();
    }
    else
    {
        // 获取返回内容
        qDebug() << "data :"<< reply->readAll();
    }
}
