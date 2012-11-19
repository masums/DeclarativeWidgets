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

#ifndef DECLARATIVEGRIDLAYOUT_P_H
#define DECLARATIVEGRIDLAYOUT_P_H

#include "declarativelayoutproxy_p.h"

#include <QGridLayout>

class DeclarativeGridLayoutAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
  Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
  Q_PROPERTY(int rowSpan READ rowSpan WRITE setRowSpan NOTIFY rowSpanChanged)
  Q_PROPERTY(int columnSpan READ columnSpan WRITE setColumnSpan NOTIFY columnSpanChanged)
  Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

  public:
    DeclarativeGridLayoutAttached(QWidget *widget, QObject *parent);
    DeclarativeGridLayoutAttached(QLayout *layout, QObject *parent);
    ~DeclarativeGridLayoutAttached();

    void setParentLayout(QGridLayout *parentLayout);

    void setRow(int row);
    int row() const;

    void setColumn(int column);
    int column() const;

    void setRowSpan(int rowSpan);
    int rowSpan() const;

    void setColumnSpan(int columnSpan);
    int columnSpan() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

  Q_SIGNALS:
    void rowChanged(int row);
    void columnChanged(int column);
    void rowSpanChanged(int rowSpan);
    void columnSpanChanged(int columnSpan);
    void alignmentChanged(Qt::Alignment alignment);

  private:
    class Private;
    Private *const d;
};

class DeclarativeGridLayout : public DeclarativeLayoutProxy<QGridLayout>
{
  DECLARATIVE_OBJECT

  public:
    explicit DeclarativeGridLayout(QObject *parent = 0);

    static DeclarativeGridLayoutAttached *qmlAttachedProperties(QObject *parent);

  protected:
    void addWidget(QWidget *widget, AbstractDeclarativeObject *declarativeObject);
    void addLayout(QLayout *layout, AbstractDeclarativeObject *declarativeObject);
};

QML_DECLARE_TYPEINFO(DeclarativeGridLayout, QML_HAS_ATTACHED_PROPERTIES)

#endif
