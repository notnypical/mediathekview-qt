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
#include <QMenuBar>
#include <QScreen>
#include <QToolBar>

#include "about_dialog.h"
#include "colophon_dialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/16/mediathekview.svg")));

    createChannels();
    createActions();
    createMenus();
    createToolbars();

    setApplicationGeometry();
    setApplicationState();

    updateActionFullScreen();
}

MainWindow::~MainWindow()
{
}


void MainWindow::createChannels()
{
    m_listChannels[QStringLiteral("3sat")] = QStringList() << QStringLiteral("3sat");
    m_listChannels[QStringLiteral("ard")] = QStringList() << QStringLiteral("ARD") << QStringLiteral("Das Erste");
    m_listChannels[QStringLiteral("arteDe")] = QStringList() << QStringLiteral("ARTE.de");
    m_listChannels[QStringLiteral("arteFr")] = QStringList() << QStringLiteral("ARTE.fr");
    m_listChannels[QStringLiteral("br")] = QStringList() << QStringLiteral("BR") << QStringLiteral("Bayerischer Rundfunk");
    m_listChannels[QStringLiteral("dw")] = QStringList() << QStringLiteral("DW TV") << QStringLiteral("Deutsche Welle");
    m_listChannels[QStringLiteral("hr")] = QStringList() << QStringLiteral("HR") << QStringLiteral("Hessischer Rundfunk");
    m_listChannels[QStringLiteral("kika")] = QStringList() << QStringLiteral("KiKA") << QStringLiteral("Kinderkanal von ARD und ZDF");
    m_listChannels[QStringLiteral("mdr")] = QStringList() << QStringLiteral("MDR") << QStringLiteral("Mitteldeutscher Rundfunk");
    m_listChannels[QStringLiteral("ndr")] = QStringList() << QStringLiteral("NDR") << QStringLiteral("Norddeutscher Rundfunk");
    m_listChannels[QStringLiteral("orf")] = QStringList() << QStringLiteral("ORF") << QStringLiteral("Österreichischer Rundfunk");
    m_listChannels[QStringLiteral("phoenix")] = QStringList() << QStringLiteral("phoenix");
    m_listChannels[QStringLiteral("rbb")] = QStringList() << QStringLiteral("RBB") << QStringLiteral("Rundfunk Berlin-Brandenburg");
    m_listChannels[QStringLiteral("sr")] = QStringList() << QStringLiteral("SR") << QStringLiteral("Saarländischer Rundfunk");
    m_listChannels[QStringLiteral("srf")] = QStringList() << QStringLiteral("SRF") << QStringLiteral("Schweizer Rundfunk");
    m_listChannels[QStringLiteral("swr")] = QStringList() << QStringLiteral("SWR") << QStringLiteral("Südwestrundfunk");
    m_listChannels[QStringLiteral("wdr")] = QStringList() << QStringLiteral("WDR") << QStringLiteral("Westdeutscher Rundfunk");
    m_listChannels[QStringLiteral("zdf")] = QStringList() << QStringLiteral("ZDF") << QStringLiteral("Zweites Deutsches Fernsehen");
}


