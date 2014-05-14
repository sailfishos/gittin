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

#ifndef REPOSTATUS_H
#define REPOSTATUS_H

#include <QSharedDataPointer>

namespace Gittin {

class RepoStatusPrivate;

class RepoStatus
{
public:
    RepoStatus(const RepoStatus &other);
    ~RepoStatus();

    RepoStatus &operator=(const RepoStatus &other);

    bool isClean() const;
    bool hasStagedFiles() const;
    bool hasDirtyFiles() const;
    bool hasUntrackedFiles() const;

    QStringList stagedFiles() const;
    QStringList dirtyFiles() const;
    QStringList untrackedFiles() const;

    struct File {
        char index;
        char workTree;
        QString file;
    };
    QList<File> files() const;

private:
    RepoStatus(const QByteArray &data);

    QSharedDataPointer<RepoStatusPrivate> d;
    friend class Repo;
};

}

#endif
