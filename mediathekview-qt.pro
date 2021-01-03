#
# Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
#
# This file is part of MediathekView-Qt.
#
# MediathekView-Qt is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MediathekView-Qt is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MediathekView-Qt.  If not, see <https://www.gnu.org/licenses/>.
#

QT += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about_dialog.cpp \
    colophon_about_page.cpp \
    colophon_authors_page.cpp \
    colophon_credits_page.cpp \
    colophon_dialog.cpp \
    colophon_environment_page.cpp \
    colophon_license_page.cpp \
    dialog_title_box.cpp \
    main.cpp \
    main_window.cpp \
    preferences_database_settings.cpp \
    preferences_dialog.cpp \
    preferences_general_settings.cpp \
    settings.cpp

HEADERS += \
    about_dialog.h \
    colophon_about_page.h \
    colophon_authors_page.h \
    colophon_credits_page.h \
    colophon_dialog.h \
    colophon_environment_page.h \
    colophon_license_page.h \
    dialog_title_box.h \
    main_window.h \
    preferences_database_settings.h \
    preferences_dialog.h \
    preferences_general_settings.h \
    settings.h

TRANSLATIONS += \
    translations/mediathekview-qt_en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
