#include "twitterapi.h"
#include <QSettings>
#include <QDebug>
#include <QDesktopServices>

QSettings tokens("private_tokens.ini", QSettings::IniFormat);
/*
QString consumer_key(tokens.value("ACCESS_TOKEN").toString());
QString consumer_secret(tokens.value("ACCESS_TOKEN_SECRET").toString());
*/
QString consumer_key = tokens.value("CONSUMER_KEY").toString();
QString consumer_secret = tokens.value("CONSUMER_SECRET").toString();

TwitterAPI::TwitterAPI(QObject *parent) :
    QObject(parent) {
}

void TwitterAPI::authenticate() {
    twitter_auth = new O1Twitter(this);
    twitter_auth->setClientId(consumer_key);
    twitter_auth->setClientSecret(consumer_secret);

    settings = new O2SettingsStore(O2_ENCRYPTION_KEY);
    settings->setGroupKey("twitter");
    twitter_auth->setStore(settings);
    qDebug() << consumer_key;
    // <--Add connections here later-->
    connect(twitter_auth, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSuccess()));
    connect(twitter_auth, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(twitter_auth, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    twitter_auth->link();
}

void TwitterAPI::get_timeline() {
    if (!twitter_auth->linked()) {
        qDebug() << twitter_auth->token();
        qDebug() << "TwitterAPI::Not linked to Twitter!";
        return;
    }
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    O1Requestor *requestor = new O1Requestor(manager, twitter_auth, this);

    QUrl url("https://api.twitter.com/1.1/statuses/user_timeline.json");
    QList<O1RequestParameter> req_params = QList<O1RequestParameter>();

    req_params << O1RequestParameter(QByteArray("screen_name"), QByteArray("Chronoes"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);
    reply = requestor->get(request, req_params);
    connect(reply, SIGNAL(finished()), this, SLOT(onReply()));
}

void TwitterAPI::onLinkingSuccess() {
    O1Twitter* o1t = qobject_cast<O1Twitter *>(sender());

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
    emit timelineReceived(QString(reply->readAll()));
}

void TwitterAPI::onOpenBrowser(const QUrl &url) {
    qDebug() << "Opening browser with url" << url.toString();
    QDesktopServices::openUrl(url);
}
