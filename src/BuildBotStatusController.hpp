/*
 * BuildBotStatusController.hpp
 *
 *  Created on: 13.05.2015
 *      Author: "Peter Schuller <ps@pzzz.de>"
 */

#ifndef BUILDBOTSTATUSCONTROLLER_HPP
#define BUILDBOTSTATUSCONTROLLER_HPP

#include <QObject>

class BuildBotStatusController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString buildBotUrl READ getBuildBotUrl WRITE setBuildBotUrl)
    Q_PROPERTY(bool useHttps READ getUseHttps WRITE setUseHttps)
    Q_PROPERTY(bool useHttpBasicAuth READ getUseHttpBasicAuth WRITE setUseHttpBasicAuth)
    Q_PROPERTY(QString basicAuthUser READ getBasicAuthUser WRITE setBasicAuthUser)
    Q_PROPERTY(QString basicAuthPass READ getBasicAuthPass WRITE setBasicAuthPass)

public:
    BuildBotStatusController();

private:
    void setBuildBotUrl (const QString &url);
    QString getBuildBotUrl() const;

    void setUseHttps(bool value);
    bool getUseHttps() const;

    void setUseHttpBasicAuth(bool value);
    bool getUseHttpBasicAuth() const;

    void setBasicAuthUser (const QString &user);
    QString getBasicAuthUser() const;

    void setBasicAuthPass (const QString &pass);
    QString getBasicAuthPass() const;

    QString m_buildBotUrl;
    bool m_useHttps;
    bool m_useHttpBasicAuth;
    QString m_basicAuthUser;
    QString m_basicAuthPass;
};

#endif
