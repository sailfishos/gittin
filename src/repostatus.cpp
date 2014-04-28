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

#include <QStringList>
#include <QDebug>

#include "repostatus.h"

namespace LibGit {

class RepoStatusPrivate
{
public:
    void parse(const QByteArray &data)
    {
        QList<QByteArray> files(data.split('\0'));

        foreach (QByteArray file, files) {
            char x = file[0];
            char y = file[1];
            QByteArray fileName = file.mid(2);

            if (x == '?' && y == '?') {
                untrackedFiles << fileName;
            } else if (x != ' ') {
                stagedFiles << fileName;
            } else {
                dirtyFiles << fileName;
            }
        }
    }

    QStringList stagedFiles;
    QStringList dirtyFiles;
    QStringList untrackedFiles;
};

RepoStatus::RepoStatus(const QByteArray &data)
          : d(new RepoStatusPrivate)
{
    d->parse(data);
}

RepoStatus::~RepoStatus()
{
    delete d;
}

bool RepoStatus::hasStagedFiles() const
{
    return !d->stagedFiles.isEmpty();
}

bool RepoStatus::hasDirtyFiles() const
{
    return !d->dirtyFiles.isEmpty();
}

bool RepoStatus::hasUntrackedFiles() const
{
    return !d->untrackedFiles.isEmpty();
}

QStringList RepoStatus::stagedFiles() const
{
    return d->stagedFiles;
}

QStringList RepoStatus::dirtyFiles() const
{
    return d->dirtyFiles;
}

QStringList RepoStatus::untrackedFiles() const
{
    return d->untrackedFiles;
}

}
