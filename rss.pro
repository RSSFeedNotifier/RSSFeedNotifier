#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T12:16:46
#
#-------------------------------------------------

QT += core \
      widgets \
      network \
      gui \
      webkitwidgets

TARGET = rss

TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           rssparser.cpp

HEADERS  += mainwindow.h \
            rssparser.h

FORMS    += mainwindow.ui
