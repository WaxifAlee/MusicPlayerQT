QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AVLTree.cpp \
    main.cpp \
    musicplayer.cpp \
    signup.cpp \
    soundsky.cpp \
    user.cpp

HEADERS += \
    AVLTree.h \
    musicplayer.h \
    signup.h \
    soundsky.h \
    user.h

FORMS += \
    musicplayer.ui \
    signup.ui \
    soundsky.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    database/database.sqlite
