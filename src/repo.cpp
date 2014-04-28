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

#include <QProcess>
#include <QDebug>

#include "repo.h"
#include "repostatus.h"

namespace LibGit {

class RepoPrivate
{
public:
    RepoPrivate()
        : process(new QProcess)
    {
    }

    ~RepoPrivate()
    {
        delete process;
    }

    QProcess *process;
};



Repo::Repo(const QString &path)
    : d(new RepoPrivate)
{
    d->process->setWorkingDirectory(path);
    d->process->setProcessChannelMode(QProcess::ForwardedErrorChannel);
}

Repo::~Repo()
{
    delete d;
}

Repo *Repo::clone(const QUrl &url, const QString &path, const QString &name)
{
    return 0;
}

void Repo::init()
{
    basicCmd("init");
}

void Repo::reset()
{
    basicCmd("reset");
}

void Repo::clean()
{
    basicCmd("clean");
}

RepoStatus Repo::status() const
{
    return RepoStatus(basicCmd("status", QStringList() << "-z"));
}

QByteArray Repo::basicCmd(const QString &cmd, const QStringList &params) const
{
    d->process->start(QLatin1String("git"), QStringList() << cmd << params);
    qDebug()<<"executing" << QLatin1String("git") << (QStringList() << cmd << params);
    d->process->waitForFinished();
    QByteArray output = d->process->readAllStandardOutput();
    return output;
}

}
