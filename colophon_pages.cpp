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

#include "colophon_pages.h"

#include <QApplication>
#include <QTextBrowser>


ColophonAboutPage::ColophonAboutPage(QWidget *parent)
    : QWidget(parent)
{
    auto *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(tr("<html><body>"
        "<p>%1 is an open source front-end tool written in Qt for C++ and designed for easy access to the <a href=\"https://mediathekview.de\" title=\"Visit MediathekView's homepage\">MediathekView</a> database.</p>"
        "<p>Copyright &copy; 2020-2021 <a href=\"%2\" title=\"Visit organization's homepage\">%3</a>.</p>"
        "<p>This application is licensed under the terms of the <a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\" title=\"Visit license's homepage\">GNU General Public License, version 3</a>.</p>"
        "</body></html>").arg(QApplication::applicationName(), QApplication::organizationDomain(), QApplication::organizationName()));

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(textBox);
}


void ColophonAboutPage::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString ColophonAboutPage::title() const
{
    return tr("About");
}


ColophonAuthorsPage::ColophonAuthorsPage(QWidget *parent)
    : QWidget(parent)
{
    auto *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(tr("<html><body>"
        "<dl><dt><strong>NotNypical</strong></dt>"
            "<dd>Created and developed by <a href=\"https://notnypical.github.io\" title=\"Visit author's homepage\">NotNypical</a>.</dd></dl>"
        "</body></html>"));

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(textBox);
}


void ColophonAuthorsPage::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString ColophonAuthorsPage::title() const
{
    return tr("Authors");
}


ColophonCreditsPage::ColophonCreditsPage(QWidget *parent)
    : QWidget(parent)
{
    auto *textBox = new QTextBrowser;
    textBox->setFrameStyle(QFrame::NoFrame);
    textBox->setStyleSheet(QStringLiteral("background-color:transparent;"));
    textBox->setOpenExternalLinks(true);
    textBox->setHtml(tr("<html><body>"
        "<dl><dt><strong>BreezeIcons project</strong></dt>"
            "<dd>Application logo and icons made by <a href=\"https://api.kde.org/frameworks/breeze-icons/html/\" title=\"Visit project's homepage\">BreezeIcons project</a> "
                "from <a href=\"https://kde.org\" title=\"Visit organization's homepage\">KDE</a> "
                "are licensed under <a href=\"https://www.gnu.org/licenses/lgpl-3.0.en.html\" title=\"Visit license's homepage\">LGPLv3</a>.</dd></dl>"
        "</body></html>"));

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(textBox);
}


void ColophonCreditsPage::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString ColophonCreditsPage::title() const
{
    return tr("Credits");
}
