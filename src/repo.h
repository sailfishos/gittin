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

#ifndef REPO_H
#define REPO_H

#include <QStringList>

#include "tag.h"

namespace LibGit {

class RepoStatus;
class Commit;
class Branch;
class Tag;
class Command;

class Repo
{
public:
    explicit Repo(const QString &path);
    ~Repo();

    static Repo *clone(const QUrl &url, const QString &path, const QString &name = QString());

    void init();
    void reset();
    void clean();

    void checkout(const Commit &commit);
    void checkout(const Branch branch);

    void add(const QString &file);
    void rm(const QString &file);
    Commit commit(const QString &message);

    RepoStatus status() const;
    QList<Tag> tags() const;

    QString configValue(const QString &name, const QString &defaultValue = QString()) const;
    void setConfigValue(const QString &name, const QString &value);

    Command *command(const QString &cmd, const QStringList &params = QStringList()) const;

private:
    QByteArray basicCmd(const QString &cmd, const QStringList &params = QStringList()) const;

    class RepoPrivate *const d;
    friend class RepoPrivate;
};

}

#endif
