/**
 * Copyright 2020 NotNypical, <https://notnypical.github.io>.
 *
 * This file is part of MediathekView-Qt.
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
#include <QCommandLineParser>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("NotNypical"));
    app.setOrganizationDomain(QStringLiteral("https://notnypical.github.io"));
    app.setApplicationName(QStringLiteral("MediathekView-Qt"));
    app.setApplicationDisplayName(QStringLiteral("MediathekView-Qt"));
    app.setApplicationVersion(QStringLiteral("0.1.0"));

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("%1 - %2").arg(app.applicationName(), QStringLiteral("A front-end tool for the MediathekView database")));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    MainWindow window;
    window.show();

    return app.exec();
}
