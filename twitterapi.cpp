#include "twitterapi.h"
#include <QSettings>

QSettings tokens("private_tokens.ini", QSettings::IniFormat);
QString consumer_key(tokens.value("tokens/ACCESS_TOKEN").toString());
QString consumer_secret(tokens.value("tokens/ACCESS_TOKEN_SECRET").toString());

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
    // <--Add connections here later-->
    twitter_auth->link();
}

