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
#include <QMenuBar>
#include <QScreen>
#include <QStyle>

#include "about_dialog.h"
#include "colophon_dialog.h"
#include "preferences_dialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/16/mediathekview.svg")));

    readSettings();

    createChannels();

    createActions();
    createMenus();
    createToolBars();

    setApplicationState(m_applicationState);
    setApplicationGeometry(m_applicationGeometry);

    updateActionChannels();
    updateActionFullScreen();
}

MainWindow::~MainWindow()
{
}


void MainWindow::setApplicationState(const QByteArray &state)
{
    if (!state.isEmpty()) {
        restoreState(state);
    }
    else {
        m_toolbarApplication->setVisible(true);
        m_toolbarChannels->setVisible(true);
        m_toolbarTools->setVisible(true);
        m_toolbarView->setVisible(false);
        m_toolbarHelp->setVisible(false);
    }
}


QByteArray MainWindow::applicationState() const
{
    return saveState();
}


void MainWindow::setApplicationGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        const auto availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() * 2/3, availableGeometry.height() * 2/3);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}


QByteArray MainWindow::applicationGeometry() const
{
    return saveGeometry();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (true) {
        // Application properties
        m_applicationState = m_preferences.restoreApplicationState() ? applicationState() : QByteArray();
        m_applicationGeometry = m_preferences.restoreApplicationGeometry() ? applicationGeometry() : QByteArray();

        writeSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}


void MainWindow::readSettings()
{
    QSettings settings;

    // Preferences
    m_preferences.load(settings);

    // Application and dialog properties
    m_applicationState = m_preferences.restoreApplicationState() ? settings.value(QStringLiteral("Application/State"), QByteArray()).toByteArray() : QByteArray();
    m_applicationGeometry = m_preferences.restoreApplicationGeometry() ? settings.value(QStringLiteral("Application/Geometry"), QByteArray()).toByteArray() : QByteArray();
    m_aboutDialogGeometry = settings.value(QStringLiteral("AboutDialog/Geometry"), QByteArray()).toByteArray();
    m_colophonDialogGeometry = settings.value(QStringLiteral("ColophonDialog/Geometry"), QByteArray()).toByteArray();
    m_preferencesDialogGeometry = settings.value(QStringLiteral("PreferencesDialog/Geometry"), QByteArray()).toByteArray();
}


void MainWindow::writeSettings()
{
    QSettings settings;

    // Preferences
    m_preferences.save(settings);

    // Application and dialog properties
    settings.setValue(QStringLiteral("Application/State"), m_applicationState);
    settings.setValue(QStringLiteral("Application/Geometry"), m_applicationGeometry);
    settings.setValue(QStringLiteral("AboutDialog/Geometry"), m_aboutDialogGeometry);
    settings.setValue(QStringLiteral("ColophonDialog/Geometry"), m_colophonDialogGeometry);
    settings.setValue(QStringLiteral("PreferencesDialog/Geometry"), m_preferencesDialogGeometry);
}


void MainWindow::createChannels()
{
    m_listChannels[QStringLiteral("3sat")] = QStringList() << tr("3sat") << QString("");
    m_listChannels[QStringLiteral("ard")] = QStringList() << tr("ARD") << tr("Das Erste");
    m_listChannels[QStringLiteral("arteDe")] = QStringList() << tr("ARTE.de") << QString("");
    m_listChannels[QStringLiteral("arteFr")] = QStringList() << tr("ARTE.fr") << QString("");
    m_listChannels[QStringLiteral("br")] = QStringList() << tr("BR") << tr("Bayerischer Rundfunk");
    m_listChannels[QStringLiteral("dw")] = QStringList() << tr("DW TV") << tr("Deutsche Welle");
    m_listChannels[QStringLiteral("hr")] = QStringList() << tr("HR") << tr("Hessischer Rundfunk");
    m_listChannels[QStringLiteral("kika")] = QStringList() << tr("KiKA") << tr("Kinderkanal von ARD und ZDF");
    m_listChannels[QStringLiteral("mdr")] = QStringList() << tr("MDR") << tr("Mitteldeutscher Rundfunk");
    m_listChannels[QStringLiteral("ndr")] = QStringList() << tr("NDR") << tr("Norddeutscher Rundfunk");
    m_listChannels[QStringLiteral("orf")] = QStringList() << tr("ORF") << tr("Österreichischer Rundfunk");
    m_listChannels[QStringLiteral("phoenix")] = QStringList() << tr("phoenix") << QString("");
    m_listChannels[QStringLiteral("rbb")] = QStringList() << tr("RBB") << tr("Rundfunk Berlin-Brandenburg");
    m_listChannels[QStringLiteral("sr")] = QStringList() << tr("SR") << tr("Saarländischer Rundfunk");
    m_listChannels[QStringLiteral("srf")] = QStringList() << tr("SRF") << tr("Schweizer Rundfunk");
    m_listChannels[QStringLiteral("swr")] = QStringList() << tr("SWR") << tr("Südwestrundfunk");
    m_listChannels[QStringLiteral("wdr")] = QStringList() << tr("WDR") << tr("Westdeutscher Rundfunk");
    m_listChannels[QStringLiteral("zdf")] = QStringList() << tr("ZDF") << tr("Zweites Deutsches Fernsehen");
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
    m_actionLiveStreams = new QAction(tr("Live Streams"), this);
    m_actionLiveStreams->setObjectName(QStringLiteral("actionLiveStreams"));
    m_actionLiveStreams->setIcon(QIcon::fromTheme(QStringLiteral("network-wireless-hotspot"), QIcon(QStringLiteral(":/icons/actions/16/live-stream.svg"))));
    m_actionLiveStreams->setIconText(tr("Live"));
    m_actionLiveStreams->setCheckable(true);
    m_actionLiveStreams->setToolTip(tr("Show all live streaming channels"));
    connect(m_actionLiveStreams, &QAction::toggled, [=](bool checked) { onActionLiveStreamsToggled(checked); });

    QMapIterator<QString, QStringList> it(m_listChannels);
    while (it.hasNext()) {
        it.next();

        auto text = !it.value()[1].isEmpty() ? tr("%1 (%2)").arg(it.value()[0], it.value()[1]) : it.value()[0];

        auto *channel = new QAction(text, this);
        channel->setObjectName(QStringLiteral("actionChannel_%1").arg(it.key()));
        channel->setIconText(it.value()[0]);
        channel->setCheckable(true);
        channel->setToolTip(tr("Show all programs of channel %1").arg(text));
        connect(channel, &QAction::toggled, [=](bool checked) { onActionChannelsToggled(channel->objectName(), checked); });

        m_actionChannels << channel;
    }

    m_actionSelectInvert = new QAction(tr("Invert Selection"), this);
    m_actionSelectInvert->setObjectName(QStringLiteral("actionSelectInvert"));
    m_actionSelectInvert->setIcon(QIcon::fromTheme(QStringLiteral("edit-select-invert"), QIcon(QStringLiteral(":/icons/actions/16/edit-select-invert.svg"))));
    m_actionSelectInvert->setIconText(tr("Invert"));
    m_actionSelectInvert->setCheckable(true);
    m_actionSelectInvert->setToolTip(tr("Invert list of selected channels"));
    connect(m_actionSelectInvert, &QAction::toggled, [=](bool checked) { onActionSelectInvertToggled(checked); });

    // Actions: Tools
    m_actionUpdate = new QAction(tr("Update Database"), this);
    m_actionUpdate->setObjectName(QStringLiteral("actionUpdate"));
    m_actionUpdate->setIcon(QIcon::fromTheme(QStringLiteral("edit-download"), QIcon(QStringLiteral(":/icons/actions/16/edit-download.svg"))));
    m_actionUpdate->setIconText(tr("Update"));
    m_actionUpdate->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F5));
    m_actionUpdate->setToolTip(tr("Update the local database [%1]").arg(m_actionUpdate->shortcut().toString(QKeySequence::NativeText)));
    connect(m_actionUpdate, &QAction::triggered, this, &MainWindow::onActionUpdateTriggered);

    // Actions: View
    m_actionFullScreen = new QAction(this);
    m_actionFullScreen->setObjectName(QStringLiteral("actionFullScreen"));
    m_actionFullScreen->setIconText(tr("Full Screen"));
    m_actionFullScreen->setCheckable(true);
    m_actionFullScreen->setShortcuts(QList<QKeySequence>() << QKeySequence(Qt::Key_F11) << QKeySequence::FullScreen);
    connect(m_actionFullScreen, &QAction::triggered, this, &MainWindow::onActionFullScreenTriggered);

    m_actionToolbarApplication = new QAction(tr("Show Application Toolbar"), this);
    m_actionToolbarApplication->setObjectName(QStringLiteral("actionToolbarApplication"));
    m_actionToolbarApplication->setCheckable(true);
    m_actionToolbarApplication->setToolTip(tr("Display the Application toolbar"));
    connect(m_actionToolbarApplication, &QAction::toggled, [=](bool checked) { m_toolbarApplication->setVisible(checked); });

    m_actionToolbarChannels = new QAction(tr("Show Channels Toolbar"), this);
    m_actionToolbarChannels->setObjectName(QStringLiteral("actionToolbarChannels"));
    m_actionToolbarChannels->setCheckable(true);
    m_actionToolbarChannels->setToolTip(tr("Display the Channels toolbar"));
    connect(m_actionToolbarChannels, &QAction::toggled, [=](bool checked) { m_toolbarChannels->setVisible(checked); });

    m_actionToolbarTools = new QAction(tr("Show Tools Toolbar"), this);
    m_actionToolbarTools->setObjectName(QStringLiteral("actionToolbarTools"));
    m_actionToolbarTools->setCheckable(true);
    m_actionToolbarTools->setToolTip(tr("Display the Tools toolbar"));
    connect(m_actionToolbarTools, &QAction::toggled, [=](bool checked) { m_toolbarTools->setVisible(checked); });

    m_actionToolbarView = new QAction(tr("Show View Toolbar"), this);
    m_actionToolbarView->setObjectName(QStringLiteral("actionToolbarView"));
    m_actionToolbarView->setCheckable(true);
    m_actionToolbarView->setToolTip(tr("Display the View toolbar"));
    connect(m_actionToolbarView, &QAction::toggled, [=](bool checked) { m_toolbarView->setVisible(checked); });

    m_actionToolbarHelp = new QAction(tr("Show Help Toolbar"), this);
    m_actionToolbarHelp->setObjectName(QStringLiteral("actionToolbarHelp"));
    m_actionToolbarHelp->setCheckable(true);
    m_actionToolbarHelp->setToolTip(tr("Display the Help toolbar"));
    connect(m_actionToolbarHelp, &QAction::toggled, [=](bool checked) { m_toolbarHelp->setVisible(checked); });
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
    menuChannels->addSeparator();
    menuChannels->addActions(m_actionChannels);
    menuChannels->addSeparator();
    menuChannels->addAction(m_actionSelectInvert);

    // Menu: Tools
    auto *menuTools = menuBar()->addMenu(tr("Tools"));
    menuTools->setObjectName(QStringLiteral("menuTools"));
    menuTools->addAction(m_actionUpdate);

    // Menu: View
    auto *menuView = menuBar()->addMenu(tr("View"));
    menuView->setObjectName(QStringLiteral("menuView"));
    menuView->addAction(m_actionFullScreen);
    menuView->addSeparator();
    menuView->addAction(m_actionToolbarApplication);
    menuView->addAction(m_actionToolbarChannels);
    menuView->addAction(m_actionToolbarTools);
    menuView->addAction(m_actionToolbarView);
    menuView->addAction(m_actionToolbarHelp);

    // Menu: Help
    auto *menuHelp = menuBar()->addMenu(tr("Help"));
    menuHelp->setObjectName(QStringLiteral("menuHelp"));
}


