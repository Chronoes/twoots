#ifndef REQUEST_URLS
#define REQUEST_URLS

#include <QString>
#include <QUrl>

const QString REQUEST_ROOT("https://api.twitter.com/1.1/");

const QUrl HOME_TIMELINE(REQUEST_ROOT + "statuses/home_timeline.json");

#endif // REQUEST_URLS
