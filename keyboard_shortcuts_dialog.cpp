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

#include "keyboard_shortcuts_dialog.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>

#include "keyboard_shortcuts_page.h"


KeyboardShortcutsDialog::KeyboardShortcutsDialog(QWidget *parent)
    : QDialog(parent)
{
    setMinimumSize(640, 480);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Keyboard Shortcuts"));

    // Content
    auto *keyboardShortcutsPage = new KeyboardShortcutsPage(parentWidget());
    keyboardShortcutsPage->setZeroMargins();
    connect(this, &KeyboardShortcutsDialog::actionTextChanged, keyboardShortcutsPage, &KeyboardShortcutsPage::onActionTextChanged);

    // Button box
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &KeyboardShortcutsDialog::close);

    // Main layout
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(keyboardShortcutsPage);
    layout->addWidget(buttonBox);
}


void KeyboardShortcutsDialog::onActionTextChanged()
{
    emit actionTextChanged();
}
