/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXDE-Qt - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2013 LXDE-Qt team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
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

#ifndef LXQTTRANSLATOR_H
#define LXQTTRANSLATOR_H

#include <QStringList>
#include "lxqtglobals.h"

namespace LxQt
{
/**
  The Translator class provides internationalization support for application and librarioes.
 **/
class LXQT_API Translator
{
public:
    /**
      Returns a list of paths that the application will search translations files.
     **/
    static QStringList translationSearchPaths();

    /**
      Sets the list of directories to search translations. All existing paths
      will be deleted and the path list will consist of the paths given in paths.
     **/
    static void setTranslationSearchPaths(const QStringList &paths);

    /**
      Loads translations for application. If applicationName is not specified,
      then basename of QCoreApplication::applicationFilePath() is used.
      Returns true if the translation is successfully loaded; otherwise returns false.
    **/
    static bool translateApplication(const QString &applicationName = "");

    /**
      Loads translations for application. If applicationName is not specified,
      then basename of QCoreApplication::applicationFilePath() is used.
      Returns true if the translation is successfully loaded; otherwise returns false.
    **/
    static bool translateLibrary(const QString &libraryName = "");

};

} // namespace LxQt
#endif // LXQTTRANSLATOR_H
