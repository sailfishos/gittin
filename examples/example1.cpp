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

#include <QCoreApplication>
#include <QDebug>

#include "src/repo.hpp"
#include "src/repostatus.hpp"
#include "src/branch.hpp"
#include "src/commit.hpp"

int main(int argv, char **argc)
{
    QCoreApplication app(argv, argc);

    Gittin::Repo repo(".");

    QString action = app.arguments().size() > 1 ? app.arguments().at(1) : QString();
    if (action == QLatin1String("init")) {
        repo.init();
    } else if (action == QLatin1String("status")) {
        Gittin::RepoStatus status = repo.status();
        qDebug()<<"untracked:" << status.untrackedFiles();
        qDebug()<<"staged:" << status.stagedFiles();
        qDebug()<<"dirty" << status.dirtyFiles();
    } else if (action == QLatin1String("show_tags")) {
        qDebug() << repo.tags();
    } else if (action == QLatin1String("check_branch")) {
        Gittin::Branch branch(&repo, app.arguments().at(2));
        qDebug() << branch.exists();
    } else if (action == QLatin1String("commit")) {
        Gittin::Branch branch(&repo, app.arguments().at(2));
        qDebug() << branch.head(app.arguments().at(3).toInt());
    } else if (action == QLatin1String("hash-object")) {
        qDebug() << repo.hashObject(app.arguments().at(2));
    }

    return 0;
}
