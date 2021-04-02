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

#include "preferences.h"

#include <QSettings>


Preferences::Preferences()
{
    // General: Geometry & State
    m_restoreApplicationGeometry = true;
    m_restoreApplicationState = true;
}


void Preferences::loadSettings()
{
    QSettings settings;

    settings.beginGroup(QStringLiteral("Preferences"));

    // General: Geometry & State
    setRestoreApplicationGeometry(settings.value(QStringLiteral("RestoreApplicationGeometry"), true).toBool());
    setRestoreApplicationState(settings.value(QStringLiteral("RestoreApplicationState"), true).toBool());

    settings.endGroup();
}


void Preferences::saveSettings()
{
    QSettings settings;

    settings.remove(QStringLiteral("Preferences"));
    settings.beginGroup(QStringLiteral("Preferences"));

    // General: Geometry & State
    settings.setValue(QStringLiteral("RestoreApplicationGeometry"), m_restoreApplicationGeometry);
    settings.setValue(QStringLiteral("RestoreApplicationState"), m_restoreApplicationState);

    settings.endGroup();
}


void Preferences::setRestoreApplicationGeometry(bool value)
{
    m_restoreApplicationGeometry = value;
}


bool Preferences::restoreApplicationGeometry(bool isDefault)
{
    if (isDefault)
        return true;

    return m_restoreApplicationGeometry;
}


void Preferences::setRestoreApplicationState(bool value)
{
    m_restoreApplicationState = value;
}


bool Preferences::restoreApplicationState(bool isDefault)
{
    if (isDefault)
        return true;

    return m_restoreApplicationState;
}
