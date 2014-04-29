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
#include <QDebug>

#include "commit.h"

namespace LibGit
{

class CommitPrivate : public QSharedData
{
public:
    CommitPrivate(Repo *r, const QString &s)
        : repo(r)
        , sha(s)
    {
    }

    Repo *repo;
    QString message;
    QString sha;
};


Commit::Commit(Repo *repo, const QString &sha)
      : d(new CommitPrivate(repo, sha))
{
}

Commit::Commit(const Commit &other)
      : d(other.d)
{
}

Commit::~Commit()
{
}

Commit &Commit::operator=(const Commit &other)
{
    d = other.d;
    return *this;
}

QString Commit::message() const
{
    return d->message;
}

QString Commit::sha() const
{
    return d->sha;
}

QDebug operator<<(QDebug dbg, const Commit &t)
{
    dbg.nospace() << "Commit(" << t.sha() << " " << t.message() << ")";
    return dbg.space();
}

}
