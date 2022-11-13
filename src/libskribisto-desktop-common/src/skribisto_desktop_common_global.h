/***************************************************************************
 *   Copyright (C) 2016 by Cyril Jacquet                                 *
 *   cyril.jacquet@skribisto.eu                                        *
 *                                                                         *
 *  Filename: mysharedlib_global
 *                                                  *
 *  This file is part of Skribisto.                                    *
 *                                                                         *
 *  Skribisto is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  Skribisto is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Skribisto.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/
#ifndef SKRIBISTO_DESKTOP_COMMON_GLOBAL_H
#define SKRIBISTO_DESKTOP_COMMON_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(SKRIBISTO_DESKTOP_COMMON_LIBRARY)
#define SKRDESKTOPCOMMONEXPORT Q_DECL_EXPORT
#else // if defined(SKRIBISTO_COMMON_LIBRARY)
#define SKRDESKTOPCOMMONEXPORT Q_DECL_IMPORT
#endif // if defined(SKRIBISTO_COMMON_LIBRARY)

#endif // SKRIBISTO_DESKTOP_COMMON_GLOBAL_H