void MainWindow::createActions()
{
    // Actions: Application
    m_actionAbout = new QAction(tr("About %1").arg(QApplication::applicationName()), this);
    m_actionAbout->setObjectName(QStringLiteral("actionAbout"));
    m_actionAbout->setIcon(QIcon(QStringLiteral(":/icons/apps/16/mediathekview.svg")));
    m_actionAbout->setIconText(tr("About"));
    m_actionAbout->setToolTip(tr("Brief description of the application"));
    connect(m_actionAbout, &QAction::triggered, this, &MainWindow::onActionAboutTriggered);

    m_actionColophon = new QAction(tr("Colophon"), this);
    m_actionColophon->setObjectName(QStringLiteral("actionColophon"));
    m_actionColophon->setIconText(tr("Colophon"));
    m_actionColophon->setToolTip(tr("Lengthy description of the application"));
    connect(m_actionColophon, &QAction::triggered, this, &MainWindow::onActionColophonTriggered);

    m_actionPreferences = new QAction(tr("Preferences…"), this);
    m_actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
    m_actionPreferences->setIcon(QIcon::fromTheme(QStringLiteral("configure"), QIcon(QStringLiteral(":/icons/actions/16/application-configure.svg"))));
    m_actionPreferences->setIconText(tr("Preferences"));
    m_actionPreferences->setToolTip(tr("Customize the appearance and behavior of the application"));
    connect(m_actionPreferences, &QAction::triggered, this, &MainWindow::onActionPreferencesTriggered);

    m_actionQuit = new QAction(tr("Quit"), this);
    m_actionQuit->setObjectName(QStringLiteral("actionQuit"));
    m_actionQuit->setIcon(QIcon::fromTheme(QStringLiteral("application-exit"), QIcon(QStringLiteral(":/icons/actions/16/application-exit.svg"))));
    m_actionQuit->setIconText(tr("Quit"));
    m_actionQuit->setShortcut(QKeySequence::Quit);
    m_actionQuit->setToolTip(tr("Quit the application [%1]").arg(m_actionQuit->shortcut().toString(QKeySequence::NativeText)));
    connect(m_actionQuit, &QAction::triggered, this, &MainWindow::close);

    // Actions: Channels
    m_actionLiveStreams = new QAction(tr("Live streams"), this);
    m_actionLiveStreams->setObjectName(QStringLiteral("actionLiveStreams"));
    m_actionLiveStreams->setIcon(QIcon::fromTheme(QStringLiteral("network-wireless-hotspot"), QIcon(QStringLiteral(":/icons/actions/16/live-stream.svg"))));
    m_actionLiveStreams->setIconText(tr("Live streams"));
    m_actionLiveStreams->setCheckable(true);
    m_actionLiveStreams->setToolTip(tr("Show all live streaming channels."));
    connect(m_actionLiveStreams, &QAction::toggled, [=](bool checked) { onActionLiveStreamsToggled(checked); });

    // Actions: View
    m_actionFullScreen = new QAction(this);
    m_actionFullScreen->setIconText(tr("Full Screen"));
    m_actionFullScreen->setCheckable(true);
    m_actionFullScreen->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::Key_F11) << QKeySequence::FullScreen);
    connect(m_actionFullScreen, &QAction::triggered, this, &MainWindow::onActionFullScreenTriggered);

    m_actionToolbarApplication = new QAction(tr("Show Application Toolbar"), this);
    m_actionToolbarApplication->setObjectName(QStringLiteral("actionToolbarApplication"));
    m_actionToolbarApplication->setCheckable(true);
    m_actionToolbarApplication->setChecked(true);
    m_actionToolbarApplication->setToolTip(tr("Display the Application toolbar"));
    connect(m_actionToolbarApplication, &QAction::toggled, [=](bool checked) { m_toolbarApplication->setVisible(checked); });

    m_actionToolbarChannels = new QAction(tr("Show Channels Toolbar"), this);
    m_actionToolbarChannels->setObjectName(QStringLiteral("actionToolbarChannels"));
    m_actionToolbarChannels->setCheckable(true);
    m_actionToolbarChannels->setChecked(true);
    m_actionToolbarChannels->setToolTip(tr("Display the Channels toolbar"));
    connect(m_actionToolbarChannels, &QAction::toggled, [=](bool checked) { m_toolbarChannels->setVisible(checked); });

    m_actionToolbarView = new QAction(tr("Show View Toolbar"), this);
    m_actionToolbarView->setObjectName(QStringLiteral("actionToolbarView"));
    m_actionToolbarView->setCheckable(true);
    m_actionToolbarView->setChecked(true);
    m_actionToolbarView->setToolTip(tr("Display the View toolbar"));
    connect(m_actionToolbarView, &QAction::toggled, [=](bool checked) { m_toolbarView->setVisible(checked); });

}


