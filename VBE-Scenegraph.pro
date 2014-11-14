QT       -= core gui

TARGET = VBE-Scenegraph
TEMPLATE = lib
CONFIG += staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include src

include(../common.pri)

OTHER_FILES += \
    VBE-Scenegraph.pri

HEADERS += \
    include/VBE/scenegraph.hpp \
    include/VBE/VBE-Scenegraph.hpp \
    include/VBE/scenegraph/Camera.hpp \
    include/VBE/scenegraph/ContainerObject.hpp \
    include/VBE/scenegraph/Game.hpp \
    include/VBE/scenegraph/GameObject.hpp

SOURCES += \
    src/VBE/scenegraph/Camera.cpp \
    src/VBE/scenegraph/ContainerObject.cpp \
    src/VBE/scenegraph/Game.cpp \
    src/VBE/scenegraph/GameObject.cpp
