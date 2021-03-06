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

#include "preferences_page_database.h"

#include <QLabel>


PreferencesPageDatabase::PreferencesPageDatabase(QWidget *parent)
    : QWidget(parent)
{
    // Title
    auto *title = new QLabel(tr("<strong style=\"font-size:large;\">%1</strong>").arg(this->title()));

    //
    // Content


    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addStretch(1);
}


void PreferencesPageDatabase::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString PreferencesPageDatabase::title() const
{
    return tr("Database");
}


void PreferencesPageDatabase::onPreferencesChanged()
{
    emit preferencesChanged();
}
