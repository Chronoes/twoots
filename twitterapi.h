#ifndef TWITTERAPI_H
#define TWITTERAPI_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariantMap>

#include "o2/o1twitter.h"
#include "o2/oxtwitter.h"

class TwitterAPI : public QObject
{
    Q_OBJECT
public:
    explicit TwitterAPI(QObject *parent = 0);

signals:

public slots:
};

#endif // TWITTERAPI_H
