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

#include "preferences_general_settings.h"

#include <QLabel>


PreferencesGeneralSettings::PreferencesGeneralSettings(QWidget *parent)
    : QWidget(parent)
{
    auto *label = new QLabel(tr("<strong style=\"font-size:large;\">General Options</strong>"));


    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(label);
}


QString PreferencesGeneralSettings::title() const
{
    return tr("General");
}


void PreferencesGeneralSettings::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


void PreferencesGeneralSettings::onSettingsChanged()
{
    emit settingsChanged();
}
