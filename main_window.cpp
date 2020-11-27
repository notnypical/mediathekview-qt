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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(QStringLiteral(":/icons/apps/16/mediathekview.svg")));

    createActions();
    createMenus();
    createToolbars();

    setWindowGeometry(QByteArray());
}

MainWindow::~MainWindow()
{
}


void MainWindow::createActions()
{
    // Actions: Application
    m_actionAbout = new QAction(QStringLiteral("About %1").arg(QApplication::applicationName()), this);
    m_actionAbout->setObjectName(QStringLiteral("actionAbout"));
    m_actionAbout->setIcon(QIcon(QStringLiteral(":/icons/apps/16/mediathekview.svg")));
    m_actionAbout->setToolTip(QStringLiteral("Brief description of the application"));
    connect(m_actionAbout, &QAction::triggered, this, &MainWindow::onActionAboutTriggered);

    m_actionColophon = new QAction(QStringLiteral("Colophon"), this);
    m_actionColophon->setObjectName(QStringLiteral("actionColophon"));
    m_actionColophon->setToolTip(QStringLiteral("Lengthy description of the application"));
    connect(m_actionColophon, &QAction::triggered, this, &MainWindow::onActionColophonTriggered);

}


void MainWindow::createMenus()
{
    // Menu: Application
    auto *menuApplication = menuBar()->addMenu(QStringLiteral("Application"));
    menuApplication->setObjectName(QStringLiteral("menuApplication"));
    menuApplication->addAction(m_actionAbout);
    menuApplication->addAction(m_actionColophon);

}


void MainWindow::createToolbars()
{
    // Toolbar: Application
    auto *toolbarApplication = addToolBar(QStringLiteral("Application"));
    toolbarApplication->setObjectName(QStringLiteral("toolbarApplication"));
    toolbarApplication->addAction(m_actionAbout);

}


void MainWindow::setWindowGeometry(const QByteArray &geometry)
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


QByteArray MainWindow::windowGeometry() const
{
    return saveGeometry();
}


void MainWindow::setWindowState(const QByteArray &state)
{
    if (!state.isEmpty()) {
        restoreState(state);
    }
}


QByteArray MainWindow::windowState() const
{
    return saveState();
}


void MainWindow::onActionAboutTriggered()
{

}


void MainWindow::onActionColophonTriggered()
{

}
