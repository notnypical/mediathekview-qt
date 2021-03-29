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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QAction>
#include <QByteArray>
#include <QCloseEvent>
#include <QMainWindow>
#include <QToolBar>

#include "preferences.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setApplicationState(const QByteArray &state = QByteArray());
    QByteArray applicationState() const;

    void setApplicationGeometry(const QByteArray &geometry = QByteArray());
    QByteArray applicationGeometry() const;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onActionAboutTriggered();
    void onActionColophonTriggered();
    void onActionPreferencesTriggered();

    void onActionLiveStreamsToggled(bool checked);
    void onActionChannelsToggled(bool checked, const QString &channel);
    void onActionSelectInvertToggled(bool checked);

    void onActionUpdateTriggered();

    void onActionFullScreenTriggered();

private:
    Preferences m_preferences;

    QByteArray m_applicationState;
    QByteArray m_applicationGeometry;
    QByteArray m_preferencesDialogGeometry;

    void loadSettings();
    void saveSettings();

    QMap<QString, QStringList> m_listChannels;

    void createChannels();

    QToolBar *m_toolbarApplication;
    QToolBar *m_toolbarChannels;
    QToolBar *m_toolbarTools;
    QToolBar *m_toolbarView;
    QToolBar *m_toolbarHelp;

    void createActions();
    void createMenus();
    void createToolBars();

    void updateActionChannels(bool invert = false);
    void updateActionFullScreen();

    QAction *m_actionAbout;
    QAction *m_actionColophon;
    QAction *m_actionPreferences;
    QAction *m_actionQuit;

    QAction *m_actionLiveStreams;
    QList<QAction *> m_actionChannels;
    QAction *m_actionSelectInvert;

    QAction *m_actionUpdate;

    QAction *m_actionFullScreen;
    QAction *m_actionToolbarApplication;
    QAction *m_actionToolbarChannels;
    QAction *m_actionToolbarTools;
    QAction *m_actionToolbarView;
    QAction *m_actionToolbarHelp;
};

#endif // MAIN_WINDOW_H
