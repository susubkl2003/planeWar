QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bomb.cpp \
    bullet.cpp \
    enemyplane.cpp \
    heroplane.cpp \
    main.cpp \
    map.cpp \
    music.cpp \
    widget.cpp

HEADERS += \
    bomb.h \
    bullet.h \
    config.h \
    enemyplane.h \
    heroplane.h \
    map.h \
    music.h \
    widget.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

FORMS += \
    widget.ui

