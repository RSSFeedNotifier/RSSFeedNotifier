#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rssparser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fetch() {
    // Set up network manager
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    // Get the rss feed url from the GUI
    QUrl url(ui->lineEdit->text());

    qDebug() << url;
    qDebug() << url.path();
    qDebug() << url.host();
    // Do a network request
    manager->get(QNetworkRequest(url));
}

void MainWindow::replyFinished(QNetworkReply *reply) {
    // Check for connection status
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200) {
        qDebug() << "error!";
        qDebug() << reply->errorString();
    } else {
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();

        xml.addData(reply->readAll());
        // Time to parse
        parseXML();

    }
}

void MainWindow::parseXML() {

    RSSParser::RSSChannel *channel = new RSSParser::RSSChannel( &xml );
    qDebug() << channel->items.size();
    channel->print();

}


