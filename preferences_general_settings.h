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

#ifndef PREFERENCES_GENERAL_SETTINGS_H
#define PREFERENCES_GENERAL_SETTINGS_H

#include <QCheckBox>
#include <QVBoxLayout>
#include <QWidget>


class PreferencesGeneralSettings : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesGeneralSettings(QWidget *parent = nullptr);

    QString title() const;

    void setZeroMargins();

    void setRestoreApplicationState(const bool checked);
    bool restoreApplicationState() const;

    void setRestoreApplicationGeometry(const bool checked);
    bool restoreApplicationGeometry() const;

signals:
    void settingsChanged();

private slots:
    void onSettingsChanged();

private:
    QVBoxLayout *m_layout;

    QCheckBox *m_chkRestoreApplicationState;
    QCheckBox *m_chkRestoreApplicationGeometry;
};

#endif // PREFERENCES_GENERAL_SETTINGS_H
