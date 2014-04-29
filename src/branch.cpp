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

#include <QSharedData>
#include <QString>

#include "branch.h"
#include "commit.h"
#include "repo.h"

namespace LibGit
{

class BranchPrivate : public QSharedData
{
public:
    QString name;
};


Branch::Branch(const QString &name)
      : d(new BranchPrivate)
{
    d->name = name;
}

Branch::Branch(const Branch &other)
      : d(other.d)
{
}

Branch::~Branch()
{
}

Branch &Branch::operator=(const Branch &other)
{
    d = other.d;
    return *this;
}

bool Branch::exists() const
{

}

QString Branch::name() const
{
    return d->name;
}

Commit Branch::head(unsigned int n) const
{

}

}
