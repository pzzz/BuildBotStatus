/*
 * StatusRequest.hpp
 *
 *  Created on: 14.05.2015
 *      Author: "Peter Schuller <ps@pzzz.de>"
 */

#ifndef STATUSREQUEST_HPP
#define STATUSREQUEST_HPP

#include <QObject>

class QNetworkAccessManager;

class StatusRequest : public QObject
{
    Q_OBJECT
    public:
        StatusRequest(QObject* parent = 0);

    public Q_SLOTS:
        void getBuilders(const QString &url, const bool &https, const bool &basicAuth, const QString &basicAuthUser, const QString &basicAuthPass);

    Q_SIGNALS:
        void complete(const QVariant &value);
        void error(const QString &error);

    private Q_SLOTS:
        void getBuildResults();
        void getResultsForBuilder();

    private:
        QNetworkAccessManager* m_networkAccessManager;
        QString server;
        bool secureConnection;
        bool auth;
        QString user;
        QString pass;
};

#endif
