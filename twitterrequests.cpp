#include "twitterrequests.h"
#include "request_urls.h"
#include <QDebug>

// TODO: Find a way to identify incoming signals

TwitterRequests::TwitterRequests(QObject* parent) :
    QObject(parent) {
    API = qobject_cast<TwitterAPI* >(parent);
    qDebug() << "TwitterRequests::Initialised";
}

void TwitterRequests::getHomeTimeline() {
    qDebug() << "TwitterRequests::Timeline request sent";
    connect(API, SIGNAL(replyReceived(QNetworkReply*)), this, SLOT(onReplyReceived(QNetworkReply*)));
    API->get(HOME_TIMELINE);
}

void TwitterRequests::onReplyReceived(QNetworkReply* reply) {
    qDebug() << "TwitterRequests::Timeline request received";
    emit timelineReceived(QString(reply->readAll()));
}