void MainWindow::createToolBars()
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
    m_toolbarChannels->setStyleSheet("*[invertChannel=true] { text-decoration: line-through; }");
    m_toolbarChannels->addAction(m_actionLiveStreams);
    m_toolbarChannels->addSeparator();
    m_toolbarChannels->addActions(m_actionChannels);
    m_toolbarChannels->addSeparator();
    m_toolbarChannels->addAction(m_actionSelectInvert);
    connect(m_toolbarChannels, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarChannels->setChecked(visible); });

    // Toolbar: Tools
    m_toolbarTools = addToolBar(tr("Tools Toolbar"));
    m_toolbarTools->setObjectName(QStringLiteral("toolbarTools"));
    m_toolbarTools->addAction(m_actionUpdate);
    connect(m_toolbarTools, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarTools->setChecked(visible); });

    // Toolbar: View
    m_toolbarView = addToolBar(tr("View Toolbar"));
    m_toolbarView->setObjectName(QStringLiteral("toolbarView"));
    m_toolbarView->addAction(m_actionFullScreen);
    connect(m_toolbarView, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarView->setChecked(visible); });

    // Toolbar: Help
    m_toolbarHelp = addToolBar(tr("Help Toolbar"));
    m_toolbarHelp->setObjectName(QStringLiteral("toolbarHelp"));
    connect(m_toolbarHelp, &QToolBar::visibilityChanged, [=](bool visible) { m_actionToolbarHelp->setChecked(visible); });
}


