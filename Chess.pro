QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets
QT += svg

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell.cpp \
    chessboard.cpp \
    figure.cpp \
    gamelogic.cpp \
    gamemainwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    positionmap.cpp

HEADERS += \
    cell.h \
    chessboard.h \
    figures/figure.h \
    gamelogic.h \
    gamemainwindow.h \
    mainwindow.h \
    positionmap.h \
    storage.h

FORMS += \
    gamemainwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
