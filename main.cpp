/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of MediathekView-Qt, <https://github.com/notnypical/mediathekview-qt>.
 *
 * MediathekView-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MediathekView-Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MediathekView-Qt.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "main_window.h"

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>


int showLanguageList()
{
    QString usage = QCoreApplication::instance()->arguments().constFirst();
    usage += QStringLiteral(" --language <") + QCoreApplication::translate("main", "language code") + QStringLiteral(">");

    printf("%s\n\n", qPrintable(QCoreApplication::translate("main", "Usage: %1").arg(usage)));

    return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("NotNypical"));
    app.setOrganizationDomain(QStringLiteral("https://notnypical.github.io"));
    app.setApplicationName(QStringLiteral("MediathekView-Qt"));
    app.setApplicationDisplayName(QStringLiteral("MediathekView-Qt"));
    app.setApplicationVersion(QStringLiteral("0.1.0"));


    //
    // Command line

    QCommandLineOption languageListOption(QStringLiteral("language-list"),
        QCoreApplication::translate("main", "Lists available application languages."));

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "%1 - A front-end tool for the MediathekView database").arg(app.applicationName()));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(languageListOption);
    parser.process(app);

    // Command line: Language list
    if (parser.isSet(languageListOption))
        return showLanguageList();


    MainWindow window;
    window.show();

    return app.exec();
}
