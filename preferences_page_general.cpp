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

#include "preferences_page_general.h"

#include <QGroupBox>
#include <QLabel>


PreferencesPageGeneral::PreferencesPageGeneral(QWidget *parent)
    : QWidget(parent)
{
    // Title
    auto *title = new QLabel(tr("<strong style=\"font-size:large;\">%1</strong>").arg(this->title()));

    //
    // Content: Geometry & State

    m_chkRestoreApplicationGeometry = new QCheckBox(tr("Save and restore the application geometry"));
    connect(m_chkRestoreApplicationGeometry, &QCheckBox::stateChanged, this, &PreferencesPageGeneral::onPreferencesChanged);

    m_chkRestoreApplicationState = new QCheckBox(tr("Save and restore the application state"));
    connect(m_chkRestoreApplicationState, &QCheckBox::stateChanged, this, &PreferencesPageGeneral::onPreferencesChanged);

    auto *geometryStateLayout = new QVBoxLayout;
    geometryStateLayout->addWidget(m_chkRestoreApplicationGeometry);
    geometryStateLayout->addWidget(m_chkRestoreApplicationState);

    auto *geometryStateGroup = new QGroupBox(tr("Geometry && State"));
    geometryStateGroup->setLayout(geometryStateLayout);

    // Main layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(title);
    m_layout->addWidget(geometryStateGroup);
    m_layout->addStretch(1);
}


void PreferencesPageGeneral::setZeroMargins()
{
    m_layout->setContentsMargins(0, 0, 0, 0);
}


QString PreferencesPageGeneral::title() const
{
    return tr("General");
}


void PreferencesPageGeneral::onPreferencesChanged()
{
    emit preferencesChanged();
}


void PreferencesPageGeneral::setRestoreApplicationGeometry(const bool checked)
{
    m_chkRestoreApplicationGeometry->setChecked(checked);
}


bool PreferencesPageGeneral::restoreApplicationGeometry() const
{
    return m_chkRestoreApplicationGeometry->isChecked();
}


void PreferencesPageGeneral::setRestoreApplicationState(const bool checked)
{
    m_chkRestoreApplicationState->setChecked(checked);
}


bool PreferencesPageGeneral::restoreApplicationState() const
{
    return m_chkRestoreApplicationState->isChecked();
}
