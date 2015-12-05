TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    CarModel.cpp

RESOURCES += qml.qrc \
    assets/Shaders/shaders.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    CarModel.h
