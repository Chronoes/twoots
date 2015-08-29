#ifndef TWITTERREQUESTS_H
#define TWITTERREQUESTS_H

#include <QObject>
#include <QUrl>
#include "twitterapi.h"

class TwitterRequests : public QObject {
    Q_OBJECT
public:
    explicit TwitterRequests(QObject* parent = 0);
    void getHomeTimeline();
private:
    TwitterAPI* API;

signals:
    void timelineReceived(QString replyString);
public slots:
    void onReplyReceived(QNetworkReply* reply);
};

#endif // TWITTERREQUESTS_H
