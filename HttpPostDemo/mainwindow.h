#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void requestFinished(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
