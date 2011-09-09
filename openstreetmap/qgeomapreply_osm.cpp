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

#include "qgeomapreply_osm.h"

QGeoMapReplyOsm::QGeoMapReplyOsm(QNetworkReply *reply, const QGeoTiledMapRequest &request, QObject *parent)
        : QGeoTiledMapReply(request, parent),
        m_reply(reply)
{
    m_reply->setParent(this);
    QVariant fromCache = m_reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute);
    setCached(fromCache.toBool());

    connect(m_reply,
            SIGNAL(finished()),
            this,
            SLOT(networkFinished()));

    connect(m_reply,
            SIGNAL(error(QNetworkReply::NetworkError)),
            this,
            SLOT(networkError(QNetworkReply::NetworkError)));

    connect(m_reply,
            SIGNAL(destroyed()),
            this,
            SLOT(replyDestroyed()));
}

QGeoMapReplyOsm::~QGeoMapReplyOsm()
{
}

QNetworkReply* QGeoMapReplyOsm::networkReply() const
{
    return m_reply;
}

void QGeoMapReplyOsm::abort()
{
    if (!m_reply)
        return;

    m_reply->abort();
}

void QGeoMapReplyOsm::replyDestroyed()
{
    m_reply = 0;
}

void QGeoMapReplyOsm::networkFinished()
{
    if (!m_reply)
        return;

    if (m_reply->error() != QNetworkReply::NoError) {
        return;
    }

    setMapImageData(m_reply->readAll());
    setMapImageFormat("PNG");
    setFinished(true);

    m_reply->deleteLater();
    m_reply = 0;
}

void QGeoMapReplyOsm::networkError(QNetworkReply::NetworkError error)
{
    if (!m_reply)
        return;

    if (error != QNetworkReply::OperationCanceledError)
        setError(QGeoTiledMapReply::CommunicationError, m_reply->errorString());
    m_reply->deleteLater();
    m_reply = 0;
}

