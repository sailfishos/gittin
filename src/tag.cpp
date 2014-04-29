/*
 * Copyright (C) 2014 Jolla Ltd.
 * Contact: Giulio Camuffo <giulio.camuffo@jollamobile.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
 */

#include "tag.h"

#include <QSharedData>
#include <QString>
#include <QDebug>

namespace LibGit
{

class TagPrivate : public QSharedData
{
public:
    TagPrivate(const QString &n)
        : name(n)
    {
    }

    TagPrivate(const TagPrivate &o)
        : name(o.name)
    {
    }

    QString name;
};


Tag::Tag(const QString &name)
   : d(new TagPrivate(name))
{

}

Tag::Tag(const Tag &other)
   : d(other.d)
{
}

Tag::~Tag()
{
}

Tag &Tag::operator=(const Tag &other)
{
    d = other.d;
    return *this;
}

QString Tag::name() const
{
    return d->name;
}


QDebug operator<<(QDebug dbg, const Tag &t)
{
    dbg.nospace() << "Tag(" << t.name() << ")";
    return dbg.space();
}

}
