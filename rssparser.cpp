#include <iostream>
#include <cstring>

#include <QXmlStreamReader>
#include <QDebug>

#include "rssparser.h"

using namespace std;

namespace RSSParser
{

    /** An RSS Feed has the following structure:
        <rss>
          <channel>
            ...
            <item> ... </item>
            <item> ... </item>
            ...
          </feed>
        </rss>
    */

    RSSFeedItem::RSSFeedItem()
    {

    }

    /** Representation of a channel item.
    */
    RSSFeedItem::RSSFeedItem(
#define ATTR_ITEM( name ) \
      QString name,
RSS_FEED_ITEM_ATTR_LIST
#undef ATTR_ITEM
        ...
    )
    {
#define ATTR_ITEM( name ) \
      this->name = name;
RSS_FEED_ITEM_ATTR_LIST
#undef ATTR_ITEM
    }

    void RSSFeedItem::print()
    {
        qDebug() << title;
    }

    RSSChannel::RSSChannel()
    {

    }

    RSSChannel::RSSChannel(
#define ATTR_ITEM( name ) \
      QString name,
RSS_CHANNEL_ATTR_LIST
#undef ATTR_ITEM
        ...
    )
    {
#define ATTR_ITEM( name ) \
      this->name = name;
RSS_CHANNEL_ATTR_LIST
#undef ATTR_ITEM
    }

    RSSChannel::RSSChannel( QXmlStreamReader *xml )
    {

        RSSFeedItem *item = NULL;

        enum ParseState {
            STATE_START,
            STATE_CHANNEL,
            STATE_ITEM,
            STATE_OTHER,
            STATE_END
        } state = STATE_START;

        int depth = 0;

        while( !xml->atEnd() ) {

            switch( state )
            {
                case STATE_CHANNEL:
                    qDebug() << "RSS" << xml->name();
                break;
                case STATE_ITEM:
                    qDebug() << "ITEM" << xml->name();
                break;
                case STATE_OTHER:
                    qDebug() << "OTHER" << xml->name();
                break;
                case STATE_START:
                    qDebug() << "START" << xml->name();
                break;
                case STATE_END:
                    qDebug() << "END" << xml->name();
                break;
            default:
                break;
            }

            // do processing
            switch( xml->tokenType() )
            {
            case QXmlStreamReader::StartElement:
            {
                switch( state )
                {
                case STATE_START:
                {
                    if( "channel" == xml->name() )
                    {
                        RSSChannel();
                        state = STATE_CHANNEL;
                    }
                    break;
                }
                case STATE_CHANNEL:
                {
#define ATTR_ITEM( nname ) \
                    if( #nname == xml->name() ) \
                    { \
                        nname = xml->readElementText(); \
                    } \
                    else
RSS_CHANNEL_ATTR_LIST
#undef ATTR_ITEM
                    if( "item" == xml->name() )
                    {
                        item = new RSSFeedItem();
                        add( item );
                        state = STATE_ITEM;
                    }
                    else
                    {
                        state = STATE_OTHER;
                    }
                    break;
                }
                case STATE_ITEM:
                {
#define ATTR_ITEM( nname ) \
                    if( #nname == xml->name() ) \
                    { \
                        item->nname = xml->readElementText(); \
                    } \
                    else
RSS_FEED_ITEM_ATTR_LIST
#undef ATTR_ITEM
                    {

                    }
                    break;
                }
                case STATE_OTHER:
                {
                    depth++;
                }
                default:
                    break;
                }
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                switch( state )
                {
                case STATE_CHANNEL:
                {
                    state = STATE_END;
                }
                case STATE_ITEM:
                {
                    if( "item" == xml->name() )
                    {
                        state = STATE_CHANNEL;
                    }
                    break;
                }
                case STATE_OTHER:
                {
                    if( 0 == depth )
                    {
                        state = STATE_CHANNEL;
                    }
                    else
                    {
                        depth--;
                    }
                }
                default:
                    break;
                }
            }
            default:
                break;
            }

            // continue
            xml->readNext();
        }
        if (xml->hasError()) {
            // do error handling
        }
    }

    void RSSChannel::add( RSSFeedItem *item )
    {
        items.push_back( item );
    }

    void RSSChannel::print()
    {
        qDebug() << title;
        for( RSSFeedItem *item : items )
        {
            item->print();
        }
    }
}
