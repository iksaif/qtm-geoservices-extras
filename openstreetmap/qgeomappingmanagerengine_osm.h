/****************************************************************************
**
** Copyright (C) 2011 Corentin Chary
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Corentin Chary (corentin.chary@gmail.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGEOMAPPINGMANAGERENGINE_OSM_H
#define QGEOMAPPINGMANAGERENGINE_OSM_H

#include "qgeoserviceproviderplugin_osm.h"

#include <qgeoserviceprovider.h>
#include <qgeotiledmappingmanagerengine.h>

class QNetworkAccessManager;
class QNetworkDiskCache;

QTM_USE_NAMESPACE

class QGeoMappingManagerEngineOsm : public QGeoTiledMappingManagerEngine
{
    Q_OBJECT
public:
    QGeoMappingManagerEngineOsm(const QMap<QString, QVariant> &parameters,
                                  QGeoServiceProvider::Error *error,
                                  QString *errorString);
    virtual ~QGeoMappingManagerEngineOsm();

    QGeoMapData* createMapData();
    QGeoTiledMapReply* getTileImage(const QGeoTiledMapRequest &request);

private:
    Q_DISABLE_COPY(QGeoMappingManagerEngineOsm)

    QString getRequestString(const QGeoTiledMapRequest &request) const;

    QMap<QString, QVariant> m_parameters;
    QNetworkAccessManager *m_nam;
    QStringList m_servers;
};

#endif

