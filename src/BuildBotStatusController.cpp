/*
 * BuildBotStatusController.cpp
 *
 *  Created on: 13.05.2015
 *      Author: "Peter Schuller <ps@pzzz.de>"
 */

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <QSettings>

#include "BuildBotStatusController.hpp"
#include "StatusRequest.hpp"

using namespace bb::cascades;

BuildBotStatusController::BuildBotStatusController() {
    m_useHttps = false;
    m_useHttpBasicAuth = false;

    qmlRegisterType<StatusRequest>("BuildBot.StatusRequest", 1, 0, "StatusRequest");

    QmlDocument* qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_buildbotstatus", this);

    AbstractPane* root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);
}

void BuildBotStatusController::setBuildBotUrl(const QString &url) {
    if (m_buildBotUrl == url) return;
    m_buildBotUrl = url;
}

QString BuildBotStatusController::getBuildBotUrl() const
{
    return m_buildBotUrl;
}

void BuildBotStatusController::setUseHttps(const bool value) {
    if (m_useHttps == value) return;
    m_useHttps = value;
}

bool BuildBotStatusController::getUseHttps() const
{
    return m_useHttps;
}

void BuildBotStatusController::setUseHttpBasicAuth(const bool value) {
    if (m_useHttpBasicAuth == value) return;
    m_useHttpBasicAuth = value;
}

bool BuildBotStatusController::getUseHttpBasicAuth() const
{
    return m_useHttpBasicAuth;
}

void BuildBotStatusController::setBasicAuthUser(const QString &user) {
    if (!m_useHttpBasicAuth) return;
    if (m_basicAuthUser == user) return;
    m_basicAuthUser = user;
}

QString BuildBotStatusController::getBasicAuthUser() const
{
    if (!m_useHttpBasicAuth) return false;
    return m_basicAuthUser;
}

void BuildBotStatusController::setBasicAuthPass(const QString &pass) {
    if (!m_useHttpBasicAuth) return;
    if (m_basicAuthPass == pass) return;
    m_basicAuthPass = pass;
}

QString BuildBotStatusController::getBasicAuthPass() const
{
    if (!m_useHttpBasicAuth) return false;
    return m_basicAuthPass;
}
