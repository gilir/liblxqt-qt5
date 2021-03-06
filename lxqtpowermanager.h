/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXDE-Qt - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef LXQTPOWERMANAGER_H
#define LXQTPOWERMANAGER_H

#include <QObject>
#include <QAction>
#include "lxqtglobals.h"

namespace LxQt
{
class Power;

/*! QAction centric menu aware wrapper around lxqtpower
*/
class LXQT_API PowerManager : public QObject
{
    Q_OBJECT

public:
    PowerManager(QObject * parent, bool skipWarning = false);
    ~PowerManager();
    QList<QAction*> availableActions();

public slots:
    // power management
    void suspend();
    void hibernate();
    void reboot();
    void shutdown();
    // lxqt session
    void logout();

public:
    bool skipWarning() const { return m_skipWarning; }

private:
    LxQt::Power * m_power;
    bool m_skipWarning;

private slots:
    void hibernateFailed();
    void suspendFailed();
};

} // namespace LxQt

#endif // LXQTPOWERMANAGER_H
