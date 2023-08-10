// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef DYNAMICGEOMETRY_H
#define DYNAMICGEOMETRY_H

#include <QtQuick3D/QQuick3DGeometry>

class DynamicGeometry : public QQuick3DGeometry
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DynamicGeometry)
public:
    DynamicGeometry();

public Q_SLOTS:
    void changeGeometry();

private:
    void updateData();
};

#endif // DYNAMICGEOMETRY_H
