#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QXmlStreamReader>
#include <QtNetwork>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QTreeWidget>
#include <rssparser.h>

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
    void itemActivated(QTreeWidgetItem *item);
    void onCustomContextMenu(const QPoint &point);
    void removeFeedClickedSlot();

private:
    Ui::MainWindowClass *ui;
    QMenu* contextMenu;
    QAction *removeAction;

    void parseXML();
    void addTreeRoot(QString name, RSSParser::RSSChannel *channel);
    void addTreeChild(QTreeWidgetItem *parent, RSSParser::RSSFeedItem *item);


    QXmlStreamReader xml;
    QNetworkAccessManager *manager;
    QNetworkReply * reply;
};

#endif // MAINWINDOW_H