void MainWindow::updateActionChannels(bool invert)
{
    // Tool buttons
    for (int idx = 0; idx < m_actionChannels.size(); idx++) {

        auto *widget = m_toolbarChannels->widgetForAction(m_actionChannels[idx]);
        widget->setProperty("invertChannel", invert);
        widget->style()->unpolish(widget);
        widget->style()->polish(widget);

        if (!invert)
            m_actionChannels[idx]->setToolTip(tr("Show all programs of channel %1").arg(m_actionChannels[idx]->text()));
        else
            m_actionChannels[idx]->setToolTip(tr("Hide all programs of channel %1").arg(m_actionChannels[idx]->text()));
    }
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


void MainWindow::onActionAboutTriggered()
{
    const auto geometry = m_preferences.restoreDialogGeometry() ? m_aboutDialogGeometry : QByteArray();

    AboutDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.exec();

    m_aboutDialogGeometry = m_preferences.restoreDialogGeometry() ? dialog.dialogGeometry() : QByteArray();
}


void MainWindow::onActionColophonTriggered()
{
    const auto geometry = m_preferences.restoreDialogGeometry() ? m_colophonDialogGeometry : QByteArray();

    ColophonDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.exec();

    m_colophonDialogGeometry = m_preferences.restoreDialogGeometry() ? dialog.dialogGeometry() : QByteArray();
}


void MainWindow::onActionPreferencesTriggered()
{
    const auto geometry = m_preferences.restoreDialogGeometry() ? m_preferencesDialogGeometry : QByteArray();

    PreferencesDialog dialog(this);
    dialog.setDialogGeometry(geometry);
    dialog.setPreferences(m_preferences);
    dialog.exec();

    m_preferences = dialog.preferences();
    m_preferencesDialogGeometry = m_preferences.restoreDialogGeometry() ? dialog.dialogGeometry() : QByteArray();
}


void MainWindow::onActionLiveStreamsToggled(bool checked)
{

}


void MainWindow::onActionChannelsToggled(const QString &channel, bool checked)
{

}


void MainWindow::onActionSelectInvertToggled(bool checked)
{
    updateActionChannels(checked);
}


void MainWindow::onActionUpdateTriggered()
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
