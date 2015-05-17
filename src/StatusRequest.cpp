/*
 * StatusRequest.cpp
 *
 *  Created on: 13.05.2015
 *      Author: "Peter Schuller <ps@pzzz.de>"
 */

#include "BuildBotStatusController.hpp"
#include "StatusRequest.hpp"

#include <bb/data/JsonDataAccess>

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QSslConfiguration>
#include <QUrl>

StatusRequest::StatusRequest(QObject* parent) : QObject(parent), m_networkAccessManager(new QNetworkAccessManager(this)) {
    server = "";
    secureConnection = false;
    auth = false;
    user = "";
    pass  = "";
}

void StatusRequest::getBuilders(const QString &bburl, const bool &https, const bool &basicAuth, const QString &basicAuthUser, const QString &basicAuthPass)
{
    secureConnection = https;
    auth = basicAuth;
    user = basicAuthUser;
    pass = basicAuthPass;
    QString urlString = "http://" + bburl + "/json/builders/";
    if (https) {
        urlString = "https://" + bburl + "/json/builders/";
    }
    server = urlString;
    QNetworkRequest request = QNetworkRequest();
    request.setUrl(QUrl(urlString));

    if (https) {
        QSslConfiguration config = request.sslConfiguration();
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::TlsV1);
        request.setSslConfiguration(config);
    }

    QNetworkReply* reply = m_networkAccessManager->get(request);

    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(getBuildResults()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}

void StatusRequest::getBuildResults()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QVariantList buildersList;
    QVariantList buildResults;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                bb::data::JsonDataAccess jsonResponse;
                const QVariant buildersVariant = jsonResponse.loadFromBuffer(buffer);
                const QMap<QString, QVariant> buildersMap = buildersVariant.toMap();
                QMap<QString, QVariant>::const_iterator i;
                for (i = buildersMap.constBegin(); i != buildersMap.constEnd(); ++i) {
                    buildersList.append(i.key());
                }
                for (int i = 0; i < buildersList.count(); i++) {
                    QString builderUrl = server + buildersList.value(i).toString()+"/builds/-1";
                    QNetworkRequest request = QNetworkRequest();
                    request.setUrl(QUrl(builderUrl));

                    if (secureConnection) {
                        QSslConfiguration config = request.sslConfiguration();
                        config.setPeerVerifyMode(QSslSocket::VerifyNone);
                        config.setProtocol(QSsl::TlsV1);
                        request.setSslConfiguration(config);
                    }

                    QNetworkReply* reply = m_networkAccessManager->get(request);

                    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(getResultsForBuilder()));
                    Q_ASSERT(ok);
                    Q_UNUSED(ok);
                }
            }
        } else {
            emit error("HTTP Error: "+reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    } else {
        emit error("Unable to connect to BuildBot Server");
    }
}

void StatusRequest::getResultsForBuilder() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QString status;
    QString builder;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                bb::data::JsonDataAccess jsonResponse;
                const QVariant buildersVariant = jsonResponse.loadFromBuffer(buffer);
                const QMap<QString, QVariant> buildersMap = buildersVariant.toMap();
                QMap<QString, QVariant>::const_iterator i;
//                buildersMap const QMap<QString, QVariant>   {...}
//                    [12]    QMapNode<QString, QVariant> {...}
//                        key QString "text"
//                        value   QVariant    {...}
//                            [0] QList<QVariant> {...}
//                                [0] QVariant    {...}
//                                    [0] QString "build"
//                                [1] QVariant    {...}
//                                    [0] QString "successful"
                for (i = buildersMap.constBegin(); i != buildersMap.constEnd(); ++i) {
                    if ("builderName" == i.key()) {
                        builder = i.value().toString();
                    }
                    if ("text" == i.key()) {
                        QList<QVariant> statusList = i.value().toList();
                        if (0 != statusList.size()) {
                            QList<QVariant>::const_iterator statusIterator;
                            for (statusIterator = statusList.constBegin(); statusIterator < statusList.constEnd(); ++statusIterator) {
                                status += " "+statusIterator->toString();
                            }
                        }
                    }
                }
                emit complete(builder + " -" + status);
            }
        } else {
            emit error("HTTP Error: "+reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    } else {
        emit error("Unable to connect to BuildBot Server");
    }
}
