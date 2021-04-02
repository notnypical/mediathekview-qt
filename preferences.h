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

#ifndef PREFERENCES_H
#define PREFERENCES_H


class Preferences
{
public:
    Preferences();

    void loadSettings();
    void saveSettings();

    void setRestoreApplicationGeometry(bool value);
    bool restoreApplicationGeometry(bool isDefault = false);

    void setRestoreApplicationState(bool value);
    bool restoreApplicationState(bool isDefault = false);

private:
    bool m_restoreApplicationGeometry;
    bool m_restoreApplicationState;
};

#endif // PREFERENCES_H
