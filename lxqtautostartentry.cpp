/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXDE-Qt - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright (C) 2012  Alec Moskvin <alecm@gmx.com>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "lxqtautostartentry.h"
#include <QtCore/QFileInfo>
#include <QtXdg/XdgAutoStart>
#include <QtXdg/XdgDirs>

using namespace LxQt;

AutostartEntry::AutostartEntry() :
    mLocalState(StateNone), mSystem(false)
{
}

AutostartEntry::AutostartEntry(const QString& name):
    mLocalState(StateNone), mSystem(false)
{
    foreach (const QString& dir, XdgDirs::autostartDirs())
    {
        QString path = QString("%1/%2").arg(dir, name);
        if (QFile(path).exists())
        {
            mSystemFile.load(path);
            mSystem = true;
            break;
        }
    }

    QString path = QString("%1/%2").arg(XdgDirs::autostartHome(), name);
    if (QFile(path).exists())
    {
        mLocalFile.load(path);
        mLocalState = StateExists;
    }
}

void AutostartEntry::setFile(const XdgDesktopFile& file)
{
    bool local = isLocal();
    if (mSystem && local && file == mSystemFile)
    {
        removeLocal();
    }
    else
    {
        if (local)
            mLocalState = StateModified;
        else
            mLocalState = StateTransient;
        mLocalFile = file;
    }
}

bool AutostartEntry::removeLocal()
{
    if (!isLocal())
        return false;

    if (mLocalState == StateTransient)
        mLocalState = StateNone;
    else
        mLocalState = StateDeleted;

    return !mSystem;
}

const XdgDesktopFile& AutostartEntry::file() const
{
    return isLocal() ? mLocalFile : mSystemFile;
}

QString AutostartEntry::name() const
{
    return QFileInfo(file().fileName()).fileName();
}

void AutostartEntry::setEnabled(bool enable)
{
    XdgDesktopFile f = file();
    if (enable)
        f.removeEntry("Hidden");
    else
        f.setValue("Hidden", true);

    setFile(f);
}

bool AutostartEntry::isEnabled() const
{
    return !isEmpty() && !file().value("Hidden", false).toBool();
}

bool AutostartEntry::commit()
{
    if (mLocalState == StateDeleted)
    {
        mLocalState = StateNone;
        return QFile::remove(mLocalFile.fileName());
    }
    else if (mLocalState == StateModified || mLocalState == StateTransient)
    {
        mLocalState = StateExists;
        return mLocalFile.save(XdgAutoStart::localPath(mLocalFile));
    }
    return true;
}
