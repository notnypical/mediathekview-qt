/**
 * Copyright 2020-2021 NotNypical, <https://notnypical.github.io>.
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

#include "settings.h"


Settings::Settings()
{
    // General: State & Geometries
    m_restoreApplicationState = RESTORE_APPLICATION_STATE_DEFAULT;
    m_restoreApplicationGeometry = RESTORE_APPLICATION_GEOMETRY_DEFAULT;
    m_restoreDialogGeometry = RESTORE_DIALOG_GEOMETRY_DEFAULT;
}


void Settings::load(QSettings &settings)
{
    settings.beginGroup(QStringLiteral("Settings"));

    // General: State & Geometries
    setRestoreApplicationState(settings.value(QStringLiteral("restoreApplicationState"), RESTORE_APPLICATION_STATE_DEFAULT).toBool());
    setRestoreApplicationGeometry(settings.value(QStringLiteral("restoreApplicationGeometry"), RESTORE_APPLICATION_GEOMETRY_DEFAULT).toBool());
    setRestoreDialogGeometry(settings.value(QStringLiteral("restoreDialogGeometry"), RESTORE_DIALOG_GEOMETRY_DEFAULT).toBool());

    settings.endGroup();
}


void Settings::save(QSettings &settings)
{
    settings.beginGroup(QStringLiteral("Settings"));
    settings.remove("");

    // General: State & Geometries
    settings.setValue(QStringLiteral("restoreApplicationState"), m_restoreApplicationState);
    settings.setValue(QStringLiteral("restoreApplicationGeometry"), m_restoreApplicationGeometry);
    settings.setValue(QStringLiteral("restoreDialogGeometry"), m_restoreDialogGeometry);

    settings.endGroup();
}


void Settings::setRestoreApplicationState(bool value)
{
    m_restoreApplicationState = value;
}


bool Settings::restoreApplicationState(bool isDefault)
{
    if (isDefault)
        return RESTORE_APPLICATION_STATE_DEFAULT;

    return m_restoreApplicationState;
}


void Settings::setRestoreApplicationGeometry(bool value)
{
    m_restoreApplicationGeometry = value;
}


bool Settings::restoreApplicationGeometry(bool isDefault)
{
    if (isDefault)
        return RESTORE_APPLICATION_GEOMETRY_DEFAULT;

    return m_restoreApplicationGeometry;
}


void Settings::setRestoreDialogGeometry(bool value)
{
    m_restoreDialogGeometry = value;
}


bool Settings::restoreDialogGeometry(bool isDefault)
{
    if (isDefault)
        return RESTORE_DIALOG_GEOMETRY_DEFAULT;

    return m_restoreDialogGeometry;
}