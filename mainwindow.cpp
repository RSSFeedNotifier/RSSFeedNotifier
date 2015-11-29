#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rssparser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabels(QStringList() << "Feed");

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fetch() {
    xml.clear();
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
    reply->deleteLater();
}

void MainWindow::parseXML() {
    RSSParser::RSSChannel *channel = new RSSParser::RSSChannel( &xml );
    qDebug() << channel->title;

    addTreeRoot(channel->title, channel);
}

void MainWindow::addTreeRoot(QString name, RSSParser::RSSChannel *channel) {
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    //add the root
    treeItem->setText(0,name);

    //add the feed items
    for( RSSParser::RSSFeedItem *item : channel->items ) {
        addTreeChild(treeItem, item);
    }
    delete channel;

}

void MainWindow::addTreeChild(QTreeWidgetItem *parent, RSSParser::RSSFeedItem *item) {
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    treeItem->setText(0,item->title);
    treeItem->setText(1, item->link);

    parent->addChild(treeItem);

}

void MainWindow::itemActivated(QTreeWidgetItem *item) {
    ui->webView->load(QUrl(item->text(1)));
    ui->webView->show();
}










