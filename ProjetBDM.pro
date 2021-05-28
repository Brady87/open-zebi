QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DESTDIR = $$PWD

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}

SOURCES += \
    ground.cpp \
    barrel.cpp \
    car.cpp \
    gauge.cpp \
    main.cpp \
    myglwidget.cpp \
    stopzone.cpp \
    webcam.cpp

HEADERS += \
    ground.h \
    barrel.h \
    car.h \
    gauge.h \
    myglwidget.h \
    stopzone.h \
    webcam.h

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core452 \
    -lopencv_highgui452 \
    -lopencv_imgproc452 \
    -lopencv_imgcodecs452 \
    -lopencv_videoio452 \
    -lopencv_features2d452 \
    -lopencv_calib3d452 \
    -lopencv_objdetect452

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/textures.qrc

