#ifndef RSSPARSER_H
#define RSSPARSER_H

#include <vector>

namespace RSSParser
{
    class RSSFeedItem
    {
    private:
      const char *title;
      const char *link;
      const char *description;
      const char *pubDate;
      const char *guid;
      const char *date;

    public:
      RSSFeedItem(
        const char *title,
        const char *link,
        const char *description,
        const char *pubDate,
        const char *guid,
        const char *date
      );
      void print();
    };

    class RSSChannel
    {
    private:
        const char *title;
        const char *link;
        const char *description;
        const char *language;
        std::vector<RSSFeedItem> items;
    public:
        RSSChannel(
            const char *title,
            const char *link,
            const char *description,
            const char *language
        );
        void print();
    };


    RSSChannel *parseDocument( QXmlStreamReader *xml );

}

#endif // RSSPARSER_H

