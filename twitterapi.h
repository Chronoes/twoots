#ifndef TWITTERAPI_H
#define TWITTERAPI_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariantMap>

#include "o2/o2settingsstore.h"
#include "o2/o1twitter.h"
#include "o2/oxtwitter.h"
#include "o2/o1requestor.h"


class TwitterAPI : public QObject {
    Q_OBJECT
public:
    explicit TwitterAPI(QObject* parent = 0);
    ~TwitterAPI();
    void authenticate();
    void get(const QUrl& url, QList<O1RequestParameter>& reqParams);
    void get(const QUrl& url);
    void post(const QUrl& url, QList<O1RequestParameter>& reqParams, QByteArray& data);
    void post(const QUrl& url, QByteArray& data);

signals:
    void extraTokensReady(const QVariantMap& extraTokens);
    void linkingSucceeded();
    void replyReceived(QNetworkReply* reply);
    void replyFailed();

public slots:

private slots:
    void onLinkingSuccess();
    void onLinkingFailed();
    void onOpenBrowser(const QUrl& url);
    void onReply();
    void onError(QNetworkReply::NetworkError code);

private:
    O1Twitter* TwitterAuth;
    O2SettingsStore* settings;

    QNetworkAccessManager* manager;
    O1Requestor* requestor;

    QNetworkRequest request(const QUrl& url);
};

#endif // TWITTERAPI_H
