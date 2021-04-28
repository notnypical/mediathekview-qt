#
# Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
#
# This file is part of MediathekView-Qt, <https://github.com/notnypical/mediathekview-qt>.
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
    colophon_dialog.cpp \
    colophon_pages.cpp \
    dialog_title_box.cpp \
    keyboard_shortcuts_dialog.cpp \
    keyboard_shortcuts_page.cpp \
    main.cpp \
    main_window.cpp \
    preferences.cpp \
    preferences_dialog.cpp \
    preferences_page_database.cpp \
    preferences_page_general.cpp

HEADERS += \
    about_dialog.h \
    colophon_dialog.h \
    colophon_pages.h \
    dialog_title_box.h \
    keyboard_shortcuts_dialog.h \
    keyboard_shortcuts_page.h \
    main_window.h \
    preferences.h \
    preferences_dialog.h \
    preferences_page_database.h \
    preferences_page_general.h

TRANSLATIONS += \
    translations/mediathekview-qt_de.ts \
    translations/mediathekview-qt_en.ts \
    translations/mediathekview-qt_he.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    translations.qrc
