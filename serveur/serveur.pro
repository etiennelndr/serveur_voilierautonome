######################################################################
# Automatically generated by qmake (2.01a) mer. oct. 10 09:11:57 2018
######################################################################

QT += network widgets concurrent serialport sql

greaterThan(QT_MAJOR_VERSION, 4)

TARGET = serveur
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

DEPENDPATH += . include main src
INCLUDEPATH += . include

SOURCES += main/main.cpp src/serveur.cpp \
    src/message.cpp \
    src/mainwindow.cpp \
    src/serialdata.cpp \
    src/database.cpp

HEADERS += include/serveur.h \
    include/message.h \
    include/mainwindow.h \
    include/serialdata.h \
    include/database.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
