#ifndef TWITTERAPI_H
#define TWITTERAPI_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariantMap>

#include "o2/o2globals.h"
#include "o2/o1requestor.h"
#include "o2/o2settingsstore.h"
#include "o2/o1twitter.h"
#include "o2/oxtwitter.h"

class TwitterAPI : public QObject {
    Q_OBJECT
public:
    explicit TwitterAPI(QObject *parent = 0);

signals:

public slots:
    void authenticate();

private:
    O1Twitter *twitter_auth;
    O2SettingsStore *settings;
};

#endif // TWITTERAPI_H
