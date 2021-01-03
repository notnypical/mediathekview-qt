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

#include "preferences_dialog.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>


PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Preferences"));

    setDialogGeometry();

    // Settings box
    m_generalSettings = new PreferencesGeneralSettings(this);
    m_generalSettings->setZeroMargins();
    connect(m_generalSettings, &PreferencesGeneralSettings::settingsChanged, this, &PreferencesDialog::onSettingsChanged);

    m_databaseSettings = new PreferencesDatabaseSettings(this);
    m_databaseSettings->setZeroMargins();
    connect(m_databaseSettings, &PreferencesDatabaseSettings::settingsChanged, this, &PreferencesDialog::onSettingsChanged);

    auto *stackedBox = new QStackedWidget;
    stackedBox->addWidget(m_generalSettings);
    stackedBox->addWidget(m_databaseSettings);
    stackedBox->setCurrentIndex(0);

    auto *listBox = new QListWidget;
    listBox->addItem(m_generalSettings->title());
    listBox->addItem(m_databaseSettings->title());
    listBox->setCurrentRow(stackedBox->currentIndex());
    connect(listBox, &QListWidget::currentRowChanged, stackedBox, &QStackedWidget::setCurrentIndex);

    auto *settingsBox = new QHBoxLayout;
    settingsBox->addWidget(listBox, 1);
    settingsBox->addWidget(stackedBox, 3);

    // Button box
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::RestoreDefaults | QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    m_buttonApply = buttonBox->button(QDialogButtonBox::Apply);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QAbstractButton::clicked, this, &PreferencesDialog::onButtonDefaultsClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onButtonOkClicked);
    connect(m_buttonApply, &QAbstractButton::clicked, this, &PreferencesDialog::onButtonApplyClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PreferencesDialog::close);

    // Main layout
    auto *layout = new QVBoxLayout(this);
    layout->addLayout(settingsBox);
    layout->addWidget(buttonBox);

    updateSettings();
    m_buttonApply->setEnabled(false);
}


void PreferencesDialog::setDialogGeometry(const QByteArray &geometry)
{
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }
    else {
        resize(800, 600);
    }
}


QByteArray PreferencesDialog::dialogGeometry() const
{
    return saveGeometry();
}


void PreferencesDialog::setSettings(const Settings &settings)
{
    m_settings = settings;

    updateSettings();
    m_buttonApply->setEnabled(false);
}


Settings PreferencesDialog::settings() const
{
    return m_settings;
}


void PreferencesDialog::onSettingsChanged()
{
    m_buttonApply->setEnabled(true);
}


void PreferencesDialog::onButtonDefaultsClicked()
{
    updateSettings(true);
}


void PreferencesDialog::onButtonOkClicked()
{
    saveSettings();
    close();
}


void PreferencesDialog::onButtonApplyClicked()
{
    saveSettings();
    m_buttonApply->setEnabled(false);
}


void PreferencesDialog::updateSettings(bool isDefault)
{
    // General
    m_generalSettings->setRestoreApplicationState(m_settings.restoreApplicationState(isDefault));
    m_generalSettings->setRestoreApplicationGeometry(m_settings.restoreApplicationGeometry(isDefault));
    m_generalSettings->setRestoreDialogGeometry(m_settings.restoreDialogGeometry(isDefault));
}


void PreferencesDialog::saveSettings()
{
    // General
    m_settings.setRestoreApplicationState(m_generalSettings->restoreApplicationState());
    m_settings.setRestoreApplicationGeometry(m_generalSettings->restoreApplicationGeometry());
    m_settings.setRestoreDialogGeometry(m_generalSettings->restoreDialogGeometry());
}
