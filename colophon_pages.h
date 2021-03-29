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

#ifndef COLOPHON_PAGES_H
#define COLOPHON_PAGES_H

#include <QVBoxLayout>
#include <QWidget>


class ColophonAboutPage : public QWidget
{
    Q_OBJECT

public:
    explicit ColophonAboutPage(QWidget *parent = nullptr);

    void setZeroMargins();

    QString title() const;

private:
    QVBoxLayout *m_layout;
};


class ColophonAuthorsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ColophonAuthorsPage(QWidget *parent = nullptr);

    void setZeroMargins();

    QString title() const;

private:
    QVBoxLayout *m_layout;
};


class ColophonCreditsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ColophonCreditsPage(QWidget *parent = nullptr);

    void setZeroMargins();

    QString title() const;

private:
    QVBoxLayout *m_layout;
};


class ColophonEnvironmentPage : public QWidget
{
    Q_OBJECT

public:
    explicit ColophonEnvironmentPage(QWidget *parent = nullptr);

    void setZeroMargins();

    QString title() const;

private:
    QVBoxLayout *m_layout;
};


class ColophonLicensePage : public QWidget
{
    Q_OBJECT

public:
    explicit ColophonLicensePage(QWidget *parent = nullptr);

    void setZeroMargins();

    QString title() const;

private:
    QVBoxLayout *m_layout;
};

#endif // COLOPHON_PAGES_H
