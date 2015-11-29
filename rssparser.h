#ifndef RSSPARSER_H
#define RSSPARSER_H

#include <vector>

#include <QString>

namespace RSSParser
{
    class RSSFeedItem
    {
    public:
      QString title;
      QString link;
      QString description;
      QString pubDate;
      QString guid;
      QString date;
    public:
      RSSFeedItem();
      RSSFeedItem(
          QString title,
          QString link,
          QString description,
          QString pubDate,
          QString guid,
          QString date
      );
      void print();
    };

    class RSSChannel
    {
    public:
        QString title;
        QString link;
        QString description;
        QString language;
        std::vector<RSSFeedItem *> items;
    public:
        RSSChannel();
        RSSChannel(
          QString title,
          QString link,
          QString description,
          QString language
        );
        RSSChannel( QXmlStreamReader *xml );
        void add( RSSFeedItem *item );
        void print();
    };


}

#endif // RSSPARSER_H

