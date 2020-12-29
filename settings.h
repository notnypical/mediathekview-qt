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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>


const bool RESTORE_APPLICATION_STATE_DEFAULT = true;
const bool RESTORE_APPLICATION_GEOMETRY_DEFAULT = true;
const bool RESTORE_DIALOG_GEOMETRY_DEFAULT = true;


class Settings
{
public:
    Settings();

    void load(QSettings &settings);
    void save(QSettings &settings);

    void setRestoreApplicationState(bool value);
    bool restoreApplicationState(bool isDefault = false);

    void setRestoreApplicationGeometry(bool value);
    bool restoreApplicationGeometry(bool isDefault = false);

    void setRestoreDialogGeometry(bool value);
    bool restoreDialogGeometry(bool isDefault = false);

private:
    bool m_restoreApplicationState;
    bool m_restoreApplicationGeometry;
    bool m_restoreDialogGeometry;
};

#endif // SETTINGS_H