void MainWindow::updateActionFullScreen()
{
    if (!isFullScreen()) {
        m_actionFullScreen->setText(tr("Full Screen Mode"));
        m_actionFullScreen->setIcon(QIcon::fromTheme(QStringLiteral("view-fullscreen"), QIcon(QStringLiteral(":/icons/actions/16/view-fullscreen.svg"))));
        m_actionFullScreen->setChecked(false);
        m_actionFullScreen->setToolTip(tr("Display the window in full screen [%1]").arg(m_actionFullScreen->shortcut().toString(QKeySequence::NativeText)));
    }
    else {
        m_actionFullScreen->setText(tr("Exit Full Screen Mode"));
        m_actionFullScreen->setIcon(QIcon::fromTheme(QStringLiteral("view-restore"), QIcon(QStringLiteral(":/icons/actions/16/view-restore.svg"))));
        m_actionFullScreen->setChecked(true);
        m_actionFullScreen->setToolTip(tr("Exit the full screen mode [%1]").arg(m_actionFullScreen->shortcut().toString(QKeySequence::NativeText)));
    }
}


void MainWindow::createMenus()
{
    // Menu: Application
    auto *menuApplication = menuBar()->addMenu(tr("Application"));
    menuApplication->setObjectName(QStringLiteral("menuApplication"));
    menuApplication->addAction(m_actionAbout);
    menuApplication->addAction(m_actionColophon);
    menuApplication->addSeparator();
    menuApplication->addAction(m_actionPreferences);
    menuApplication->addSeparator();
    menuApplication->addAction(m_actionQuit);

    // Menu: Channels
    auto *menuChannels = menuBar()->addMenu(tr("Channels"));
    menuChannels->setObjectName(QStringLiteral("menuChannels"));
    menuChannels->addAction(m_actionLiveStreams);

    // Menu: View
    auto *menuView = menuBar()->addMenu(tr("View"));
    menuView->setObjectName(QStringLiteral("menuView"));
    menuView->addAction(m_actionFullScreen);
    menuView->addSeparator();
    menuView->addAction(m_actionToolbarApplication);
    menuView->addAction(m_actionToolbarChannels);
    menuView->addAction(m_actionToolbarView);
}


void MainWindow::createToolbars()
{
    // Toolbar: Application
    m_toolbarApplication = addToolBar(tr("Application Toolbar"));
    m_toolbarApplication->setObjectName(QStringLiteral("toolbarApplication"));
    m_toolbarApplication->addAction(m_actionAbout);
    m_toolbarApplication->addAction(m_actionPreferences);
    m_toolbarApplication->addSeparator();
    m_toolbarApplication->addAction(m_actionQuit);
    connect(m_toolbarApplication, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarApplication->setChecked(visible); });

    // Toolbar: Channels
    m_toolbarChannels = addToolBar(tr("Channels Toolbar"));
    m_toolbarChannels->setObjectName(QStringLiteral("toolbarChannels"));
    m_toolbarChannels->addAction(m_actionLiveStreams);
    connect(m_toolbarChannels, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarChannels->setChecked(visible); });

    // Toolbar: View
    m_toolbarView = addToolBar(tr("View Toolbar"));
    m_toolbarView->setObjectName(QStringLiteral("toolbarView"));
    m_toolbarView->addAction(m_actionFullScreen);
    connect(m_toolbarView, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarView->setChecked(visible); });
}


void MainWindow::setApplicationGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() * 2/3, availableGeometry.height() * 2/3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}


QByteArray MainWindow::applicationGeometry() const
{
    return saveGeometry();
}


void MainWindow::setApplicationState(const QByteArray &state)
{
    if (!state.isEmpty()) {
        restoreState(state);
    }
    else {
        m_actionToolbarView->setChecked(false);
    }
}


QByteArray MainWindow::applicationState() const
{
    return saveState();
}


void MainWindow::onActionAboutTriggered()
{
    auto geometry = QByteArray();

    AboutDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.exec();
}


void MainWindow::onActionColophonTriggered()
{
    auto geometry = QByteArray();

    ColophonDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.exec();
}


void MainWindow::onActionPreferencesTriggered()
{

}


void MainWindow::onActionLiveStreamsToggled(bool checked)
{

}


void MainWindow::onActionFullScreenTriggered()
{
    if (!isFullScreen())
        setWindowState(windowState() | Qt::WindowFullScreen);
    else
        setWindowState(windowState() & ~Qt::WindowFullScreen);

    updateActionFullScreen();
}
