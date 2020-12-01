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

#include "dialog_title_box.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QVBoxLayout>


DialogTitleBox::DialogTitleBox(QWidget *parent)
    : QWidget(parent)
{
    auto *logo = new QSvgWidget;
    logo->load(QStringLiteral(":/icons/apps/22/mediathekview.svg"));

    auto *name = new QLabel(tr("<strong style=\"font-size:large;\">%1</strong> v%2").arg(QApplication::applicationName(), QApplication::applicationVersion()));
    auto *description = new QLabel(tr("A front-end tool for the MediathekView database"));

    auto *labels = new QVBoxLayout;
    labels->addWidget(name);
    labels->addWidget(description);

    // Main layout
    layout = new QHBoxLayout(this);
    layout->addWidget(logo);
    layout->addLayout(labels);

    // Set logo size
    const int height = name->sizeHint().height() + labels->layout()->spacing() + description->sizeHint().height();
    logo->setFixedSize(height, height);
}


void DialogTitleBox::setZeroMargins()
{
    layout->setContentsMargins(0, 0, 0, 0);
}
