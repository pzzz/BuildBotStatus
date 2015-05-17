/*
 * main.cpp
 *
 *  Created on: 13.05.2015
 *      Author: "Peter Schuller <ps@pzzz.de>"
 */

#include "BuildBotStatusController.hpp"

#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>

#include <Qt/qdeclarativedebug.h>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);
    BuildBotStatusController bbscontroller;
    return Application::exec();
}
