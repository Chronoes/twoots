#include "twitterapi.h"
#include <QDebug>
#include <QDesktopServices>

#include "o2/o2globals.h"

#include "keys.h"

TwitterAPI::TwitterAPI(QObject* parent) :
    QObject(parent) {
    TwitterAuth = new O1Twitter(this);
    settings = new O2SettingsStore(O2_ENCRYPTION_KEY);

    settings->setGroupKey("twitter");
    TwitterAuth->setStore(settings);

    manager = new QNetworkAccessManager(this);
    requestor = new O1Requestor(manager, TwitterAuth, this);
}

TwitterAPI::~TwitterAPI() {
    delete requestor;
    delete manager;
    delete settings;
    delete TwitterAuth;

}

void TwitterAPI::authenticate() {
    TwitterAuth->setClientId(CONSUMER_KEY);
    TwitterAuth->setClientSecret(CONSUMER_SECRET);

    connect(TwitterAuth, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSuccess()));
    connect(TwitterAuth, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(TwitterAuth, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    TwitterAuth->link();
}

QNetworkRequest TwitterAPI::request(const QUrl& url) {
    QNetworkRequest nRequest(url);
    if (!TwitterAuth->linked()) {
        qDebug() << TwitterAuth->token();
        qDebug() << "TwitterAPI::Not linked to Twitter!";
        return nRequest;
    }

    nRequest.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);
    qDebug() << "TwitterAPI::Request created";
    return nRequest;
}

void TwitterAPI::get(const QUrl& url, QList<O1RequestParameter>& reqParams) {
    QNetworkReply* reply = requestor->get(request(url), reqParams);
    connect(reply, SIGNAL(finished()), this, SLOT(onReply()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

void TwitterAPI::get(const QUrl& url) {
    QList<O1RequestParameter> list = QList<O1RequestParameter>();
    return get(url, list);
}

void TwitterAPI::post(const QUrl& url, QList<O1RequestParameter>& reqParams, QByteArray& data) {
    QNetworkReply* reply = requestor->post(request(url), reqParams, data);
    connect(reply, SIGNAL(finished()), this, SLOT(onReply()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

void TwitterAPI::post(const QUrl& url, QByteArray& data) {
    QList<O1RequestParameter> list = QList<O1RequestParameter>();
    return post(url, list, data);
}

void TwitterAPI::onLinkingSuccess() {
    O1Twitter* o1t = qobject_cast<O1Twitter* >(sender());

    QVariantMap extraTokens = o1t->extraTokens();

    if (!extraTokens.isEmpty()) {
        emit extraTokensReady(extraTokens);

        qDebug() << "Extra tokens in response:";
        foreach (QString key, extraTokens.keys()) {
            qDebug() << "\t" << key << ":" << extraTokens.value(key).toString();
        }
    }
    emit linkingSucceeded();
    qDebug() << "TwitterAPI::Linking success!";
}

void TwitterAPI::onLinkingFailed() {
    qDebug() << "TwitterAPI::Linking failed!";
}

void TwitterAPI::onReply() {
    QNetworkReply* reply = qobject_cast<QNetworkReply* >(sender());
    if (reply->error())
        emit replyFailed();
    else
        emit replyReceived(reply);
}

void TwitterAPI::onError(QNetworkReply::NetworkError code) {
    qDebug() << "TwitterAPI::Network reply has failed: code " << code;
}

void TwitterAPI::onOpenBrowser(const QUrl& url) {
    qDebug() << "TwitterAPI::Opening browser with url" << url.toString();
    QDesktopServices::openUrl(url);
}
