#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QtNetwork>
#include <QDebug>
#include <QNetworkAccessManager>

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void fetch();
    void replyFinished(QNetworkReply *reply);

private:
    Ui::MainWindowClass *ui;

    void parseXML();

    QXmlStreamReader xml;
    QNetworkAccessManager *manager;
    QNetworkReply * reply;
};

#endif // MAINWINDOW_H
