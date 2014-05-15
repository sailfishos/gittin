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
#include <QSharedPointer>

#include "repo.hpp"
#include "repostatus.hpp"
#include "commit.hpp"
#include "command.hpp"
#include "branch.hpp"

namespace Gittin {

class RepoPrivate
{
public:
    RepoPrivate()
    {
    }

    ~RepoPrivate()
    {
    }

    QString path;
};



Repo::Repo(const QString &path)
    : d(new RepoPrivate)
{
    d->path = path;
}

Repo::~Repo()
{
    delete d;
}

Repo *Repo::clone(const QUrl &url, const QString &path, const QString &name)
{
    return 0;
}

QString Repo::path() const
{
    return d->path;
}

bool Repo::init()
{
    QSharedPointer<Command> cmd = command("init");
    return !cmd->exitCode();
}

void Repo::reset(ResetOptions options, const QString &object)
{
    QStringList opts;
    if (options & ResetOptions::Hard) opts << "--hard";
    if (!object.isEmpty()) opts << object;
    basicCmd("reset", opts);
}

void Repo::clean(CleanOptions options, const QString &path)
{
    QStringList opts;
    if (options & CleanOptions::Force) opts << "-f";
    if (options & CleanOptions::RemoveDirectories) opts << "-d";
    if (options & CleanOptions::IgnoreIgnores) opts << "-x";
    if (!path.isEmpty()) opts << "--" << path;
    basicCmd("clean", opts);
}

void Repo::checkout(const Commit &commit, CheckoutOptions options)
{
    checkout(commit.sha(), options);
}

void Repo::checkout(const Branch &branch, CheckoutOptions options)
{
    checkout(branch.name(), options);
}

void Repo::checkout(const Tag &tag, CheckoutOptions options)
{
    checkout(tag.name(), options);
}

void Repo::checkout(const QString &object, CheckoutOptions options)
{
    QStringList opts;
    if (options & CheckoutOptions::Force) opts << "-f";
    opts << object;
    basicCmd("checkout", opts);
}

QByteArray Repo::hashObject(const QString &path) const
{
    return basicCmd("hash-object", QStringList() << path).left(40); //strip the newline
}

void Repo::add(const QString &file, AddOptions options)
{
    QStringList opts;
    if (options & AddOptions::All) opts << "-A";
    if (options & AddOptions::Update) opts << "-u";
    opts << file;
    basicCmd("add", opts);
}

void Repo::rm(const QString &file)
{
    basicCmd("rm", QStringList() << file);
}

Commit Repo::commit(const QString &message)
{
    basicCmd("commit", QStringList() << QLatin1String("-m") << message);
    QByteArray commit = basicCmd("log", QStringList() << "-n1" << "--oneline" << "--no-abbrev-commit");
    return Commit(this, commit.split(' ').first());
}

Tag Repo::tag(const QString &name)
{
    basicCmd("tag", QStringList() << name);
    return Tag(this, name);
}

RepoStatus Repo::status(const QString &path) const
{
    return RepoStatus(basicCmd("status", QStringList() << "-z" << (path.isEmpty() ? "." : path)));
}

QList<Tag> Repo::tags() const
{
    QList<Tag> list;

    QString out = basicCmd("tag", QStringList());
    QStringList names = out.split("\n");
    for (int i = 0; i < names.size() - 1; ++i) {
        // FIXME: Remove this const_cast somehow
        list.append(Tag(const_cast<Repo *>(this), names.at(i)));
    }

    return list;
}

QString Repo::configValue(const QString &name, const QString &defaultValue) const
{
    QSharedPointer<Command> cmd = command("config", QStringList() << name);
    if (cmd->exitCode() == 0) {
        return cmd->stdout();
    }

    return defaultValue;
}

void Repo::setConfigValue(const QString &name, const QString &value)
{
    command("config", QStringList() << name << value);
}

QSharedPointer<Command> Repo::command(const QString &cmd, const QStringList &params) const
{
    QProcess *proc = new QProcess;
    proc->setWorkingDirectory(d->path);
    proc->setProcessChannelMode(QProcess::ForwardedErrorChannel);
    proc->setProgram("git");
    proc->setArguments(QStringList() << cmd << params);

    QSharedPointer<Command> comm(new Command(proc));
    proc->start();
    proc->waitForFinished();
    return comm;
}

QByteArray Repo::basicCmd(const QString &cmd, const QStringList &params) const
{
    qDebug()<<"executing" << QLatin1String("git") << (QStringList() << cmd << params);
    return command(cmd, params)->stdout();
}

}
