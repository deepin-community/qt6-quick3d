// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QTest>
#include <QSignalSpy>

#include <QtQuick3D/private/qquick3dpointlight_p.h>

#include <QtQuick3DRuntimeRender/private/qssgrenderlight_p.h>
#include <QtQuick3D/private/qquick3dobject_p.h>
#include <QtQuick3DUtils/private/qssgutils_p.h>

class tst_QQuick3DPointLight : public QObject
{
    Q_OBJECT

    // Work-around to get access to updateSpatialNode
    class Light : public QQuick3DPointLight
    {
    public:
        using QQuick3DPointLight::updateSpatialNode;
    };

private slots:
    void testProperties();
    void testScope();
};

void tst_QQuick3DPointLight::testProperties()
{
    Light light;
    auto node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(nullptr));
    const auto originalNode = node; // for comparisons later...
    QVERIFY(node);

    // lightType
    QCOMPARE(QSSGRenderLight::Type::PointLight, node->type);

    const float brightness = 0.5f;
    light.setBrightness(brightness);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(originalNode, node);
    QCOMPARE(brightness, node->m_brightness);
    QCOMPARE(light.brightness(), node->m_brightness);

    const float constantFade = 0.4f;
    light.setConstantFade(constantFade);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(constantFade, node->m_constantFade);
    QCOMPARE(light.constantFade(), node->m_constantFade);

    const float linearFade = 0.4f;
    light.setLinearFade(linearFade);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(linearFade, node->m_linearFade);
    QCOMPARE(light.linearFade(), node->m_linearFade);

    const float quadraticFade = 0.4f;
    light.setQuadraticFade(quadraticFade);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(quadraticFade, node->m_quadraticFade);
    QCOMPARE(light.quadraticFade(), node->m_quadraticFade);

    const float shadowBias = 0.5f;
    light.setShadowBias(shadowBias);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowBias, node->m_shadowBias);
    QCOMPARE(light.shadowBias(), node->m_shadowBias);

    const float shadowFactor = 4.0f;
    light.setShadowFactor(shadowFactor);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowFactor, node->m_shadowFactor);
    QCOMPARE(light.shadowFactor(), node->m_shadowFactor);

    const float shadowMapFar = 2000.0f;
    light.setShadowMapFar(shadowMapFar);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowMapFar, node->m_shadowMapFar);
    QCOMPARE(light.shadowMapFar(), node->m_shadowMapFar);

    const float shadowFilter = 20.0f;
    light.setShadowFilter(shadowFilter);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowFilter, node->m_shadowFilter);
    QCOMPARE(light.shadowFilter(), node->m_shadowFilter);

    const QQuick3DAbstractLight::QSSGShadowMapQuality qualities[] = {
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityLow,
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityMedium,
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityHigh,
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityVeryHigh
    };
    const unsigned int mappedResolutions[] = {8, 9, 10, 11};

    for (int i = 0; i < 4; ++i) {
        const auto shadowMapQuality = qualities[i];
        const auto mappedResolution = mappedResolutions[i];
        light.setShadowMapQuality(shadowMapQuality);
        node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
        QCOMPARE(mappedResolution, node->m_shadowMapRes);
        QCOMPARE(light.shadowMapQuality(), shadowMapQuality);
    }

    light.setCastsShadow(true);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QVERIFY(node->m_castShadow);
    light.setCastsShadow(false);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QVERIFY(!node->m_castShadow);

    QColor color1("#12345678");
    QVector3D color1Vec3 = QSSGUtils::color::sRGBToLinear(color1).toVector3D();
    QColor color2("#cccccccc");
    QVector3D color2Vec3 = QSSGUtils::color::sRGBToLinear(color2).toVector3D();
    light.setColor(color1);
    light.setAmbientColor(color2);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(originalNode, node);
    QCOMPARE(color1, light.color());
    QCOMPARE(color2, light.ambientColor());
    // Note: none of these colors contain alpha
    QCOMPARE(color1Vec3, node->m_diffuseColor);
    QCOMPARE(color1Vec3, node->m_specularColor);
    QCOMPARE(color2Vec3, node->m_ambientColor);
}

void tst_QQuick3DPointLight::testScope()
{
    Light light;
    auto node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(nullptr));
    QVERIFY(node);
    QQuick3DNode nodeItem;
    QVERIFY(!light.scope());
    light.setScope(&nodeItem);
    QVERIFY(light.scope());
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    auto scope = static_cast<QSSGRenderNode*>(QQuick3DObjectPrivate::get(light.scope())->spatialNode);
    QCOMPARE(scope, node->m_scope);
}

QTEST_APPLESS_MAIN(tst_QQuick3DPointLight)
#include "tst_qquick3dpointlight.moc"
