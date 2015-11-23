#ifndef RSSPARSER_H
#define RSSPARSER_H

#include <vector>

#include <QString>

#define RSS_CHANNEL_ATTR_LIST \
    ATTR_ITEM( title ) \
    ATTR_ITEM( link ) \
    ATTR_ITEM( description ) \
    ATTR_ITEM( language )

#define RSS_FEED_ITEM_ATTR_LIST \
    ATTR_ITEM( title ) \
    ATTR_ITEM( link ) \
    ATTR_ITEM( description ) \
    ATTR_ITEM( pubDate ) \
    ATTR_ITEM( guid ) \
    ATTR_ITEM( date )

namespace RSSParser
{
    class RSSFeedItem
    {
    public:
#define ATTR_ITEM( name ) \
      QString name;
RSS_FEED_ITEM_ATTR_LIST
#undef ATTR_ITEM
    public:
      RSSFeedItem();
      RSSFeedItem(
#define ATTR_ITEM( name ) \
      QString name,
RSS_FEED_ITEM_ATTR_LIST
#undef ATTR_ITEM
        ...
      );
      void print();
    };

    class RSSChannel
    {
    public:
#define ATTR_ITEM( name ) \
      QString name;
RSS_CHANNEL_ATTR_LIST
#undef ATTR_ITEM
        std::vector<RSSFeedItem *> items;
    public:
        RSSChannel();
        RSSChannel(
#define ATTR_ITEM( name ) \
      QString name,
RSS_CHANNEL_ATTR_LIST
#undef ATTR_ITEM
            ...
        );
        void add( RSSFeedItem *item );
        void print();
    };

    RSSChannel *parseDocument( QXmlStreamReader *xml );

}

#endif // RSSPARSER_H

