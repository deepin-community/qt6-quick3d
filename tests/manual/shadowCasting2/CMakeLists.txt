# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_internal_add_manual_test(manual_test_shadowCasting2
    GUI
    SOURCES
        main.cpp
    LIBRARIES
        Qt::Gui
        Qt::Quick
        Qt::Quick3D
)

# Resources:
set(qml_resource_files
    "main.qml"
)

qt_internal_add_resource(manual_test_shadowCasting2 "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)

