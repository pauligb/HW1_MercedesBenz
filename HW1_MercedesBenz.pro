TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    ModelLoader.cpp \
    CarModel.cpp \
    Scene.cpp

RESOURCES += qml.qrc \
    assets/models.qrc  \
    assets/textures.qrc  \
    assets/Shaders/shaders.qrc  \
    assets/images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    ModelLoader.h \
    CarModel.h \
    Scene.h \
    Model3DInterface.h
