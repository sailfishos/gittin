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

#ifndef BRANCH_H
#define BRANCH_H

#include <QSharedDataPointer>

class QString;

namespace Gittin
{

class Repo;
class Commit;
class BranchPrivate;

class Branch
{
public:
    explicit Branch(Repo *repo, const QString &name);
    Branch(const Branch &other);
    ~Branch();

    Branch &operator=(const Branch &other);

    bool exists() const;
    QString name() const;
    Commit head(unsigned int n = 0) const;

private:
    QSharedDataPointer<BranchPrivate> d;
};

}

#endif
