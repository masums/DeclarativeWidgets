/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "declarativefiledialog_p.h"

class DeclarativeFileDialogAttached::Private
{
  public:
    Private() : options(-1) {}

  public:
    QString caption;
    QString dir;
    QStringList nameFilters;
    int options;
    QString selectedFilter;
};

DeclarativeFileDialogAttached::DeclarativeFileDialogAttached(QObject *parent)
  : StaticDialogMethodAttached(parent), d(new Private)
{
}

DeclarativeFileDialogAttached::~DeclarativeFileDialogAttached()
{
  delete d;
}

void DeclarativeFileDialogAttached::setCaption(const QString &caption)
{
  if (caption == d->caption)
    return;

  d->caption = caption;
  emit captionChanged(caption);
}

QString DeclarativeFileDialogAttached::caption() const
{
  return d->caption;
}

void DeclarativeFileDialogAttached::setDir(const QString &dir)
{
  if (dir == d->dir)
    return;

  d->dir = dir;
  emit dirChanged(dir);
}

QString DeclarativeFileDialogAttached::dir() const
{
  return d->dir;
}

void DeclarativeFileDialogAttached::setNameFilters(const QStringList &nameFilters)
{
  if (nameFilters == d->nameFilters)
    return;

  d->nameFilters = nameFilters;
  emit nameFiltersChanged(nameFilters);
}

QStringList DeclarativeFileDialogAttached::nameFilters() const
{
  return d->nameFilters;
}

void DeclarativeFileDialogAttached::setOptions(int options)
{
  if (d->options == options)
    return;

  d->options = static_cast<QFileDialog::Options>(options);
  emit optionsChanged(options);
}

int DeclarativeFileDialogAttached::options() const
{
  return d->options < 0 ? 0 : d->options;
}

QString DeclarativeFileDialogAttached::selectedFilter() const
{
  return d->selectedFilter;
}

QString DeclarativeFileDialogAttached::getExistingDirectory()
{
  const QFileDialog::Options options = (d->options < 0 ? QFileDialog::ShowDirsOnly : static_cast<QFileDialog::Options>(d->options));

  return QFileDialog::getExistingDirectory(bestParentWindow(), d->caption, d->dir, options);
}

QString DeclarativeFileDialogAttached::getOpenFileName()
{
  const QFileDialog::Options options = static_cast<QFileDialog::Options>(d->options < 0 ? 0 : d->options);
  QString selectedFilter;

  const QString retVal = QFileDialog::getOpenFileName(bestParentWindow(), d->caption, d->dir,
                                                      d->nameFilters.join(";;"), &selectedFilter, options);

  setSelectedFilter(selectedFilter);
  return retVal;
}

QStringList DeclarativeFileDialogAttached::getOpenFileNames()
{
  const QFileDialog::Options options = static_cast<QFileDialog::Options>(d->options < 0 ? 0 : d->options);
  QString selectedFilter;

  const QStringList retVal = QFileDialog::getOpenFileNames(bestParentWindow(), d->caption, d->dir,
                                                           d->nameFilters.join(";;"), &selectedFilter, options);

  setSelectedFilter(selectedFilter);
  return retVal;
}

QString DeclarativeFileDialogAttached::getSaveFileName()
{
  const QFileDialog::Options options = static_cast<QFileDialog::Options>(d->options < 0 ? 0 : d->options);
  QString selectedFilter;

  const QString retVal = QFileDialog::getSaveFileName(bestParentWindow(), d->caption, d->dir,
                                                      d->nameFilters.join(";;"), &selectedFilter, options);

  setSelectedFilter(selectedFilter);
  return retVal;
}

void DeclarativeFileDialogAttached::setSelectedFilter(const QString &filter)
{
  if (filter == d->selectedFilter)
    return;

  d->selectedFilter = filter;
  emit selectedFilterChanged(filter);
}


DeclarativeFileDialog::DeclarativeFileDialog(QWidget *parent)
  : QFileDialog(parent)
{
}

DeclarativeFileDialogAttached *DeclarativeFileDialog::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeFileDialogAttached(parent);
}
